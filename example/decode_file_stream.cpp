#include <iostream>
#include <fstream>
#include "libfoa++.hpp"

// 
// Example: decode_file_stream
// 
// Decode data read from a file.
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
	
	foa::decoder dec(fs);
	while(const foa::entity *ent = dec.read()) {
		if(ent->name.size() != 0) {
			std::cout << ent->name << " = " << ent->data << "\t(type=" << ent->type << ")\n";
		} else {
			std::cout << ent->data << "\t(type=" << ent->type << ")\n";
		}		
	}
	
	return 0;
}
