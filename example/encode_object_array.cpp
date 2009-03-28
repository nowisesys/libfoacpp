#include <iostream>
#include "libfoa++.hpp"

// 
// Example: encode_object_array
// 
// Show how to encode an array of objects (persons).
// 

struct person
{
	const char *name;
	int age;
};

int main()
{
	person persons[] = {
		{ "adam", 35 },
		{ "bertil", 41 },
		{ "ceasar", 71 },
		{ 0, 0 }
	};
	
	foa::encoder enc(std::cout);
	
	enc.write(foa::start_array);
	for(person *pp = persons; pp->name; ++pp) {
		enc.write(foa::start_object);
		enc.write("name", pp->name);
		enc.write("age", pp->age);
		enc.write(foa::end_object);
	}
	enc.write(foa::end_array);
	
	return 0;
}
