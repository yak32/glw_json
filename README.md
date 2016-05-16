# glw_json
Single-file public domain compact json serialization for C/C++.
~380 lines of code

### Example
```c++
#include "../glw_json.h"

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
	json::load_object_from_file("test.json", v);
	json::save_object_to_file("test2.json", v);
	return 1;
}
```

To avoid hash maps with allocations, values should be serialized in alphabetical order.
With Sublime Text 2/3: select everything inside serialize() and press F9 - it will sort it automatically.

## FAQ

The license?
This library is in the public domain. You can do what you want, but I would appreciate attribution.

### Dependencies
 STL, c-runtime.

### Performance
JSON loading - allocation-free parsing, N Log(N) performance where N is number of properties in an JSON object.

JSON saving - linear performance, std::ofstream is used to save data ( some allocations )

### Tests
 Download googletests from https://github.com/google/googletest/tree/master/googletest, install near glw_json. Run cmake on CMakeLists.txt in tests folder.

### Compartibility
 Currently tested with Visual Studio 2013.



