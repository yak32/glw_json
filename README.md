# glw_json
Single-file public domain compact and fast json serialization for C++ with no-alloc parsing.

### Example
```c++
#include "glw_json.h"

using namespace json;
using namespace std;

struct vec3{
  float x,y,z;
};

template<typename T>
bool serialize(T& t, vec3& v){
	SERIALIZE(x);
	SERIALIZE(y);
	SERIALIZE(z);
	return true;
}

int main(){
	vec3 v;

	// simple objects
	if (json::load_object_from_file("test.json", v) != JSON_OK)
		return 0;

	if (json::save_object_to_file("test2.json", v) != JSON_OK)
		return 0;

	return 1;
}
```

To avoid hash maps with allocations, values should be serialized in alphabetical order.
BTW, realization with hash map was 2x times slower (for avarage sized json object with around 50 properties)
With Sublime Text 2/3: select everything inside serialize() and press F9 - it will sort properties automatically.

## FAQ

The license?
This library is in the public domain. You can do what you want, but I would appreciate attribution.

### Dependencies
 STL, c-runtime.

### Performance
JSON loading - allocation-free parsing, N Log(N) performance where N is number of properties in JSON object.
   Parsing speed is comparable to RapidJSON, saving is slower.

JSON saving - linear performance, std::ofstream is used to save data ( some allocations )

### Tests
 Run cmake on CMakeLists.txt in tests folder. Tests require C++11 support to compile (glw_json.h doesn't).

### Compartibility
  Tested with Visual Studio 2013, 2015, GCC 4.3.6 to GCC 7.0 (HEAD), Clang 3.0 to 3.9.0 (trunc), compartible with C++98, C++11 and C++14.

### More examples
```c++
#include "glw_json.h"
#include <sstream>

using namespace json;
using namespace std;

struct vec3{
  float x,y,z;
};

template<typename T>
bool serialize(T& t, vec3& v){
	SERIALIZE(x);
	SERIALIZE(y);
	SERIALIZE(z);
	return true;
}

struct array_int_var {
	std::vector<int> val;
};
template <typename T> bool serialize(T& t, array_int_var& v) {
	return SERIALIZE(val);
}

struct obj_array_var1 {
	int val1;
	float val2;
};

struct obj_array_var2 {
	int val1;
	float val2;
	vector<obj_array_var1> val3;
};

template <typename T> bool serialize(T& t, obj_array_var1& v) {
	bool b = true;
	b &= SERIALIZE(val1);
	b &= SERIALIZE(val2);
	return b;
}
template <typename T> bool serialize(T& t, obj_array_var2& v) {
	bool b = true;
	b &= SERIALIZE(val1);
	b &= SERIALIZE(val2);
	b &= SERIALIZE(val3);
	return b;
}

int main(){
	vec3 v;

	// simple objects
	if (json::load_object_from_file("test.json", v) != JSON_OK)
		return 0;

	if (json::save_object_to_file("test2.json", v) != JSON_OK)
		return 0;

	// array
	stringstream ss;
	array_int_var av;
	av.val = {1, 2, 3};

	if (save_object_to_stream(av, ss) != JSON_OK )
		printf("failed");

	// array of objects
	stringstream sss;
	obj_array_var2 oav;
	oav.val1 = 1;
	oav.val2 = 1.1f;
	oav.val3.resize(1);
	oav.val3[0].val1 = 1;
	oav.val3[0].val2 = 1.1f;

	if (JSON_OK != save_object_to_stream(oav, sss))
		printf("failed");

	return 1;
}
```

