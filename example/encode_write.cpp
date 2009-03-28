#include <iostream>
#include "libfoa++.hpp"

// 
// Example: encode_write
// 
// Test the various write methods of the encoder class.
// 

int main()
{
	foa::encoder enc;
	
	enc.write("single line");
	std::cout << enc.buffer() << std::endl;
	
	enc.write("name", "anders");
	std::cout << enc.buffer() << std::endl;
	enc.write("age", 39);
	std::cout << enc.buffer() << std::endl;
	enc.write("bmi", 1.56);
	std::cout << enc.buffer() << std::endl;
	
	enc.write("object", foa::start_object);
	std::cout << enc.buffer() << std::endl;
	enc.write(foa::end_object);
	std::cout << enc.buffer() << std::endl;

	enc.write("array", foa::start_array);
	std::cout << enc.buffer() << std::endl;
	enc.write(foa::end_array);
	std::cout << enc.buffer() << std::endl;
	
	return 0;
}
