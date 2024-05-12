#pragma once

#include <exception>

#include <queue>

#include <mutex>
#include <condition_variable>
#include <atomic>

template <typename T>
class safe_queue {
public:
	void push(const T& obj) {
		std::unique_lock<std::mutex> lock(m);
		queue.push(std::move(obj));
		cv.notify_one();
	}

	T pop() {
		std::unique_lock<std::mutex> lock(m);
		cv.wait(lock, [this]() { return !queue.empty() || done; });

		if (queue.empty() && done) throw std::runtime_error("Queue is closed");

		T obj = queue.front();
		queue.pop();
		return obj;
	}

	void close() {
		done = true;
		cv.notify_all();
	}

	bool empty() {
		std::lock_guard<std::mutex> lock(m);
		return queue.empty();
	}

	size_t size() {
		std::lock_guard<std::mutex> lock(m);
		return queue.size();
	}

private:
	std::queue<T> queue;
	std::mutex m;
	std::condition_variable cv;
	std::atomic<bool> done = false;
};