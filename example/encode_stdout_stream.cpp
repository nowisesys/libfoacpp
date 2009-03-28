#include <iostream>
#include "libfoa++.hpp"

// 
// Example: encode_stdout_stream
// 
// Demonstrate how to make encoded data be written to stdout without
// explicit call encoder::buffer to get encoded data. 
// 
// This example uses std::cout, but in practice any std::ostream 
// could be used.
// 

int main()
{
	foa::encoder enc(std::cout);
	
	// 
	// Write a simple object:
	// 
	enc.write("person", foa::start_object);
	enc.write("name", "adam");
	enc.write("age", 24);
	enc.write(foa::end_object);
	
	return 0;
}
