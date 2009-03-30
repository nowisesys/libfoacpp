#include <iostream>
#include "libfoa++.hpp"

// 
// Example: decode_escape
// 
// Tests decoding escaped input data from an memory buffer.
// 

int main()
{
	const foa::entity *ent;
	foa::decoder dec;
	
	std::cout << "\n** escape " << dec.option(foa::enable_escape) << ":\n";
	dec.buffer("name=a%28b%5Bc%29d%5De%3D\n");
	if((ent = dec.read())) {
		std::cout << dec.buffer();
		std::cout << "  name: '" << ent->name << "'\n";
		std::cout << "  data: '" << ent->data << "'\n";
	}

	dec.buffer("a%28b%5Bc%29d%5De%3D=name\n");
	if((ent = dec.read())) {
		std::cout << dec.buffer();
		std::cout << "  name: '" << ent->name << "'\n";
		std::cout << "  data: '" << ent->data << "'\n";
	}
	
	dec.buffer("a%28b%5Bc%29d%5De%3D=a%28b%5Bc%29d%5De%3D\n");
	if((ent = dec.read())) {
		std::cout << dec.buffer();
		std::cout << "  name: '" << ent->name << "'\n";
		std::cout << "  data: '" << ent->data << "'\n";
	}

	dec.buffer("name=name=a%28b%5Bc%29d%5De%3D\n");
	if((ent = dec.read())) {
		std::cout << dec.buffer();
		std::cout << "  name: '" << ent->name << "'\n";
		std::cout << "  data: '" << ent->data << "'\n";
	}

	dec.option(foa::enable_escape, false);
	std::cout << "\n** escape " << dec.option(foa::enable_escape) << ":\n";
	dec.buffer("name=a%28b%5Bc%29d%5De%3D\n");
	if((ent = dec.read())) {
		std::cout << dec.buffer();
		std::cout << "  name: '" << ent->name << "'\n";
		std::cout << "  data: '" << ent->data << "'\n";
	}
	return 0;
}
