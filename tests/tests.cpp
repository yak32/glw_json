#include "../glw_json.h"
#include "src/gtest-all.cc"
#include "src/gtest_main.cc"

#include <sstream>

using namespace std;
using namespace json;

struct empty {};
template <typename T> bool serialize(T& t, empty& e) {
	return true;
}

TEST(EmptyObject, LoadEmptyJSON) {
	const char* json_str = "{}";
	empty e;
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, e));
}
TEST(EmptyObject, LoadEmptyJSONTwoBreaks) {
	const char* json_str = "{\n\n}";
	empty e;
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, e));
}
TEST(EmptyObject, LoadEmptyJSONTwoTabs) {
	const char* json_str = "{		}";
	empty e;
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, e));
}
TEST(EmptyObject, LoadEmptyJSONTwoTabsTwoBreaksAtTheEnd) {
	const char* json_str = "{		}\n\n";
	empty e;
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, e));
}
TEST(EmptyObject, SaveEmptyJSON) {
	stringstream ss;
	empty e;
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
	EXPECT_FALSE(JSON_OK == load_object_from_string(json_str, v));
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
	EXPECT_TRUE(JSON_OK == load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val1 == 1);
	EXPECT_TRUE(v.val2 == 1.1f);
	EXPECT_TRUE(v.val3.size() == 1);
	EXPECT_TRUE(v.val3[0].val1 == 1);
	EXPECT_TRUE(v.val3[0].val2 == 1.1f);
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
