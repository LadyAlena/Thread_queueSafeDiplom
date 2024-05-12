#pragma once

#include <vector>
#include <functional>
#include <thread>

#include "../safe_queue/safe_queue.hpp"

class thread_pull {
public:
	thread_pull(const size_t& number_threads = std::thread::hardware_concurrency()) {
		for (size_t i = 0; i < number_threads; ++i) {
			pull.emplace_back([this]() { work(); });
		}
	}

	~thread_pull() {
		squeue.close();
		for (auto& thread : pull) {
			thread.join();
		}
	}

	template<typename Func, typename... Args>
	void submit(Func&& func, Args&&... args) {
		auto task = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
		squeue.push(std::move(task));
	}

private:
	void work() {
		while (true) {
			try {
				auto task = squeue.pop();
				task();
			}
			catch (const std::runtime_error&) {
				return;
			}
		}
	}

	std::vector<std::thread> pull;
	safe_queue<std::function<void()>> squeue;
};