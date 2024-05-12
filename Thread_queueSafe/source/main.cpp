#include <iostream>

#include <thread>
#include <chrono>

#include "thread_pull/thread_pull.hpp"
#include "test_functions/test_functions.hpp"


int main(int argc, char** argv) {

	thread_pull pool;

	for (size_t i = 0; i < 5; ++i)
	{
		pool.submit(test_functions::func1);
		pool.submit(test_functions::func2);
		std::cout << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}