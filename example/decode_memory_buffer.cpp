#include <iostream>
#include <cstring>
#include "libfoa++.hpp"

// 
// Example: decode_memory_buffer
// 
// The example decodes an "in core" buffer. The buffer is just an ordinary
// char array, so the decoder don't have to allocate any memory.
// 

int main()
{
	const char *buffer = "persons = [\n(\nname=adam\nage = 37\n)\n(\nname=bertil\nage=45\n)\n]\n";
	foa::decoder dec(buffer, strlen(buffer));

	std::cout << "buffer:\n-------\n" << buffer << std::endl;
	
	while(const foa::entity *ent = dec.read()) {
		if(ent->name.size() != 0) {
			std::cout << ent->name << " = " << ent->data << "\t(type=" << ent->type << ")\n";
		} else {
			std::cout << ent->data << "\t(type=" << ent->type << ")\n";
		}
		
	}
	return 0;
}
