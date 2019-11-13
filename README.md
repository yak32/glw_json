# glw_json  ![](https://github.com/yak32/glw_json/workflows/status/badge.svg) [![Coverage Status](https://coveralls.io/repos/github/yak32/glw_json/badge.svg)](https://coveralls.io/github/yak32/glw_json)
Header-only, cross-platform and compact json serialization for C++ with no memory allocations.

# Usage
Just drop the header (glw_json.h) into your C++ project and include it into a source file

```C++
#include "glw_json.h"
```

# License
Licensed under [BSD](https://opensource.org/licenses/BSD-2-Clause) to simplify the usage.

### How to build and run tests
```
git clone https://github.com/yak32/glw_json.git
cd glw_json
mkdir build
cd build
cmake ..
cmake --build . --target install
 ./../install/tests
```
(use Git Bash on Windows)

### Example
```c++
#include "glw_json.h"

using namespace json;

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
	if (load_object_from_file("test.json", v) != JSON_OK)
		return 0;

	if (save_object_to_file("test2.json", v) != JSON_OK)
		return 0;

	return 1;
}
```

To avoid hash maps with allocations, values should be serialized in alphabetical order.
BTW, initial implementation with hash map was 2x times slower (for average sized json object with around 50 properties)
With Sublime Text 2/3: select everything inside serialize() and press F9 - it will sort properties automatically.

### Dependencies
 STL, c-runtime.

### Performance
JSON loading - allocation-free parsing, N Log(N) performance where N is number of properties in a JSON object.
   Parsing speed is comparable to RapidJSON, saving is slower.

Saving to JSON  - linear performance, std::ofstream is used to save data ( some allocations )

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

struct object_pointer_in_object {
	int val1;
	float val2;
	obj_array_var1* val3;
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

template <typename T> bool serialize(T& t, object_pointer_in_object& v) {
	bool b = true;
	b &= SERIALIZE(val1);
	b &= SERIALIZE(val2);
	b &= SERIALIZE(val3);
	return b;
}

int main(){
	vec3 v;

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

	object_pointer_in_object obj_in_obj;
	if (JSON_OK != load_object_from_file("object in object test", obj_in_obj))
		printf("failed");

	return 1;
}
```

