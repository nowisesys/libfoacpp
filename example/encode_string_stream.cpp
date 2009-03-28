#include <iostream>
#include <sstream>
#include "libfoa++.hpp"

// 
// Example: encode_string_stream
// 
// Demonstrate how to write encoded data to a string stream. This
// allows us to do output buffering: all data is written to the
// string stream object, once we like to send data, we simple call
// the stringstream::str() to get the data.
// 

int main()
{
	std::ostringstream str;
	foa::encoder enc(str);
	
	// 
	// Write a simple object to the string stream:
	// 
	enc.write("person", foa::start_object);
	enc.write("name", "adam");
	enc.write("age", 24);
	enc.write(foa::end_object);

	// 
	// Write string stream buffer to stdout:
	// 
	std::cout << dynamic_cast<std::ostringstream &>(enc.stream()).str();
	
	return 0;
}
