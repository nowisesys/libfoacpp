#include <iostream>
#include <string>
#include "libfoa++.hpp"

// 
// Example: decode_string_dynamic
// 
// This example is similar to decode_string_buffer, but instead of using 
// passing the string to decode when creating the decoder, we calls the 
// decoder::buffer() to set buffer to decode.
// 

static void print_decoded(foa::decoder *dec)
{
	while(const foa::entity *ent = dec->read()) {
		if(ent->name.size() != 0) {
			std::cout << ent->name << " = " << ent->data << "\t(type=" << ent->type << ")\n";
		} else {
			std::cout << ent->data << "\t(type=" << ent->type << ")\n";
		}
	}
}

int main()
{
	foa::decoder dec;

	dec.buffer("(\ndir=/home/anders\ninode=84626253\nfiles=[\nfile1.txt\nfile2.txt\n]\n)\n");
	std::cout << "buffer:\n-------\n" << dec.buffer() << std::endl;
	print_decoded(&dec);
	std::cout << std::endl << std::endl;

	dec.buffer("(\ndir=/home/bertil\ninode=74636621\nfiles=[\nfile3.txt\nimg4.jpg\n]\n)\n");
	std::cout << "buffer:\n-------\n" << dec.buffer() << std::endl;
	print_decoded(&dec);
	
	return 0;
}
