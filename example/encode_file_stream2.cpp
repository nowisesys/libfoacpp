#include <iostream>
#include <fstream>
#include "libfoa++.hpp"

// 
// Example: encode_file_stream2
// 
// Demonstrate how to write encoded data to a file by setting the
// destination ostream using a pointer to the file stream.
// 

int main()
{
	const char *file = "person.txt";
	
	std::ofstream fs(file);
	foa::encoder enc;
	enc.stream(&fs);
	
	// 
	// Write a simple object:
	// 
	enc.write("person", foa::start_object);
	enc.write("name", "adam");
	enc.write("age", 24);
	enc.write(foa::end_object);
	
	std::cout << "wrote data to " << file << std::endl;
	
	return 0;
}
