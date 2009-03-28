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
	std::cout << enc.buffer();
	
	enc.write("name", "anders");
	std::cout << enc.buffer();
	enc.write("age", 39);
	std::cout << enc.buffer();
	enc.write("bmi", 1.56);
	std::cout << enc.buffer();
	
	enc.write("object", foa::start_object);
	std::cout << enc.buffer();
	enc.write(foa::end_object);
	std::cout << enc.buffer();

	enc.write("array", foa::start_array);
	std::cout << enc.buffer();
	enc.write(foa::end_array);
	std::cout << enc.buffer();
	
	return 0;
}
