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
// This file implements the FOA decoder interface.
// 

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdexcept>
#include <cctype>

#include "libfoa++.hpp"
#include "internal.hpp"

namespace foa {
	
	static memory_strategy default_strategy;

	// 
	// Create object with no buffer or stream associated.
	// 
	decoder::decoder() : in(0), strat(0), escape(true)
	{
		data = new parse_data;
	}

	// 
	// Create decoder of external buffer.
	// 
	decoder::decoder(const char *buff, size_t len)
		: in(0), strat(0), escape(true)
	{
		data = new parse_data;
		buffer(buff, len);
	}
	
	// 
	// Create decoder for string.
	// 
	decoder::decoder(const std::string &str)
		: in(0), strat(0), escape(true)
	{
		data = new parse_data;
		buffer(str);
	}
	
	// 
	// Create decoder of stream using default memory 
	// allocation strategy.
	// 
	decoder::decoder(std::istream &in) : escape(true)
	{
		data = new parse_data;
		this->in = &in;
		this->strat = &default_strategy;
	}
	
	// 
	// Create decoder of stream using requested memory
	// allocation strategy.
	// 
	decoder::decoder(std::istream &in, const memory_strategy *strategy)
	{
		data = new parse_data;
		this->in = &in;
		this->strat = new memory_strategy(*strategy);
	}

	// 
	// Destroy decoder releasing allocated resources.
	// 
	decoder::~decoder() 
	{
		delete data;
		delete strat;
	}
	
	// 
	// Set new stream to decode. We need to reset the parse data.
	// 
	void decoder::stream(std::istream *in)
	{
		data->reset(false);
		this->in = in;
	}
	
	// 
	// Set a new memory allocation strategy.
	// 
	void decoder::strategy(const memory_strategy *strategy)
	{
		if(!strategy) {
			if(in) {
				throw std::invalid_argument("Can't clear memory strategy when input stream is set.");
			}
			delete strat;
			strat = 0;
			return;
		}
		
		if(strat->max_size() != memory_strategy::UNLIMITED && 
		   strat->max_size() != this->strat->max_size() && 
		   strat->max_size() < data->size) {
			// 
			// Make sure we don't loose data on resize:
			// 
			if(strat->max_size() < data->size - data->ppos) {
				strat->max_size(data->size - data->ppos);
			}
			data->move_data();
			data->resize(strat->max_size());
		}
		this->strat = new memory_strategy(*strategy);
	}
	
	// 
	// Sets an external buffer to parse.
	// 
	void decoder::buffer(const char *buff, size_t size)
	{
		data->reset(true);
		data->buffer = const_cast<char *>(buff);  // use buffer as read-only
		data->ppos = data->size = size;
	}
	
	// 
	// Sets an external string to parse.
	// 
	void decoder::buffer(const std::string &str) 
	{
		this->str = str;
		data->reset(true);
		data->buffer = const_cast<char *>(this->str.c_str());  // use buffer as read-only
		data->ppos = data->size = str.size();
	}
	
	// 
	// Get the current buffer. Note that returning the buffer when data 
	// is internal don't make sense (it's not terminated by null).
	// 
	const char * decoder::buffer() const 
	{
		return data->external ? data->buffer : 0;
	}
	
	// 
	// Set decoder option.
	// 
	void decoder::option(encopt opt, bool enable)
	{
		if(opt == enable_escape) {
			escape = enable;
		}
	}
	
	// 
	// Get decoder option.
	// 
	bool decoder::option(encopt opt) const
	{
		if(opt == enable_escape) {
			return escape;
		} 
		
		throw std::invalid_argument("invalid option");
	}
	
	// 
	// Parse next entity from input stream or buffer.
	// 
	const entity * decoder::read()
	{
		if(data->external) {
			if(!find()) {
				return 0;
			}
		} else {
			if(!find()) {
				// 
				// Move data to beginning of buffer, then 
				// attempt to fill it up again.
				// 
				if(data->buffer) {
					data->move_data();
				}
				if(!fill()) { 
					return 0;
				}
			}
		}
		decode();
		return &ent;
	}
	
	// 
	// Simple utility function for trimming an STL string.
	// 
	std::string FOA_API_HIDDEN trim(std::string str) 
	{
		std::string::size_type ts = 0;
		std::string::size_type te = str.size();
		
		while(isblank(str[ts]) || iscntrl(str[ts])) ++ts;
		while(isblank(str[te]) || iscntrl(str[te])) --te;
		
		return std::string(str, ts, te - ts + 1);
	}
	
	// 
	// Decode next entity.
	// 
	void decoder::decode() 
	{
		ent.line = data->line;
		
		std::string str = std::string(&data->buffer[data->start], data->end - data->start);		
		std::string::size_type pos = str.find_first_of('=');
		
		if(pos != std::string::npos) {
			ent.name = trim(str.substr(0, pos));
			ent.data = trim(str.substr(pos + 1));
		} else {
			ent.name = "";
			ent.data = trim(str);
		}
		
		if(ent.data.length() == 1) {
			switch(ent.data[0]) {
			case start_object:
				ent.type = entity::start_object;
				break;
			case start_array:
				ent.type = entity::start_array;
				break;
			case end_object:
				ent.type = entity::end_object;
				break;
			case end_array:
				ent.type = entity::end_array;
				break;
			}
		} else {
			ent.type = entity::data_name;
			if(escape) {
				ent.data = escape::decode(ent.data);
			}
		}
	}
	
	// 
	// Find next entity. After return from this method, the data
	// member contains start and end index of next entity in the
	// data buffer.
	// 
	bool decoder::find()
	{
		if(!data->buffer) {
			return false;
		}
		parse_data curr = *data;
		while(data->end < data->ppos && data->buffer[data->end] == '\n') {
			++data->end;
		}
		if(data->end >= data->ppos) {
			*data = curr;       // Rollback
			return false;
		}
		data->start = data->end;
		while(data->end < data->ppos && data->buffer[data->end] != '\n') {
			++data->end;
		}
		if(data->end >= data->ppos) {
			*data = curr;       // Rollback
			return false;
		}
		
		++data->line;
		return true;
	}
	
	// 
	// This method should be called on underflow to fill the data
	// buffer from the stream.
	// 
	bool decoder::fill()
	{
		if(!data->buffer) {
			data->buffer = new char[strat->init_size() + 1];
			data->size = strat->init_size();
		}
		while(true) {
			std::streamsize want = static_cast<std::streamsize>(data->size - data->ppos);
			
			in->read(&data->buffer[data->ppos], want);
			if(in->gcount() == 0) {
				return false;  // End of stream
			}
			data->ppos += in->gcount();
			if(find()) {
				return true;
			}
			if(in->gcount() == want) {
				size_t size = data->size + strat->step_size();
				if(strat->max_size() < size && 
				   strat->max_size() != memory_strategy::UNLIMITED) {
					throw std::overflow_error("Maximum buffer size exceeded.");
				}
				data->resize(size);
			}
		}
		return false;
	}
	
}       // namespace foa
