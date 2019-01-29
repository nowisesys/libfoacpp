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

#ifndef __LIBFOAPP_HPP__
#define __LIBFOAPP_HPP__

#ifndef __cplusplus
extern "C++" {
#endif

#include <istream>
#include <ostream>
#include <sstream>

#if defined(WIN32) || defined(_WINDOWS) || defined(__CYGWIN__)
	/* Define LIBFOAPP_EXPORTS when building library on windows. */
# if defined(LIBFOAPP_EXPORTS)
#  if defined(__GNUC__)
#   define FOA_API_PUBLIC __attribute__((dllexport))
#  else
	/* Note: actually gcc seems to also supports this syntax. */
#   define FOA_API_PUBLIC __declspec(dllexport)
#  endif
# else
#  if defined(__GNUC__)
#   define FOA_API_PUBLIC __attribute__((dllimport))
#  else
	/* Note: actually gcc seems to also supports this syntax. */
#   define FOA_API_PUBLIC __declspec(dllimport) 
#  endif
# endif
# define FOA_API_HIDDEN
#else
# if __GNUC__ >= 4
#  define FOA_API_PUBLIC __attribute__ ((visibility("default")))
#  define FOA_API_HIDDEN __attribute__ ((visibility("hidden")))
# else
#  define FOA_API_PUBLIC
#  define FOA_API_HIDDEN
# endif
#endif

namespace foa {
	
	static const int   foavers = 0x010002;  // The library version.
	static const float foaspec = 1.0f;      // The FOA specification.
	
	// 
	// The FOA special characters:
	// 
	enum spec_chars
	{
		start_object = '(', end_object = ')',
		start_array  = '[', end_array  = ']'
	};
	
	// 
	// Encoding/decoding options:
	// 
	enum encopt 
	{
		enable_escape
	};
	
	// 
	// Represents an decoded entity:
	// 
	struct entity 
	{
		enum ttype { 
			start_object, end_object, 
			start_array,  end_array,
			data_name
		};
		
		std::string name;
		std::string data;
		ttype type;
		size_t line;		
	};
	
	// 
	// Memory allocation strategy:
	// 
	class FOA_API_PUBLIC memory_strategy 
	{
	public:
		static const size_t INIT_SIZE = 128;  // Default initial size.
		static const size_t STEP_SIZE = 256;  // Default step size.
		static const size_t MAX_SIZE  = 8 * 1024 * 1024; // Maximum buffer size.
		static const size_t UNLIMITED = 0;    // Use unlimited buffer size.
	private:
		size_t init;    // Initial buffer size.
		size_t step;    // Realloc buffer step size.
		size_t max;     // Maximum buffer size.
	public:
		memory_strategy();
		memory_strategy(size_t init, size_t step, size_t max);
		memory_strategy(size_t init, size_t step);
				
		void init_size(size_t val) { init = val; }
		void step_size(size_t val) { step = val; }
		void max_size(size_t val) { max = val; }
		void unlimited() { max = UNLIMITED; }
		
		size_t init_size() const { return init; }
		size_t step_size() const { return step; }
		size_t max_size() const { return max; }
	};
	
	// 
	// The FOA encoder:
	// 
	class FOA_API_PUBLIC encoder 
	{
	private:
		std::ostream *out;   // Destination stream.
		std::string buff;    // Output buffer.
		bool escape;         // Enable/disable escape.
	public:
		encoder();
		encoder(std::ostream &out);
		encoder(std::ostream *out);
		
		void stream(std::ostream *out) { this->out = out; }
		std::ostream & stream() const { return *out; }
		const std::string & buffer() const { return buff; }
		
		void option(encopt opt, bool enable);
		bool option(encopt opt) const;  // throws std::invalid_argument
		
		inline void write(std::string data);
		inline void write(std::string name, std::string data);
		inline void write(std::string name, int data);
		inline void write(std::string name, double data);
		inline void write(std::string name, spec_chars spec);
		inline void write(spec_chars spec);
	private:
		void write_entity(const std::string &str);
		std::string & escaped(std::string &str);
		template <typename T> inline std::string convert(T &);
	};

	struct parse_data;  // Forward declare.

	// 
	// The FOA decoder:
	// 
	class FOA_API_PUBLIC decoder
	{
	private:
		std::istream *in;         // Source stream.
		std::string str;          // Source string.
		entity ent;               // Current entity.
		parse_data *data;         // Parse helper.
		memory_strategy *strat;   // Memory allocation strategy.
		bool escape;              // Enable/disable escape.
	public:
		decoder();
		decoder(const char *buff, size_t len);  // Decode external buffer.
		decoder(const std::string &);        // Decode string.
		decoder(std::istream &in);           // Decode stream.
		decoder(std::istream &in, const memory_strategy *strategy);
		~decoder();
		
		void stream(std::istream *in);
		std::istream & stream() const { return *in; }
		void strategy(const memory_strategy *strategy); // Throws std::invalid_argument
		const memory_strategy * strategy() const { return strat; }
		void buffer(const char *buff, size_t size);
		void buffer(const std::string &str);
		const char * buffer() const;
		
		void option(encopt opt, bool enable);
		bool option(encopt opt) const;  // Throws std::invalid_argument
		
		const entity * read();          // Throws std::overflow_error
	private:
		void decode();       // Decode next.
		bool find();         // Find next.
		bool fill();         // Fill buffer.
	};

	template <typename T> inline std::string encoder::convert(T &val)
	{
		std::stringstream out;
		std::string str = static_cast<std::stringstream &>((out << val)).str();
		return str;
	}
	
	inline void encoder::write(std::string data)
	{
		write_entity(escaped(data));
	}
	
	inline void encoder::write(std::string name, std::string data)
	{
		write_entity(name + " = " + escaped(data));
	}
	
	inline void encoder::write(std::string name, int data)
	{
		write_entity(name + std::string(" = ") + convert(data));
	}
	
	inline void encoder::write(std::string name, double data)
	{
		write_entity(name + std::string(" = ") + convert(data));
	}
	
	inline void encoder::write(std::string name, spec_chars spec)
	{
		write_entity(name + std::string(" = ") + static_cast<char>(spec));
	}
	
	inline void encoder::write(spec_chars spec)
	{
		write_entity(std::string() + static_cast<char>(spec));
	}
	
}      // namespace foa

#ifndef __cplusplus
}      // extern "C++"
#endif

#endif // __LIBFOAPP_H__
