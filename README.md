# glw_json
Single-file public domain compact json parser for C/C++.
~340 lines of code

### Example
```c++
#include "../glw_json.h"

struct vec3{
  float x,y,z;
};

template<typename T>
bool serialize(T& t, vec3& v){
	bool b = true;
	b &= SERIALIZE(x);
	b &= SERIALIZE(y);
	b &= SERIALIZE(z);
	return b;
}

int main(){
	vec3 v;
	json::load_object_from_file("test.json", v);
	json::save_object_to_file("test2.json", v);
	return 1;
}
```

To avoid hash maps, values should be serialized in alphabetical order. 
With Sublime Text 2/3 - select everithing inside serialize() and press F9 - it will sort it automatically.

## FAQ

The license?
This library is in the public domain. You can do what you want, but I would appreciate attribution. 

### Dependencies
 STL, c-runtime.

### Performance
JSON loading - allocation-free parsing, N Log(N) performance where N is number of lines.

JSON saving - linear perfomance, std::ofstream is used to save data



