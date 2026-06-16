#include "../glw_json.h"
#include "src/gtest-all.cc"
#include "src/gtest_main.cc"
#include "gtest/gtest.h"

#include <sstream>      // std::numeric_limits

using namespace std;
using namespace json;

struct empty_obj {};
template <typename T> bool serialize(T& t, empty_obj& e) {
	return true;
}

TEST(EmptyObject, LoadEmptyJSON) {
	const char* json_str = "{}";
	empty_obj e;
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, e));
}
TEST(EmptyObject, LoadEmptyJSONTwoBreaks) {
	const char* json_str = "{\n\n}";
	empty_obj e;
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, e));
}
TEST(EmptyObject, LoadEmptyJSONTwoTabs) {
	const char* json_str = "{		}";
	empty_obj e;
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, e));
}
TEST(EmptyObject, LoadEmptyJSONTwoTabsTwoBreaksAtTheEnd) {
	const char* json_str = "{		}\n\n";
	empty_obj e;
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, e));
}
TEST(EmptyObject, SaveEmptyJSON) {
	stringstream ss;
	empty_obj e;
	EXPECT_TRUE(JSON_OK == save_object_to_stream(e, ss));
	EXPECT_TRUE(ss.str() == "{\n\n}\n");
}

struct one_int_var {
	int val;
};
template <typename T> bool serialize(T& t, one_int_var& v) {
	return SERIALIZE(val);
}

