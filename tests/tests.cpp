#include "../glw_json.h"
#include "src/gtest-all.cc"
#include "src/gtest_main.cc"

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


