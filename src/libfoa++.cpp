// C++ library implementation of FOA - Fast Object and Array encoding.
// Copyright (C) 2009 Anders Lövgren
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STRING_H
# include <string.h>
#elif HAVE_STRINGS_H
# include <strings.h>
#endif

#include "libfoa++.hpp"
#include "internal.hpp"

#ifndef HAVE_ISBLANK
int isblank(int c)
{
	return c == ' ' || c == '\t';
}
#endif

namespace foa {

	// 
	// Constructor for the shared parse buffer.
	// 
	parse_data::buff_rep::buff_rep() 
		: buffer(0), size(0), ppos(0), external(false), ref(0)
	{
	}
	
	// 
	// Only delete internal allocated buffer.
	// 
	parse_data::buff_rep::~buff_rep()
	{
		if(!external) {
			delete [] buffer;
		}
	}
	
	parse_data::scan_rep::scan_rep()
		: start(0), end(0), line(0)
	{
	}
	
	// 
	// Construct the parse data object.
	// 
	parse_data::parse_data() 
	{
		rep = new buff_rep;
	}

	// 
	// The copy contructor should share the parse buffer representation.
	// 
	parse_data::parse_data(const parse_data &data)
	{
		clone(data);
		rep->ref++;
	}
	
	// 
	// Delete the buffer only when buffer reference count drops below zero.
	// 
	parse_data::~parse_data()
	{
		if(--rep->ref < 0) {
			delete rep;
		}
	}

	// 
	// Increment buffer reference count on this object when assigned from
	// another object. We should *not* increment the refernce count here!
	// 
	void parse_data::operator=(const parse_data &data) 
	{
		clone(data);
	}
	
	// 
	// Reset the parse data. This method should be called prior to set
	// a new stream or buffer to decode.
	// 
	void parse_data::reset(bool external)
	{
		if(external != rep->external) {
			rep->buffer = 0;
		}
		rep->external = external;
		pos.line = pos.start = pos.end = rep->ppos = 0;
	}
	
	// 
	// Resize the buffer.
	// 
	void parse_data::resize(size_t size)
	{
		char *buffer = new char[size];
		if(rep->buffer) {
			memcpy(buffer, rep->buffer, rep->size);
			delete [] rep->buffer;
		}
		rep->size = size;
		rep->buffer = buffer;
	}
	
	// 
        // Move undecoded data to beginning of array. This method should be
	// called when no more entities where found in current buffer, but
	// before the buffer is filled again.
	// 
	void parse_data::move_data()
	{
		size_t length = rep->ppos - pos.end;
		memmove(rep->buffer + pos.end, rep->buffer, length);
		rep->ppos = length - 1;
		pos.start = pos.end = 0;
	}

	// 
	// Creates the object using default sizes for initial buffer 
	// size, reallocation chunk size and maximum buffer size.
	// 
	memory_strategy::memory_strategy()
	{
		init = INIT_SIZE;
		step = STEP_SIZE;
		max  = MAX_SIZE;
	}

	// 
	// Creates the object using the requsted sizes.
	// 
	memory_strategy::memory_strategy(size_t init, size_t step, size_t max)
	{
		this->init = init;
		this->step = step;
		this->max  = max;
	}
	
	// 
	// Creates the object using default sizes for initial buffer size 
	// and reallocation chunk size, but with no maximum buffer size.
	// 
	memory_strategy::memory_strategy(size_t init, size_t step)
	{
		this->init = init;
		this->step = step;
		this->max  = UNLIMITED;
	}
	
	// 
	// Replace all occurances of 'find' with 'replace' within the string 'str'.
	// 
	std::string escape::replace(std::string str, const char *find, const char *replace)
	{
		size_t len = strlen(find);
		size_t pos = 0;
		
		while((pos = str.find(find, pos)) != std::string::npos) {
			str = str.replace(pos, len, replace);
		}
		
		return str;
	}

	// 
	// Escape all special chars in str.
	// 
	std::string & escape::encode(std::string &str)
	{
		if(str.find_first_of("([])=") != std::string::npos) {
			str = replace(str, "(", "%28");
			str = replace(str, "[", "%5B");
			str = replace(str, "]", "%5D");
			str = replace(str, ")", "%29");
			str = replace(str, "=", "%3D");
		}
		return str;
	}	

	// 
	// Unescape all special chars in str.
	// 
	std::string & escape::decode(std::string &str)
	{
		if(str.find('%') != std::string::npos) {
			str = replace(str, "%28", "(");
			str = replace(str, "%5B", "[");
			str = replace(str, "%29", "]");
			str = replace(str, "%5D", ")");
			str = replace(str, "%3D", "=");
		}
		return str;
	}
}
