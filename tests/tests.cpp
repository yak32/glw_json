#include "../glw_json.h"
#include "src/gtest-all.cc"
#include "src/gtest_main.cc"

#include <sstream>

using namespace std;

struct empty{};
template<typename T> bool serialize(T& t, empty& e){
	return true;
}

TEST(EmptyObject, LoadEmptyJSON){
	const char* json_str = "{}";
	empty e;
  	EXPECT_TRUE(json::load_object_from_string(json_str, e));
}
TEST(EmptyObject, LoadEmptyJSONTwoBreaks){
	const char* json_str = "{\n\n}";
	empty e;
	EXPECT_TRUE(json::load_object_from_string(json_str, e));
}
TEST(EmptyObject, LoadEmptyJSONTwoTabs){
	const char* json_str = "{\t\t}";
	empty e;
	EXPECT_TRUE(json::load_object_from_string(json_str, e));
}
TEST(EmptyObject, LoadEmptyJSONTwoTabsTwoBreaksAtTheEnd){
	const char* json_str = "{\t\t}\n\n";
	empty e;
	EXPECT_TRUE(json::load_object_from_string(json_str, e));
}
TEST(EmptyObject, SaveEmptyJSON){
	stringstream ss;
	empty e;
	EXPECT_TRUE(json::save_object_to_stream(e, ss));
	EXPECT_TRUE(ss.str() == "{\n\n}\n");
}

struct one_int_var{
	int val;
};
template<typename T> bool serialize(T& t, one_int_var& v){
	return SERIALIZE(val);
}

