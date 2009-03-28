// Library implementing FOA - Fast Object and Array encoding.
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

namespace foa {

	// 
	// Construct the parse data object.
	// 
	parse_data::parse_data() 
		: buffer(0), size(0), start(0), end(0), ppos(0), line(0), external(false)
	{
	}

	parse_data::~parse_data()
	{
		if(!external) {
			delete [] buffer;
		}
	}
	
	// 
	// Reset the parse data. This method should be called prior to set
	// a new stream or buffer to decode.
	// 
	void parse_data::reset(bool external)
	{
		if(external != this->external) {
			buffer = 0;
		}
		this->external = external;
		line = start = end = ppos;
	}
	
	// 
	// Resize the buffer.
	// 
	void parse_data::resize(int size)
	{
		char *buffer = new char[size + 1];
		memcpy(buffer, this->buffer, this->size);
		this->size = size;
		this->buffer = buffer;
	}
	
	// 
        // Move undecoded data to beginning of array. This method should be
	// called when no more entities where found in current buffer, but
	// before the buffer is filled again.
	// 
	void parse_data::move_data()
	{
		int length = ppos - end;
		memmove(buffer + end, buffer, length);
		ppos = length; start = end = 0;
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
	memory_strategy::memory_strategy(int init, int step, int max)
	{
		this->init = init;
		this->step = step;
		this->max  = max;
	}
	
	// 
	// Creates the object using default sizes for initial buffer size 
	// and reallocation chunk size, but with no maximum buffer size.
	// 
	memory_strategy::memory_strategy(int init, int step)
	{
		this->init = init;
		this->step = step;
		this->max  = UNLIMITED;
	}
	
	// 
	// Replace all occurances of 'find' with 'replace' within the string 'str'.
	// 
	std::string & escape::replace(std::string &str, const char *find, const char *replace)
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
		str = replace(str, "(", "%28");
		str = replace(str, "[", "%5B");
		str = replace(str, "]", "%29");
		str = replace(str, ")", "%5D");
		str = replace(str, "=", "%3D");
		
		return str;
	}	

	// 
	// Unescape all special chars in str.
	// 
	std::string & escape::decode(std::string &str)
	{
		str = replace(str, "%28", "(");
		str = replace(str, "%5B", "[");
		str = replace(str, "%29", "]");
		str = replace(str, "%5D", ")");
		str = replace(str, "%3D", "=");
		
		return str;
	}
}
