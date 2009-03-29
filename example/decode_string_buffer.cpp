#include <iostream>
#include <string>
#include "libfoa++.hpp"

// 
// Example: decode_string_buffer
// 
// This example is similar to decode_memory_buffer, but instead of using an
// char array we use a std::string. 
// 

int main()
{
	std::string buffer("persons = [\n(\nname=adam\nage = 37\n)\n(\nname=bertil\nage=45\n)\n]\n");
	foa::decoder dec(buffer);

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
