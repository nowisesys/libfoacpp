#include <iostream>
#include "libfoa++.hpp"

// 
// Example: set_memory_strategy
// 
// Test set/get memory strategy.
// 

static void show_strategy(const char *label, const foa::memory_strategy *s)
{
	if(s) {
		std::cout << label << ": init=" << s->init_size() << ", step=" << s->step_size() << ", max=" << s->max_size() << std::endl;
	} else {
		std::cout << label << ": no memory strategy set.\n";
	}
}

int main()
{
	foa::decoder dec;
	foa::memory_strategy strategy1;
	foa::memory_strategy strategy2(512, 1024, 8096);
	
	show_strategy("uninitilized", dec.strategy());
	
	dec.strategy(&strategy1);
	show_strategy("default", dec.strategy());

	dec.strategy(&strategy2);
	show_strategy("custom", dec.strategy());

	strategy2.unlimited();
	dec.strategy(&strategy2);
	show_strategy("unlimited", dec.strategy());

	dec.strategy(0);
	show_strategy("cleared", dec.strategy());
	
	return 0;
}
