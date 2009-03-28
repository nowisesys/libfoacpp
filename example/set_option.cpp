#include <iostream>
#include "libfoa++.hpp"

// 
// Example: set_option
// 
// Test setting option in class encoder and decoder.
// 

int main()
{
	foa::encoder enc;
	foa::decoder dec;
	
	std::cout << "encoder::escape: " << enc.option(foa::enable_escape) << std::endl;
	enc.option(foa::enable_escape, false);
	std::cout << "encoder::escape: " << enc.option(foa::enable_escape) << std::endl;

	std::cout << "decoder::escape: " << dec.option(foa::enable_escape) << std::endl;
	dec.option(foa::enable_escape, false);
	std::cout << "decoder::escape: " << dec.option(foa::enable_escape) << std::endl;
	
	return 0;
}
