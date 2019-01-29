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

// 
// This file implements the FOA encoder interface.
// 

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdexcept>

#include "libfoa++.hpp"
#include "internal.hpp"

namespace foa {
	
	encoder::encoder() : out(0), escape(true) 
	{
	}
	
	encoder::encoder(std::ostream &out) : out(&out), escape(true) 
	{
	}

	encoder::encoder(std::ostream *out) : out(out), escape(true) 
	{
	}
	
	void encoder::option(encopt opt, bool enable)
	{
		if(opt == enable_escape) {
			escape = enable;
		}
	}
	
	bool encoder::option(encopt opt) const 
	{
		if(opt == enable_escape) {
			return escape;
		} 
		
		throw std::invalid_argument("invalid option");
	}

	void encoder::write_entity(const std::string &str)
	{
		buff = str + "\n";
		if(out) {
			*out << buff;
		}
	}
	
	std::string & encoder::escaped(std::string &str) {
		if(escape) {
			str = escape::encode(str);
		}
		return str;
	}
}
