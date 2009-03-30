#include <iostream>
#include <cstdlib>
#include "libfoa++.hpp"

// 
// Example: decode_large_object
// 
// Generate a huge number of objects and then decode them to test
// the overall performance of the decoding code.
// 

int main(int argc, char **argv)
{	
	std::string obj("(\nname=adam\nage=35\n)\n");
	std::string str;
	unsigned int num = 20000000;

	if(argc != 1) {
		num = strtoul(argv[1], 0, 10);
	}
	
	std::cout << "initilizing " << num << " objects... ";
	std::cout.flush();
	str += "[\n";
	for(unsigned int i = 0; i < num; ++i) {
		str += obj;
	}
	str += "]\n";
	std::cout << "done\n";

	const foa::entity *ent;
	foa::decoder dec(str);
	
	std::cout << "decoding objects... ";
	std::cout.flush();
	while((ent = dec.read())) {
	}
	std::cout << "done\n";
	
	return 0;
}
