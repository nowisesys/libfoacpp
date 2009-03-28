#include <iostream>
#include "libfoa++.hpp"

// 
// Example: encode_escape
// 
// Test escaping of special chars in output.
// 

int main()
{
	const char *data = "a(b[c]d)e=";
	foa::encoder enc(std::cout);
	
	enc.option(foa::enable_escape, true);
	std::cout << "escape " << enc.option(foa::enable_escape) << ": ";
	enc.write(data);
	
	enc.option(foa::enable_escape, false);
	std::cout << "escape " << enc.option(foa::enable_escape) << ": ";
	enc.write(data);
	
	return 0;
}