TEST(OneVar, LoadStructWithOneIntVariable){
	one_int_var v;
	const char* json_str = "{\n"
						   "\t\"val\": 1\n"
						   "}\n";
	EXPECT_TRUE(json::load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == 1);
}
TEST(OneVar, SaveStructWithOneIntVariable){
	stringstream ss;
	one_int_var v; v.val = 1;
	EXPECT_TRUE(json::save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
						    "\t\"val\": 1\n"
						    "}\n");
}
TEST(OneVar, LoadStructWithOneIntVariable_Float){
	one_int_var v;
	const char* json_str = "{\n"
		"\t\"val\": 1.0\n"
		"}\n";
	EXPECT_FALSE(json::load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneIntVariable_IntWithSpace){
	one_int_var v;
	const char* json_str = "{\n"
		"\t\"val\": 1\t5\n"
		"}\n";
	EXPECT_FALSE(json::load_object_from_string(json_str, v));
}

struct one_float_var{
	float val;
};
template<typename T> bool serialize(T& t, one_float_var& v){
	return SERIALIZE(val);
}

TEST(OneVar, LoadStructWithOneFloatVariable){
	one_float_var v;
	const char* json_str = "{\n"
						   "\t\"val\": 1.1\n"
						   "}\n";
	EXPECT_TRUE(json::load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == 1.1f);
}
TEST(OneVar, SaveStructWithOneFloatVariable){
	stringstream ss;
	one_float_var v; v.val = 1.1f;
	EXPECT_TRUE(json::save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
						    "\t\"val\": 1.1\n"
						    "}\n");
}
TEST(OneVar, LoadStructWithOneFloatVariable_Bool){
	one_float_var v;
	const char* json_str = "{\n"
		"\t\"val\": false\n"
		"}\n";
	EXPECT_FALSE(json::load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneFloatVariable_FloatWithSpace){
	one_float_var v;
	const char* json_str = "{\n"
		"\t\"val\": 1.1\t5\n"
		"}\n";
	EXPECT_FALSE(json::load_object_from_string(json_str, v));
}


struct one_bool_var{
	bool val;
};
template<typename T> bool serialize(T& t, one_bool_var& v){
	return SERIALIZE(val);
}

TEST(OneVar, LoadStructWithOneBoolVariable){
	one_bool_var v;
	const char* json_str = "{\n"
		"\t\"val\": false\n"
		"}\n";
	EXPECT_TRUE(json::load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == false);
}
TEST(OneVar, LoadStructWithOneBoolVariable_true){
	one_bool_var v;
	const char* json_str = "{\n"
		"\t\"val\": true\n"
		"}\n";
	EXPECT_TRUE(json::load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == true);
}
TEST(OneVar, SaveStructWithOneBoolVariable){
	stringstream ss;
	one_bool_var v; v.val = true;
	EXPECT_TRUE(json::save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
		"\t\"val\": true\n"
		"}\n");
}
TEST(OneVar, SaveStructWithOneBoolVariable_false){
	stringstream ss;
	one_bool_var v; v.val = false;
	EXPECT_TRUE(json::save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
		"\t\"val\": false\n"
		"}\n");
}
TEST(OneVar, LoadStructWithOneBoolVariable_Bool){
	one_bool_var v;
	const char* json_str = "{\n"
		"\t\"val\": 1.1\n"
		"}\n";
	EXPECT_FALSE(json::load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneBoolVariable_BoolWithSpace){
	one_bool_var v;
	const char* json_str = "{\n"
		"\t\"val\": false\t5\n"
		"}\n";
	EXPECT_FALSE(json::load_object_from_string(json_str, v));
}


struct one_string_var{
	string val;
};
template<typename T> bool serialize(T& t, one_string_var& v){
	return SERIALIZE(val);
}

TEST(OneVar, LoadStructWithOneStringVariable){
	one_string_var v;
	const char* json_str = "{\n"
		"\t\"val\": \"Simple string\"\n"
		"}\n";
	EXPECT_TRUE(json::load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == "Simple string");
}
TEST(OneVar, SaveStructWithOneStringVariable){
	stringstream ss;
	one_string_var v; v.val = "Simple string";
	EXPECT_TRUE(json::save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
		"\t\"val\": \"Simple string\"\n"
		"}\n");
}
TEST(OneVar, LoadStructWithOneStringVariable_Int){
	one_string_var v;
	const char* json_str = "{\n"
		"\t\"val\": 1\n"
		"}\n";
	EXPECT_FALSE(json::load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneStringVariable_StringWithSpace){
	one_string_var v;
	const char* json_str = "{\n"
		"\t\"val\": \"Simple string\"\t5\n"
		"}\n";
	EXPECT_FALSE(json::load_object_from_string(json_str, v));
}
TEST(OneVar, LoadStructWithOneStringVariable_StringBraces){
	one_string_var v;
	const char* json_str = "{\n"
		"\t\"val\": \"Simple {} string\"\n"
		"}\n";
	EXPECT_TRUE(json::load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == "Simple {} string");
}
TEST(OneVar, LoadStructWithOneStringVariable_NoClosingQuote){
	one_string_var v;
	const char* json_str = "{\n"
		"\t\"val\": \"Simple string\n"
		"}\n";
	EXPECT_FALSE(json::load_object_from_string(json_str, v));
}

// ************************** arrays **************************************

struct array_int_var{
	std::vector<int> val;
};
template<typename T> bool serialize(T& t, array_int_var& v){
	return SERIALIZE(val);
}

TEST(ArrayVar, LoadStructWithArrayIntVariable){
	array_int_var v;
	const char* json_str = "{\n"
		"\t\"val\": [1 , 2 , 3]\n"
		"}\n";
	EXPECT_TRUE(json::load_object_from_string(json_str, v));
	EXPECT_TRUE(v.val == std::vector<int>({1,2,3}));
}
TEST(ArrayVar, SaveStructWithArrayIntVariable){
	stringstream ss;
	array_int_var v; v.val = { 1, 2, 3 };
	EXPECT_TRUE(json::save_object_to_stream(v, ss));
	EXPECT_TRUE(ss.str() == "{\n"
		"\t\"val\": [1,2,3]\n"
		"}\n");
}
TEST(ArrayVar, LoadStructWithArrayIntVariable_Float){
	array_int_var v;
	const char* json_str = "{\n"
		"\t\"val\": 1.0\n"
		"}\n";
	EXPECT_FALSE(json::load_object_from_string(json_str, v));
}
TEST(ArrayVar, LoadStructWithArrayIntVariable_FloatArray){
	array_int_var v;
	const char* json_str = "{\n"
		"\t\"val\": [1.1, 2.2, 3.3]\n"
		"}\n";
	EXPECT_FALSE(json::load_object_from_string(json_str, v));
}
TEST(ArrayVar, LoadStructWithArrayIntVariable_IntWithSpace){
	array_int_var v;
	const char* json_str = "{\n"
		"\t\"val\": [1\t2]\n"
		"}\n";
	EXPECT_FALSE(json::load_object_from_string(json_str, v));
}
TEST(ArrayVar, LoadStructWithArrayIntVariable_WithBraces){
	array_int_var v;
	const char* json_str = "{\n"
		"\t\"val\": [1{}, 2}]\n"
		"}\n";
	EXPECT_FALSE(json::load_object_from_string(json_str, v));
}
//struct array_float_var{
//	float val;
//};
//template<typename T> bool serialize(T& t, array_float_var& v){
//	return SERIALIZE(val);
//}
//
//TEST(ArrayVar, LoadStructWithArrayFloatVariable){
//	array_float_var v;
//	const char* json_str = "{\n"
//		"\t\"val\": 1.1\n"
//		"}\n";
//	EXPECT_TRUE(json::load_object_from_string(json_str, v));
//	EXPECT_TRUE(v.val == 1.1f);
//}
//TEST(ArrayVar, SaveStructWithArrayFloatVariable){
//	stringstream ss;
//	array_float_var v; v.val = 1.1f;
//	EXPECT_TRUE(json::save_object_to_stream(v, ss));
//	EXPECT_TRUE(ss.str() == "{\n"
//		"\t\"val\": 1.1\n"
//		"}\n");
//}
//TEST(ArrayVar, LoadStructWithArrayFloatVariable_Bool){
//	array_float_var v;
//	const char* json_str = "{\n"
//		"\t\"val\": false\n"
//		"}\n";
//	EXPECT_FALSE(json::load_object_from_string(json_str, v));
//}
//TEST(ArrayVar, LoadStructWithArrayFloatVariable_FloatWithSpace){
//	array_float_var v;
//	const char* json_str = "{\n"
//		"\t\"val\": 1.1\t5\n"
//		"}\n";
//	EXPECT_FALSE(json::load_object_from_string(json_str, v));
//}
//
//
//struct array_bool_var{
//	bool val;
//};
//template<typename T> bool serialize(T& t, array_bool_var& v){
//	return SERIALIZE(val);
//}
//
//TEST(ArrayVar, LoadStructWithArrayBoolVariable){
//	array_bool_var v;
//	const char* json_str = "{\n"
//		"\t\"val\": false\n"
//		"}\n";
//	EXPECT_TRUE(json::load_object_from_string(json_str, v));
//	EXPECT_TRUE(v.val == false);
//}
//TEST(ArrayVar, SaveStructWithArrayBoolVariable){
//	stringstream ss;
//	array_bool_var v; v.val = true;
//	EXPECT_TRUE(json::save_object_to_stream(v, ss));
//	EXPECT_TRUE(ss.str() == "{\n"
//		"\t\"val\": true\n"
//		"}\n");
//}
//TEST(ArrayVar, LoadStructWithArrayBoolVariable_Bool){
//	array_bool_var v;
//	const char* json_str = "{\n"
//		"\t\"val\": 1.1\n"
//		"}\n";
//	EXPECT_FALSE(json::load_object_from_string(json_str, v));
//}
//TEST(ArrayVar, LoadStructWithArrayBoolVariable_BoolWithSpace){
//	array_bool_var v;
//	const char* json_str = "{\n"
//		"\t\"val\": false\t5\n"
//		"}\n";
//	EXPECT_FALSE(json::load_object_from_string(json_str, v));
//}
//
//
//struct array_string_var{
//	string val;
//};
//template<typename T> bool serialize(T& t, array_string_var& v){
//	return SERIALIZE(val);
//}
//
//TEST(ArrayVar, LoadStructWithArrayStringVariable){
//	array_string_var v;
//	const char* json_str = "{\n"
//		"\t\"val\": \"Simple string\"\n"
//		"}\n";
//	EXPECT_TRUE(json::load_object_from_string(json_str, v));
//	EXPECT_TRUE(v.val == "Simple string");
//}
//TEST(ArrayVar, SaveStructWithArrayStringVariable){
//	stringstream ss;
//	array_string_var v; v.val = "Simple string";
//	EXPECT_TRUE(json::save_object_to_stream(v, ss));
//	EXPECT_TRUE(ss.str() == "{\n"
//		"\t\"val\": \"Simple string\"\n"
//		"}\n");
//}
//TEST(ArrayVar, LoadStructWithArrayStringVariable_Int){
//	array_string_var v;
//	const char* json_str = "{\n"
//		"\t\"val\": 1\n"
//		"}\n";
//	EXPECT_FALSE(json::load_object_from_string(json_str, v));
//}
//TEST(ArrayVar, LoadStructWithArrayStringVariable_StringWithSpace){
//	array_string_var v;
//	const char* json_str = "{\n"
//		"\t\"val\": \"Simple string\"\t5\n"
//		"}\n";
//	EXPECT_FALSE(json::load_object_from_string(json_str, v));
//}
//TEST(ArrayVar, LoadStructWithArrayStringVariable_StringBraces){
//	array_string_var v;
//	const char* json_str = "{\n"
//		"\t\"val\": \"Simple {} string\"\n"
//		"}\n";
//	EXPECT_TRUE(json::load_object_from_string(json_str, v));
//	EXPECT_TRUE(v.val == "Simple {} string");
//}
//TEST(ArrayVar, LoadStructWithArrayStringVariable_NoClosingQuote){
//	array_string_var v;
//	const char* json_str = "{\n"
//		"\t\"val\": \"Simple string\n"
//		"}\n";
//	EXPECT_FALSE(json::load_object_from_string(json_str, v));
//}
//
//
//
//