TEST(OneVar, LoadStructWithOneIntVariable) {
	one_int_var v;
	const char* json_str = "{\n"
						   "	\"val\": 1\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == 1);
}
TEST(OneVar, SaveStructWithOneIntVariable) {
	stringstream ss;
	one_int_var v;
	v.val = 1;
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val\": 1\n"
							"}\n");
}
struct one_uint_var {
	unsigned int val;
};
template <typename T> bool serialize(T& t, one_uint_var& v) {
	return SERIALIZE(val);
}
TEST(OneVar, LoadStructWithOneUIntVariable) {
	one_uint_var v;
	const char* json_str = "{\n"
						   "	\"val\": 1\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == 1);
}
TEST(OneVar, SaveStructWithOneUIntVariable) {
	stringstream ss;
	one_uint_var v;
	v.val = 1;
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val\": 1\n"
							"}\n");
}
TEST(OneVar, LoadStructWithOneHugeIntVariable) {
	one_int_var v;
	const char* json_str = "{\n"
						   "	\"val\": 12345678901234567890\n"
						   "}\n";
	EXPECT_TRUE(2 == load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneHugeUIntVariable) {
	one_uint_var v;
	const char* json_str = "{\n"
						   "	\"val\": 12345678901234567890\n"
						   "}\n";
	EXPECT_TRUE(2 == load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneNegativeUIntVariable) {
	one_uint_var v;
	const char* json_str = "{\n"
						   "	\"val\": -1\n"
						   "}\n";
	EXPECT_TRUE(2 == load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneIntVariable_Float) {
	one_int_var v;
	const char* json_str = "{\n"
						   "	\"val\": 1.0\n"
						   "}\n";
	EXPECT_TRUE(2 == load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneIntVariable_IntWithSpace) {
	one_int_var v;
	const char* json_str = "{\n"
						   "	\"val\": 1	5\n"
						   "}\n";
	EXPECT_TRUE(2 == load_object_from_string(json_str, v));
}

struct one_float_var {
	float val;
};
template <typename T> bool serialize(T& t, one_float_var& v) {
	return SERIALIZE(val);
}

TEST(OneVar, LoadStructWithOneFloatVariable) {
	one_float_var v;
	const char* json_str = "{\n"
						   "	\"val\": 1.1\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == 1.1f);
}
TEST(OneVar, SaveStructWithOneFloatVariable) {
	stringstream ss;
	one_float_var v;
	v.val = 1.1f;
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val\": 1.1\n"
							"}\n");
}
TEST(OneVar, LoadStructWithOneHugeFloatVariable_Bool) {
	one_float_var v;
	const char* json_str = "{\n"
						   "	\"val\": 1.18973e+4932\n"
						   "}\n";
	EXPECT_TRUE(2 == load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneFloatVariable_Bool) {
	one_float_var v;
	const char* json_str = "{\n"
						   "	\"val\": false\n"
						   "}\n";
	EXPECT_TRUE(2 == load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneFloatVariable_FloatWithSpace) {
	one_float_var v;
	const char* json_str = "{\n"
						   "	\"val\": 1.1	5\n"
						   "}\n";
	EXPECT_TRUE(2 == load_object_from_string(json_str, v));
}

struct one_bool_var {
	bool val;
};
template <typename T> bool serialize(T& t, one_bool_var& v) {
	return SERIALIZE(val);
}

TEST(OneVar, LoadStructWithOneBoolVariable) {
	one_bool_var v;
	const char* json_str = "{\n"
						   "	\"val\": false\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == false);
}
TEST(OneVar, LoadStructWithOneBoolVariable_true) {
	one_bool_var v;
	const char* json_str = "{\n"
						   "	\"val\": true\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == true);
}
TEST(OneVar, SaveStructWithOneBoolVariable) {
	stringstream ss;
	one_bool_var v;
	v.val = true;
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val\": true\n"
							"}\n");
}
TEST(OneVar, SaveStructWithOneBoolVariable_false) {
	stringstream ss;
	one_bool_var v;
	v.val = false;
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val\": false\n"
							"}\n");
}
TEST(OneVar, LoadStructWithOneBoolVariable_Bool) {
	one_bool_var v;
	const char* json_str = "{\n"
						   "	\"val\": 1.1\n"
						   "}\n";
	EXPECT_TRUE(2 == load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneBoolVariable_BoolWithSpace) {
	one_bool_var v;
	const char* json_str = "{\n"
						   "	\"val\": false	5\n"
						   "}\n";
	EXPECT_TRUE(2 == load_object_from_string(json_str, v));
}

struct one_string_var {
	string val;
};
template <typename T> bool serialize(T& t, one_string_var& v) {
	return SERIALIZE(val);
}

TEST(OneVar, LoadStructWithOneStringVariable) {
	one_string_var v;
	const char* json_str = "{\n"
						   "	\"val\": \"Simple string\"\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == "Simple string");
}
TEST(OneVar, SaveStructWithOneStringVariable) {
	stringstream ss;
	one_string_var v;
	v.val = "Simple string";
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val\": \"Simple string\"\n"
							"}\n");
}
TEST(OneVar, LoadStructWithOneStringVariable_Int) {
	one_string_var v;
	const char* json_str = "{\n"
						   "	\"val\": 1\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneStringVariable_StringWithSpace) {
	one_string_var v;
	const char* json_str = "{\n"
						   "	\"val\": \"Simple string\"	5\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneStringVariable_StringBraces) {
	one_string_var v;
	const char* json_str = "{\n"
						   "	\"val\": \"Simple {} string\"\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == "Simple {} string");
}
TEST(OneVar, LoadStructWithOneStringVariable_NoClosingQuote) {
	one_string_var v;
	const char* json_str = "{\n"
						   "	\"val\": \"Simple string\n"
						   "}\n";
	EXPECT_TRUE(3 == load_object_from_string(json_str, v));
}

// ************************** arrays **************************************

struct array_int_var {
	std::vector<int> val;
};
template <typename T> bool serialize(T& t, array_int_var& v) {
	return SERIALIZE(val);
}

TEST(ArrayVar, LoadStructWithArrayIntVariable) {
	array_int_var v;
	const char* json_str = "{\n"
						   "	\"val\": [1 , 2 , 3]\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == std::vector<int>({1, 2, 3}));
}
TEST(ArrayVar, SaveStructWithArrayIntVariable) {
	stringstream ss;
	array_int_var v;
	v.val = {1, 2, 3};
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val\": [1,2,3]\n"
							"}\n");
}
TEST(ArrayVar, LoadStructWithArrayIntVariable_Float) {
	array_int_var v;
	const char* json_str = "{\n"
						   "	\"val\": 1.0\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}
TEST(ArrayVar, LoadStructWithArrayIntVariable_FloatArray) {
	array_int_var v;
	const char* json_str = "{\n"
						   "	\"val\": [1.1, 2.2, 3.3]\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}
TEST(ArrayVar, LoadStructWithArrayIntVariable_IntWithSpace) {
	array_int_var v;
	const char* json_str = "{\n"
						   "	\"val\": [1	2]\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}
TEST(ArrayVar, LoadStructWithArrayIntVariable_WithBraces) {
	array_int_var v;
	const char* json_str = "{\n"
						   "	\"val\": [1{}, 2}]\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}

//**************************** float array

struct array_float_var {
	std::vector<float> val;
};
template <typename T> bool serialize(T& t, array_float_var& v) {
	return SERIALIZE(val);
}

TEST(ArrayVar, LoadStructWithArrayFloatVariable) {
	array_float_var v;
	const char* json_str = "{\n"
						   "	\"val\": [1.1 , 2.2 , 3.3]\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == std::vector<float>({1.1f, 2.2f, 3.3f}));
}
TEST(ArrayVar, SaveStructWithArrayFloatVariable) {
	stringstream ss;
	array_float_var v;
	v.val = {1.1f, 2.2f, 3.3f};
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val\": [1.1,2.2,3.3]\n"
							"}\n");
}
TEST(ArrayVar, LoadStructWithArrayFloatVariable_String) {
	array_float_var v;
	const char* json_str = "{\n"
						   "	\"val\": \"wrong value\"\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}
TEST(ArrayVar, LoadStructWithArrayFloatVariable_StringArray) {
	array_float_var v;
	const char* json_str = "{\n"
						   "	\"val\": [\"wrong value\", \"wrong value\", \"wrong value\"]\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}
TEST(ArrayVar, LoadStructWithArrayFloatVariable_IntWithSpace) {
	array_float_var v;
	const char* json_str = "{\n"
						   "	\"val\": [1	2]\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}
TEST(ArrayVar, LoadStructWithArrayFloatVariable_WithBraces) {
	array_float_var v;
	const char* json_str = "{\n"
						   "	\"val\": [1{}, 2}]\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}

//**************************** string array

struct array_string_var {
	std::vector<string> val;
};
template <typename T> bool serialize(T& t, array_string_var& v) {
	return SERIALIZE(val);
}

TEST(ArrayVar, LoadStructWithArrayStringVariable) {
	array_string_var v;
	const char* json_str = "{\n"
						   "	\"val\": [\"str1\" ,\"str2\", \"str3\"]\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == std::vector<string>({"str1", "str2", "str3"}));
}
TEST(ArrayVar, SaveStructWithArrayStringVariable) {
	stringstream ss;
	array_string_var v;
	v.val = {"str1", "str2", "str3"};
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val\": [\"str1\",\"str2\",\"str3\"]\n"
							"}\n");
}
TEST(ArrayVar, LoadStructWithArrayStringVariable_Int) {
	array_string_var v;
	const char* json_str = "{\n"
						   "	\"val\": 1\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}
TEST(ArrayVar, LoadStructWithArrayStringVariable_IntArray) {
	array_string_var v;
	const char* json_str = "{\n"
						   "	\"val\": [1, 2, 3]\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}
TEST(ArrayVar, LoadStructWithArrayStringVariable_IntWithSpace) {
	array_string_var v;
	const char* json_str = "{\n"
						   "	\"val\": [\"str1\"	2]\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}
TEST(ArrayVar, LoadStructWithArrayStringVariable_WithBraces) {
	array_string_var v;
	const char* json_str = "{\n"
						   "	\"val\": [\"str1\"{}, \"str2\"}]\n"
						   "}\n";
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}

//******************* embedded object

struct obj_var1 {
	int val1;
	float val2;
};

struct obj_var2 {
	int val1;
	float val2;
	obj_var1 val3;
};

template <typename T> bool serialize(T& t, obj_var1& v) {
	bool b = true;
	b &= SERIALIZE(val1);
	b &= SERIALIZE(val2);
	return b;
}
template <typename T> bool serialize(T& t, obj_var2& v) {
	bool b = true;
	b &= SERIALIZE(val1);
	b &= SERIALIZE(val2);
	b &= SERIALIZE(val3);
	return b;
}
TEST(ObjectInObject, LoadObjectInObject) {
	obj_var2 v;
	const char* json_str = "{\n"
						   "	\"val1\": 1,\n"
						   "	\"val2\": 1.1,\n"
						   "	\"val3\": {\n"
						   "		\"val1\": 1,\n"
						   "		\"val2\": 1.1\n"
						   "	}\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val1 == 1);
	EXPECT_TRUE(v.val2 == 1.1f);
	EXPECT_TRUE(v.val3.val1 == 1);
	EXPECT_TRUE(v.val3.val2 == 1.1f);
}
TEST(ObjectInObject, SaveObjectInObject) {
	stringstream ss;
	obj_var2 v;
	v.val1 = 1;
	v.val2 = 1.1f;
	v.val3.val1 = 1;
	v.val3.val2 = 1.1f;
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val1\": 1,\n"
							"	\"val2\": 1.1,\n"
							"	\"val3\": {\n"
							"		\"val1\": 1,\n"
							"		\"val2\": 1.1\n"
							"	}\n"
							"}\n");
}

//*******************  object array

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
TEST(ObjectArrayInObject, LoadObjectArrayInObject) {
	obj_array_var2 v;
	const char* json_str = "{\n"
						   "	\"val1\": 1,\n"
						   "	\"val2\": 1.1,\n"
						   "	\"val3\": [{\n"
						   "		\"val1\": 1,\n"
						   "		\"val2\": 1.1\n"
						   "	}]\n"
						   "}\n";
	int r = load_object_from_string(json_str, v);
	EXPECT_TRUE(JSON_OK == r);
	if (r == JSON_OK) {
		EXPECT_TRUE(v.val1 == 1);
		EXPECT_TRUE(v.val2 == 1.1f);
		EXPECT_TRUE(v.val3.size() == 1);
		EXPECT_TRUE(v.val3[0].val1 == 1);
		EXPECT_TRUE(v.val3[0].val2 == 1.1f);
	}
}
TEST(ObjectArrayInObject, SaveObjectArrayInObject) {
	stringstream ss;
	obj_array_var2 v;
	v.val1 = 1;
	v.val2 = 1.1f;
	v.val3.resize(1);
	v.val3[0].val1 = 1;
	v.val3[0].val2 = 1.1f;
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val1\": 1,\n"
							"	\"val2\": 1.1,\n"
							"	\"val3\": [{\n"
							"			\"val1\": 1,\n"
							"			\"val2\": 1.1\n"
							"		}]\n"
							"}\n");
}
TEST(ObjectArrayInObject, LoadObjectArray2InObject) {
	obj_array_var2 v;
	const char* json_str = "{\n"
						   "	\"val1\": 1,\n"
						   "	\"val2\": 1.1,\n"
						   "	\"val3\": [{\n"
						   "		\"val1\": 1,\n"
						   "		\"val2\": 1.1\n"
						   "	},{\n"
						   "		\"val1\": 2,\n"
						   "		\"val2\": 2.2\n"
						   "	}]\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val1 == 1);
	EXPECT_TRUE(v.val2 == 1.1f);
	EXPECT_TRUE(v.val3.size() == 2);
	EXPECT_TRUE(v.val3[0].val1 == 1);
	EXPECT_TRUE(v.val3[0].val2 == 1.1f);
	EXPECT_TRUE(v.val3[1].val1 == 2);
	EXPECT_TRUE(v.val3[1].val2 == 2.2f);
}
TEST(ObjectArrayInObject, SaveObjectArray2InObject) {
	stringstream ss;
	obj_array_var2 v;
	v.val1 = 1;
	v.val2 = 1.1f;
	v.val3.resize(2);
	v.val3[0].val1 = 1;
	v.val3[0].val2 = 1.1f;
	v.val3[1].val1 = 2;
	v.val3[1].val2 = 2.2f;
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val1\": 1,\n"
							"	\"val2\": 1.1,\n"
							"	\"val3\": [{\n"
							"			\"val1\": 1,\n"
							"			\"val2\": 1.1\n"
							"		},{\n"
							"			\"val1\": 2,\n"
							"			\"val2\": 2.2\n"
							"		}]\n"
							"}\n");
}

TEST(ObjectArrayInObject, LoadObjectArray2InObjectNoComma) {
	obj_array_var2 v;
	const char* json_str = "{\n"
						   "	\"val1\": 1,\n"
						   "	\"val2\": 1.1,\n"
						   "	\"val3\": [{\n"
						   "		\"val1\": 1,\n"
						   "		\"val2\": 1.1\n"
						   "	} {\n"
						   "		\"val1\": 2,\n"
						   "		\"val2\": 2.2\n"
						   "	}]\n"
						   "}\n";
	EXPECT_TRUE(load_object_from_string(json_str, v) == 7); // 7 - error line
}


//******************* embedded object (pointers)

struct pointer_obj_var2 {
	int val1;
	float val2;
	obj_var1* val3;
};
template <typename T> bool serialize(T& t, pointer_obj_var2& v) {
	bool b = true;
	b &= SERIALIZE(val1);
	b &= SERIALIZE(val2);
	b &= SERIALIZE(val3);
	return b;
}
TEST(ObjectPointerInObject, LoadObjectInObject) {
	pointer_obj_var2 v;
	const char* json_str = "{\n"
						   "	\"val1\": 1,\n"
						   "	\"val2\": 1.1,\n"
						   "	\"val3\": {\n"
						   "		\"val1\": 1,\n"
						   "		\"val2\": 1.1\n"
						   "	}\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val1 == 1);
	EXPECT_TRUE(v.val2 == 1.1f);
	EXPECT_TRUE(v.val3->val1 == 1);
	EXPECT_TRUE(v.val3->val2 == 1.1f);
}
TEST(ObjectPointerInObject, SaveObjectInObject) {
	stringstream ss;
	pointer_obj_var2 v;
	v.val1 = 1;
	v.val2 = 1.1f;
	v.val3 = new obj_var1;
	v.val3->val1 = 1;
	v.val3->val2 = 1.1f;
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val1\": 1,\n"
							"	\"val2\": 1.1,\n"
							"	\"val3\": {\n"
							"		\"val1\": 1,\n"
							"		\"val2\": 1.1\n"
							"	}\n"
							"}\n");
}

//*******************  object array of pointers

struct pointer_obj_array_var2 {
	int val1;
	float val2;
	vector<obj_array_var1*> val3;
};

template <typename T> bool serialize(T& t, pointer_obj_array_var2& v) {
	bool b = true;
	b &= SERIALIZE(val1);
	b &= SERIALIZE(val2);
	b &= SERIALIZE(val3);
	return b;
}
TEST(ObjectPointerArrayInObject, LoadObjectArrayInObject) {
	pointer_obj_array_var2 v;
	const char* json_str = "{\n"
						   "	\"val1\": 1,\n"
						   "	\"val2\": 1.1,\n"
						   "	\"val3\": [{\n"
						   "		\"val1\": 1,\n"
						   "		\"val2\": 1.1\n"
						   "	}]\n"
						   "}\n";
	int r = load_object_from_string(json_str, v);
	EXPECT_TRUE(JSON_OK == r);
	if (r == JSON_OK) {
		EXPECT_TRUE(v.val1 == 1);
		EXPECT_TRUE(v.val2 == 1.1f);
		EXPECT_TRUE(v.val3.size() == 1);
		EXPECT_TRUE(v.val3[0]->val1 == 1);
		EXPECT_TRUE(v.val3[0]->val2 == 1.1f);
	}
}
TEST(ObjectPointerArrayInObject, SaveObjectArrayInObject) {
	stringstream ss;
	pointer_obj_array_var2 v;
	v.val1 = 1;
	v.val2 = 1.1f;
	v.val3.resize(1);
	v.val3[0] = new obj_array_var1;
	v.val3[0]->val1 = 1;
	v.val3[0]->val2 = 1.1f;
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val1\": 1,\n"
							"	\"val2\": 1.1,\n"
							"	\"val3\": [{\n"
							"			\"val1\": 1,\n"
							"			\"val2\": 1.1\n"
							"		}]\n"
							"}\n");
}
TEST(ObjectPointerArrayInObject, LoadObjectArray2InObject) {
	pointer_obj_array_var2 v;
	const char* json_str = "{\n"
						   "	\"val1\": 1,\n"
						   "	\"val2\": 1.1,\n"
						   "	\"val3\": [{\n"
						   "		\"val1\": 1,\n"
						   "		\"val2\": 1.1\n"
						   "	},{\n"
						   "		\"val1\": 2,\n"
						   "		\"val2\": 2.2\n"
						   "	}]\n"
						   "}\n";
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val1 == 1);
	EXPECT_TRUE(v.val2 == 1.1f);
	EXPECT_TRUE(v.val3.size() == 2);
	EXPECT_TRUE(v.val3[0]->val1 == 1);
	EXPECT_TRUE(v.val3[0]->val2 == 1.1f);
	EXPECT_TRUE(v.val3[1]->val1 == 2);
	EXPECT_TRUE(v.val3[1]->val2 == 2.2f);
}
TEST(ObjectPointerArrayInObject, SaveObjectArray2InObject) {
	stringstream ss;
	pointer_obj_array_var2 v;
	v.val1 = 1;
	v.val2 = 1.1f;
	v.val3.resize(2);
	v.val3[0] = new obj_array_var1;
	v.val3[1] = new obj_array_var1;
	v.val3[0]->val1 = 1;
	v.val3[0]->val2 = 1.1f;
	v.val3[1]->val1 = 2;
	v.val3[1]->val2 = 2.2f;
	EXPECT_TRUE(JSON_OK == save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
							"	\"val1\": 1,\n"
							"	\"val2\": 1.1,\n"
							"	\"val3\": [{\n"
							"			\"val1\": 1,\n"
							"			\"val2\": 1.1\n"
							"		},{\n"
							"			\"val1\": 2,\n"
							"			\"val2\": 2.2\n"
							"		}]\n"
							"}\n");
}

TEST(ObjectPointerArrayInObject, LoadObjectArray2InObjectNoComma) {
	pointer_obj_array_var2 v;
	const char* json_str = "{\n"
						   "	\"val1\": 1,\n"
						   "	\"val2\": 1.1,\n"
						   "	\"val3\": [{\n"
						   "		\"val1\": 1,\n"
						   "		\"val2\": 1.1\n"
						   "	} {\n"
						   "		\"val1\": 2,\n"
						   "		\"val2\": 2.2\n"
						   "	}]\n"
						   "}\n";
	EXPECT_TRUE(load_object_from_string(json_str, v) == 7); // 7 - error line
}


// ************* PARSE_ANY: standard JSON with extra / out-of-order properties *************
// Mirrors real SOG (meta.json) and streamed-SOG (lod-meta.json) assets, which carry properties
// a reader struct doesn't consume ("asset", "environment", ...). Default options now parse these.

struct sog_means {
	std::vector<float> mins, maxs;
	std::vector<std::string> files;
};
// fields intentionally NOT in alphabetical order — PARSE_ANY looks up by name
template <typename T> bool serialize(T& t, sog_means& v) {
	SERIALIZE(mins);
	SERIALIZE(maxs);
	SERIALIZE(files);
	return true;
}
struct sog_meta {
	int version, count;
	sog_means means;
};
template <typename T> bool serialize(T& t, sog_meta& v) {
	SERIALIZE(version);
	SERIALIZE(count);
	SERIALIZE(means);
	return true;
}

TEST(ParseAny, SogMetaWithUnreadAssetAndExtraProps) {
	const char* json_str =
		"{\"version\":2,\"asset\":{\"generator\":\"splat-transform\"},\"count\":2442964,"
		"\"means\":{\"mins\":[-0.4,-0.6,-0.3],\"maxs\":[0.4,0.6,0.3],"
		"\"files\":[\"means_l.webp\",\"means_u.webp\"]},\"extra\":[1,2,3]}";
	sog_meta v;
	EXPECT_EQ(JSON_OK, load_object_from_string(json_str, v));
	EXPECT_EQ(2, v.version);
	EXPECT_EQ(2442964, v.count);
	EXPECT_EQ(3u, v.means.mins.size());
	EXPECT_FLOAT_EQ(-0.6f, v.means.mins[1]);
	EXPECT_EQ(2u, v.means.files.size());
	EXPECT_TRUE(v.means.files[0] == "means_l.webp");
}

struct ssog_manifest {
	std::vector<std::string> filenames;
	int lodLevels;
};
template <typename T> bool serialize(T& t, ssog_manifest& v) {
	SERIALIZE(filenames);
	SERIALIZE(lodLevels);
	return true;
}

TEST(ParseAny, SsogManifestWithNullEnvironmentAndUnreadTree) {
	const char* json_str =
		"{\"lodLevels\":3,\"environment\":null,"
		"\"filenames\":[\"0_0/meta.json\",\"1_0/meta.json\"],"
		"\"tree\":{\"bound\":{\"min\":[0,0,0],\"max\":[1,1,1]},\"children\":[]}}";
	ssog_manifest v;
	EXPECT_EQ(JSON_OK, load_object_from_string(json_str, v));
	EXPECT_EQ(3, v.lodLevels);
	EXPECT_EQ(2u, v.filenames.size());
	EXPECT_TRUE(v.filenames[1] == "1_0/meta.json");
}

struct two_ints {
	int a, b;
};
template <typename T> bool serialize(T& t, two_ints& v) {
	SERIALIZE(a);
	SERIALIZE(b);
	return true;
}

TEST(ParseAny, TrailingUnknownProperty) {
	const char* json_str = "{\"a\":1,\"b\":2,\"zzz\":99}";
	two_ints v;
	EXPECT_EQ(JSON_OK, load_object_from_string(json_str, v));
	EXPECT_EQ(1, v.a);
	EXPECT_EQ(2, v.b);
}
TEST(ParseAny, LeadingAndMiddleUnknownProperties) {
	const char* json_str = "{\"aaa\":7,\"a\":1,\"middle\":8,\"b\":2,\"zzz\":9}";
	two_ints v;
	EXPECT_EQ(JSON_OK, load_object_from_string(json_str, v));
	EXPECT_EQ(1, v.a);
	EXPECT_EQ(2, v.b);
}

// struct fields serialized out of alphabetical order — allowed under PARSE_ANY
struct unsorted_fields {
	int zebra, apple;
};
template <typename T> bool serialize(T& t, unsorted_fields& v) {
	SERIALIZE(zebra);
	SERIALIZE(apple);
	return true;
}
TEST(ParseAny, FieldsSerializedOutOfOrder) {
	const char* json_str = "{\"apple\":11,\"zebra\":22}";
	unsorted_fields v;
	EXPECT_EQ(JSON_OK, load_object_from_string(json_str, v));
	EXPECT_EQ(22, v.zebra);
	EXPECT_EQ(11, v.apple);
}

TEST(ParseAny, MalformedValueStillErrors) {
	// extra props are fine, but a bad value is still an error (string where int expected)
	const char* json_str = "{\"a\":1,\"x\":5,\"b\":\"oops\"}";
	two_ints v;
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
}
TEST(ParseAny, AbsentFieldResets) {
	const char* json_str = "{\"a\":42,\"other\":1}";
	two_ints v;
	v.b = 123;
	EXPECT_EQ(JSON_OK, load_object_from_string(json_str, v));
	EXPECT_EQ(42, v.a);
	EXPECT_EQ(0, v.b); // RESET_IF_ABSENT
}

// ************* fast sorted mode (PARSE_ANY cleared) keeps its strict contract *************
TEST(FastSortedMode, CleanSortedJsonLoads) {
	const char* json_str = "{\"a\":1,\"b\":2}";
	two_ints v;
	EXPECT_EQ(JSON_OK, load_object_from_string(json_str, v, (size_t)-1, RESET_IF_ABSENT));
	EXPECT_EQ(1, v.a);
	EXPECT_EQ(2, v.b);
}
TEST(FastSortedMode, ExtraPropertyIsRejected) {
	const char* json_str = "{\"a\":1,\"b\":2,\"c\":3}";
	two_ints v;
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v, (size_t)-1, RESET_IF_ABSENT));
}

// Mirrors the "reading a subset of a larger JSON" example in README.md — keep them in sync.
struct readme_point {
	float x, y;
};
template <typename T> bool serialize(T& t, readme_point& v) {
	return SERIALIZE(x) && SERIALIZE(y);
}
TEST(Readme, SubsetOfLargerJson) {
	const char* json = R"({"label":"p0","x":1.5,"y":-2.0,"z":9.0})";
	readme_point pt;
	EXPECT_EQ(JSON_OK, load_object_from_string(json, pt));
	EXPECT_FLOAT_EQ(1.5f, pt.x);
	EXPECT_FLOAT_EQ(-2.0f, pt.y);
}

// ******* nested containers must not accumulate across sibling array elements (regression) *******
// load_container reused one element value and appended into the destination, so a struct's own
// vectors — and nested vectors-of-structs — leaked from one sibling into the next (later siblings
// grew to contain the earlier siblings' contents). This corrupted, e.g., octree manifests.
struct na_inner {
	std::vector<int> vals;
};
template <typename T> bool serialize(T& t, na_inner& v) {
	return SERIALIZE(vals);
}
struct na_outer {
	std::vector<na_inner> items;
};
template <typename T> bool serialize(T& t, na_outer& v) {
	return SERIALIZE(items);
}
struct na_doc {
	std::vector<na_outer> groups;
};
template <typename T> bool serialize(T& t, na_doc& v) {
	return SERIALIZE(groups);
}

TEST(NestedArray, SiblingsDoNotAccumulate) {
	const char* json_str = "{\"groups\":["
						   "{\"items\":[{\"vals\":[1]},{\"vals\":[2]}]},"
						   "{\"items\":[{\"vals\":[3]}]}"
						   "]}";
	na_doc d;
	EXPECT_EQ(JSON_OK, load_object_from_string(json_str, d));

	ASSERT_EQ(2u, d.groups.size());
	// Second group must hold only its own item — not the first group's items appended on top.
	ASSERT_EQ(2u, d.groups[0].items.size());
	ASSERT_EQ(1u, d.groups[1].items.size());

	// Each leaf vector keeps exactly its own value (no accumulation across reused element).
	EXPECT_EQ(std::vector<int>({1}), d.groups[0].items[0].vals);
	EXPECT_EQ(std::vector<int>({2}), d.groups[0].items[1].vals);
	EXPECT_EQ(std::vector<int>({3}), d.groups[1].items[0].vals);
}

// The destination must be replaced, not appended to, when it already holds data.
TEST(NestedArray, LoadReplacesExistingVector) {
	array_int_var v;
	v.val = {7, 8, 9}; // pre-populate
	const char* json_str = "{\n	\"val\": [1, 2, 3]\n}\n";
	EXPECT_EQ(JSON_OK, load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == std::vector<int>({1, 2, 3}));
}
