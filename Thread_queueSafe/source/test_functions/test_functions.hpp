#pragma once

#include <iostream>

#include <thread>
#include <chrono>

namespace test_functions {
	void func_int(int x) {
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		std::cout << __FUNCTION__ << ": " << x << std::endl;
	}

	void func_str(const std::string& str) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << __FUNCTION__ << ": " << str << std::endl;
	}

	void func1() {
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		std::cout << __FUNCTION__ << std::endl;
	}

	void func2() {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << __FUNCTION__ << std::endl;
	}
}