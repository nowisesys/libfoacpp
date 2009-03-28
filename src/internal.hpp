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

#ifndef __INTERNAL_HPP__
#define __INTERNAL_HPP__

namespace foa {
	
	struct parse_data
	{
		char *buffer;    // Scan buffer
		size_t size;        // Scan buffer size
		size_t start;       // Scan start position
		size_t end;         // Scan end position
		size_t ppos;        // Current put position
		size_t line;        // Current line
		bool external;   // Buffer is external
		
		parse_data();
		~parse_data();
		
		void reset(bool external);
		void resize(size_t size);
		void move_data();
	};

	class escape 
	{
	private:
		static std::string & replace(std::string &str, const char *find, const char *replace);
	public:
		static std::string & encode(std::string &str);
		static std::string & decode(std::string &str);
	};
	
}       // namespace foa

#endif  // __INTERNAL_HPP__
