#include "../library/timing/highperf.hpp"
#include "sleep.hpp"

#include <iostream>

using namespace library;

void test_timing()
{
	typedef HighResClock clock;
    
	int count = 0;
	
	while(true)
	{
		auto t0 = clock::now();
		std::cout << count << ",   ";
		
		sleep(2);
		
		auto t1 = clock::now();
		std::chrono::microseconds micros = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
		count = micros.count();
	}
}
