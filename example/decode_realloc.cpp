#include <iostream>
#include <fstream>
#include "libfoa++.hpp"

// 
// Example: decode_realloc
// 
// Test that realloc works when decoding by setting a silly 
// memory strategy forcing realloc the data buffer for each
// decoded character.
// 
// Notes: 
// 1. Using foa::memory_strategy(0, 1) will fail because it will create an
//    empty input buffer -> first read will fail.
// 2. Using foa::memory_strategy(1, 0) will fail because it will be impossble
//    to resize the input buffer after first successful read.
// 3. Using negative values for foa::memory_strategy() will fail allocating
//    the input buffer.
//    

int main(int argc, char **argv)
{
	const char *file = "person.txt";
	if(argc != 1) {
		file = argv[1];
	}
	std::ifstream fs(file);
	if(!fs) {
		std::cerr << "failed open " << file << " for reading\n";
		return 1;
	}
	
	foa::memory_strategy strategy(1, 1);
	foa::decoder dec(fs, &strategy);
	
	while(const foa::entity *ent = dec.read()) {
		if(ent->name.size() != 0) {
			std::cout << ent->name << " = " << ent->data << "\t(type=" << ent->type << ")\n";
		} else {
			std::cout << ent->data << "\t(type=" << ent->type << ")\n";
		}
	}
	
	return 0;
}
