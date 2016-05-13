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
