// glw_json.h - v0.1 - json parser for C/C++ - BSD-3
// Iakov Sumygin, May 2016

#ifndef _GLW_JSON_
#define _GLW_JSON_

#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <string_view>
#include <algorithm>
#include <limits.h>
#include <string.h>
#include <cmath>
#include <errno.h>
#include <assert.h>

// maximum count of properties per any JSON object
#define MAX_JSON_PROPS 300
#define SERIALIZE(prop) t.process(#prop, v.prop)
#define GLW_UNUSED(x) (void)x
#ifndef LOG_JSON_ERROR
	#define LOG_JSON_ERROR(...)
#endif
namespace json {

const char quote = '\"';

const int JSON_OK = 0;
const int JSON_FAIL = -1;
const int JSON_FILESYSTEM_ERROR = -2;
enum JSON_OPTIONS {
	RESET_IF_ABSENT = 1, // if property is absent, reset variable to 0
	ERROR_IF_ABSENT = 2, // if property is absent, return error
	// Parse any standard JSON: tolerate properties the struct doesn't read, in any order, and
	// fields serialized in any order (looked up by binary search). ON by default. Clear it for the
	// faster sorted linear-merge, which requires fields serialized in ascending name order and that
	// every JSON property be consumed.
	PARSE_ANY = 4
};
const int DEFAULT_OPTIONS = RESET_IF_ABSENT | PARSE_ANY;

struct property {
	std::string_view param, value;
};
typedef property prop_map[MAX_JSON_PROPS];

#define SERIALIZE_NAME (out << '\"' << name << "\": ")

inline const char* sv_end(std::string_view sv) {
	return sv.data() + sv.size();
}

// **************************************** loading JSON ***********************************
inline const char* skip_ws(const char* in) {
	while (*in && ::isspace(*in)) in++;
	return in;
}
inline const char* search_ws(const char* in) {
	while (*in && !::isspace(*in)) in++;
	return in;
}
// end of property
inline const char* search_eop(const char* in) {
	while (*in && *in != ',' && *in != '}' && *in != ']' && !isspace(*in)) in++;
	return in;
}
inline const char* search_eov(const char* in) {
	while (*in && *in != ',' && *in != ']' && !isspace(*in)) in++;
	return in;
}
inline const char* search_obj_end(const char* in, char open_brace, char close_brace) {
	int opened = 1;
	while (*in) {
		if (*in == close_brace)
			--opened;
		else if (*in == open_brace)
			++opened;
		if (!opened)
			return in + 1; // success - we found closing
		++in;
	}
	return in - 1; // error - end of file
}
inline const char* find_ch(const char* in, char ch) {
	while (*in && *in != ch) in++;
	return in;
}
inline size_t get_value_len(const char* in) {
	if (*in == '{') {
		// special case - for object as value, value len includes whitespace after the object
		const char* brace = search_obj_end(in + 1, '{', '}'); // embedded object
		return skip_ws(brace) - in;
	}
	if (*in == '[')
		return search_obj_end(in + 1, '[', ']') - in; // embedded array
	return (*in == quote ? find_ch(in + 1, quote) + 1 : search_eop(in)) - in;
}
inline const char* load_props(const char* in, const char* end, prop_map& props,
							  size_t& props_size) {
	in = skip_ws(in);
	if (*in == '}')
		return in; // special case - empty json

	props_size = 0;
	while (*in) {
		in = skip_ws(in);
		if (*in != quote)
			return in - 1; // error
		// parse value name
		property p;
		const char* name_start = in + 1;
		const size_t name_len = find_ch(name_start, quote) - name_start;
		p.param = std::string_view(name_start, name_len);
		in = name_start + name_len;
		if (!*in)
			return in - 1;
		in = skip_ws(in + 1);
		if (*in != ':')
			return in - 1; // error

		// parse value
		in = skip_ws(in + 1);
		const size_t value_len = get_value_len(in);
		p.value = std::string_view(in, value_len);
		in += value_len;
		if (in >= end)
			return end - 1; // error - value is not closed properly

		in = skip_ws(in);

		// register name-value pair
		if (props_size >= MAX_JSON_PROPS - 1)
			return in - 1; // not enough space - error
		props[props_size++] = p;

		if (*in != ',') {
			if (*in != '}')
				return in - 1; // error
			return in;		   // success - next symbol after brace
		}
		++in;
	}
	return in - 1; // error
}
inline bool compare_props(const property& p1, const property& p2) {
	return p1.param < p2.param;
}
inline const char* load(std::string_view sv, int& v, int options) {
	GLW_UNUSED(options);
	const char* str = sv.data();
	const size_t len = sv.size();
	char* pEnd;
	errno = 0;
	long int l = strtol(str, &pEnd, 10);
	if (pEnd < str + len)
		l = strtol(str, &pEnd, 16);
	v = (int)l;
	return (pEnd < str + len) || (errno == ERANGE) ? str : pEnd;
}
inline const char* load(std::string_view sv, unsigned int& v, int options) {
	GLW_UNUSED(options);
	const char* str = sv.data();
	const size_t len = sv.size();
	char* pEnd;
	errno = 0;
	unsigned long l = strtoul(str, &pEnd, 10);
	if (pEnd < str + len)
		l = strtoul(str, &pEnd, 16);
	v = (unsigned int)l;
	return errno != ERANGE && l < UINT_MAX && pEnd == str + len && str[0] != '-' ? pEnd : str;
}
inline const char* load(std::string_view sv, char& v, int options) {
	GLW_UNUSED(options);
	const char* str = sv.data();
	const size_t len = sv.size();
	char* pEnd;
	long l = strtol(str, &pEnd, 10);
	if (pEnd < str + len)
		l = strtol(str, &pEnd, 16);
	v = (char)l;
	return l <= CHAR_MAX && l>= CHAR_MIN && pEnd == str + len ? pEnd : str;
}
inline const char* load(std::string_view sv, unsigned char& v, int options) {
	GLW_UNUSED(options);
	const char* str = sv.data();
	const size_t len = sv.size();
	char* pEnd;
	unsigned long l = strtoul(str, &pEnd, 10);
	if (pEnd < str + len)
		l = strtoul(str, &pEnd, 16);
	v = (unsigned char)l;
	return l <= UCHAR_MAX && pEnd == str + len ? pEnd : str;
}
template <typename c, typename t, typename a>
const char* load(std::string_view sv, std::basic_string<c, t, a>& v, int options) {
	GLW_UNUSED(options);
	if (sv.size() < 2)
		return sv.data(); // it's not a string
	v.assign(sv.data() + 1, sv.size() - 2);
	return sv_end(sv);
}
inline const char* load(std::string_view sv, float& v, int options) {
	GLW_UNUSED(options);
	const char* str = sv.data();
	const size_t len = sv.size();
	char* pEnd;
	v = strtof(str, &pEnd);
	if (v == HUGE_VAL || v == -HUGE_VAL)
		return str;

	return pEnd < str + len ? str : sv_end(sv);
}
inline const char* load(std::string_view sv, bool& v, int options) {
	GLW_UNUSED(options);
	if (sv == "true")
		v = true;
	else if (sv == "false")
		v = false;
	else
		return sv.data();
	return sv_end(sv);
}
inline int get_error_line(const char* in, const char* pos) {
	int lines = 0;
	in = skip_ws(in);
	while (*in && in < pos) {
		if (*in == '\n')
			++lines;
		++in;
	}
	return lines + 1;
}
template <typename V> const char* load(std::string_view sv, V& t, int options);

// overrides for embedded objects and pointers to object
template <typename V> const char* load(std::string_view sv, V*& value, int options) {
	value = new V;
	return load(sv, *value, options);
}
template <typename containter_type>
const char* load_container(std::string_view sv, containter_type& t, int options) {
	const char* in = sv.data();
	if (*in != '[')
		return in - 1;

	std::insert_iterator<containter_type> it(t, t.end());
	typename containter_type::value_type v;
	do {
		in = skip_ws(in + 1);
		const size_t len = get_value_len(in);
		const std::string_view item(in, len);
		if (load(item, v, options) != sv_end(item))
			return in - 1;
		in += len;
		it = v;
		in = skip_ws(in);
		if (*in != ',') {
			if (*in != ']')
				return in - 1;
			else {
				++in;
				break; // end of array
			}
			++in;
		}
	} while (true);
	return in; // success
}
template <typename T, typename A>
const char* load(std::string_view sv, std::vector<T, A>& t, int options) {
	return load_container(sv, t, options);
}
struct LoadObject {
	LoadObject(const prop_map& _props, size_t _props_size, const char* _start, int _options)
		: props(_props), props_size(_props_size), current(0), options(_options), error_pos(NULL),
		  start(_start), _prev_name("") {}
	const prop_map& props;
	size_t props_size;
	size_t current;
	int options;
	const char* error_pos;
	const char* start;
	const char* _prev_name;
	// Load the parsed property `props[idx]` into `value`; set error_pos on a malformed value.
	template <typename V> bool load_prop(size_t idx, V& value) {
		const std::string_view val = props[idx].value;
		const char* end = load(val, value, options);
		if (end == sv_end(val))
			return true;
		error_pos = end;
		current = props_size; // stop parsing on a malformed value
		return false;
	}
	template <typename V> bool handle_absent(V& value) {
		if (options & RESET_IF_ABSENT)
			value = V();
		if (options & ERROR_IF_ABSENT) {
			error_pos = start; // required property missing
			current = props_size;
			return false;
		}
		return true;
	}
	template <typename V> bool process(const char* name, V& value) {
		if (options & PARSE_ANY) {
			const property* const end = props + props_size;
			const property* it = std::lower_bound(
				props, end, name,
				[](const property& p, const char* n) { return p.param < n; });
			if (it != end && it->param == name)
				return load_prop(static_cast<size_t>(it - props), value);
			return handle_absent(value);
		}
#ifndef NDEBUG
		// fast path requires ascending field order (select everything inside serialize() + F9 in
		// Sublime Text 3 to sort)
		if (strcmp(_prev_name, name) >= 0)
			assert(false && "variables should be serialized in alphabetical order (or use PARSE_ANY)");
		_prev_name = name;
#endif
		if (current < props_size && props[current].param == name)
			return load_prop(current++, value);
		return handle_absent(value);
	}
	template <typename V> bool process_skip_empty(const char* name, V& value) {
		return process(name, value);
	}
};

template <typename V> const char* load(std::string_view sv, V& t, int options) {
	const char* start = sv.data();
	const size_t len = sv.size();
	prop_map props;
	size_t props_size = 0;
	const char* in = skip_ws(start);

	if (*in != '{')
		return in - 1;										 // error
	in = load_props(in + 1, start + len, props, props_size); // load prop map for child object
	if (*in != '}')
		return in - 1; // error

	std::sort(props, props + props_size, compare_props);

	LoadObject serializer(props, props_size, start, options);
	if (!serialize(serializer, t))
		return serializer.error_pos;

	if (serializer.error_pos) // a property value was malformed
		return serializer.error_pos;

	// Fast (sorted) mode requires every property to be consumed; PARSE_ANY tolerates extras.
	if (!(options & PARSE_ANY) && serializer.current < serializer.props_size)
		return props[serializer.current].param.data();

	in = skip_ws(in + 1); // skip whitespace after
	return in;
}
template <typename T>
int load_object_from_string(const char* json_string, T& t, size_t len = (size_t)-1,
							int options = DEFAULT_OPTIONS) {
	if (len == (size_t)-1)
		len = strlen(json_string);
	const char* pos = load(std::string_view(json_string, len + 1), t, options);
	if (pos != json_string + len) {
		return get_error_line(json_string, pos); // return error position
	}
	return JSON_OK;
}
template <typename T>
int load_object_from_string(std::string_view json_string, T& t, int options = DEFAULT_OPTIONS) {
	const char* pos = load(json_string, t, options);
	if (pos != sv_end(json_string)) {
		return get_error_line(json_string.data(), pos);
	}
	return JSON_OK;
}
template <typename T, typename A>
int load_object_from_string(const char* json_string, std::vector<T, A>& t, size_t len = (size_t)-1,	int options = DEFAULT_OPTIONS) {
	if (len == (size_t)-1)
		len = strlen(json_string);
	const char* pos = load_container(std::string_view(json_string, len + 1), t, options);
	if (pos != json_string + len) {
		return get_error_line(json_string, pos); // return error position
	}
	return JSON_OK;
}
template <typename T>
int load_object_from_file(const char* filename, T& t, int options = DEFAULT_OPTIONS) {
    std::ifstream is(filename, std::ios::binary);
    if (!is)
        return JSON_FILESYSTEM_ERROR;

    is.seekg(0, is.end);
    int length = (int)is.tellg();
    is.seekg(0, is.beg);
    char* buffer = new char[length + 1];
    is.read(buffer, length);
    buffer[length] = 0;
    is.close();
    int ret = load_object_from_string(buffer, t, length, options);
    delete[] buffer;
    return ret;
}
// **************************************** saving JSON ***********************************

inline void save(std::ostream& out, int& t, int tabs) {
	GLW_UNUSED(tabs);
	out << t;
}
inline void save(std::ostream& out, unsigned int& t, int tabs) {
	GLW_UNUSED(tabs);
	out << t;
}
inline void save(std::ostream& out, bool& t, int tabs) {
	GLW_UNUSED(tabs);
	out << (t ? "true" : "false");
}
inline void save(std::ostream& out, float& t, int tabs) {
	GLW_UNUSED(tabs);
	out << t;
}
inline void save(std::ostream& out, char& t, int tabs) {
	GLW_UNUSED(tabs);
	out << t;
}
inline void save(std::ostream& out, const char* t, int tabs) {
	GLW_UNUSED(tabs);
	out << quote << t << quote;
}
inline void save(std::ostream& out, std::string_view t, int tabs) {
	GLW_UNUSED(tabs);
	out << quote << t << quote;
}
template <typename c, typename tr, typename a>
void save(std::ostream& out, std::basic_string<c, tr, a>& t, int tabs) {
	GLW_UNUSED(tabs);
	out << quote << t << quote;
}

template <typename T> bool save(std::ostream& out, T& t, int tabs);
template <typename T> bool save(std::ostream& out, T*& t, int tabs){
	if (t)
		return save(out, *t, tabs);
	else
		out << "{}";
	return true;
}
template <typename iterator>
bool save_container(std::ostream& out, iterator begin, iterator end, int tabs) {
	out << '[';
	for (iterator i = begin; i != end; ++i) {
		if (i != begin)
			out << ',';
		save(out, *i, tabs + 1);
	}
	out << ']';
	return !out.fail();
}
template <typename T, typename A> bool save(std::ostream& out, std::vector<T, A>& t, int tabs) {
	return save_container(out, t.begin(), t.end(), tabs);
}
struct SaveObject {
	std::ostream& out;
	bool first;
	int tabs;
	SaveObject(std::ostream& _out, int _tabs = 1) : out(_out), first(true), tabs(_tabs) {}
	template <typename T> bool process(const char* name, T& t) {
		if (first)
			first = false;
		else
			out << ",\n";
		for (int i = 0; i < tabs; ++i) out << '\t';
		out << quote << name << quote << ": ";
		save(out, t, tabs);
		if (out.fail())
			return false;
		return true;
	}
	template <typename T> bool process_skip_empty(const char* name, T& t) {
		if (t == T())
			return true;
		return process(name, t);
	}
};
template <typename T> bool save(std::ostream& out, T& t, int tabs) {
	out << "{\n";
	SaveObject serializer(out, tabs + 1);
	serialize(serializer, t); // serialize should be defined for type T
	out << "\n";
	for (int i = 0; i < tabs; ++i) out << '\t';
	out << '}';
	return !out.fail();
}
template <typename T> int save_object_to_stream(T& t, std::ostream& out) {
	if (!json::save(out, t, 0))
		return JSON_FAIL;
	out << "\n";
	return JSON_OK;
}

template <typename T, typename A> 
int save_object_to_stream(std::vector<T, A>& t, std::ostream & out) {
	if (!json::save_container(out, t.begin(), t.end(), 0))
		return JSON_FAIL;
	out << "\n";
	return JSON_OK;
}

// serialize single object
template <typename T> 
int save_object_to_file(const char* filename, T& t) {
	try {
		std::ofstream out(filename);
		return json::save_object_to_stream(t, out);
	}
	catch (std::exception& e) {
		GLW_UNUSED(e);
		LOG_JSON_ERROR("saving json (%s) failed, error: %s", filename, e.what());
		return JSON_FAIL;
	}
	return JSON_OK;
}
} // namespace json

#endif // _GLW_JSON_
