// C++ library implementation of FOA - Fast Object and Array encoding.
// Copyright (C) 2009 Anders L�vgren
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
		buffer(str.c_str(), str.size());
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
	// Decode next entity.
	// 
	void decoder::decode() 
	{
		ent.line = data->line;
		
		std::string str = std::string(&data->buffer[data->start], data->end - data->start);
		size_t pos = str.find_first_of('=');
		if(pos != std::string::npos) {
			ent.name = str.substr(0, pos);
			ent.data = str.substr(pos + 1, 0);
		} else {
			ent.name = "";
			ent.data = str;
		}
		if(ent.data.size() == 1) {
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
			*data = curr;
			return false;
		}
		data->start = data->end;
		while(data->end < data->ppos && data->buffer[data->end] != '\n') {
			++data->end;
		}
		if(data->end >= data->ppos) {
			*data = curr;
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
