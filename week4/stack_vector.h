#pragma once

#include <stdexcept>
#include <array>
#include <iostream>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
	explicit StackVector(size_t a_size = 0) {
		if(a_size > N) {
			throw invalid_argument("size is more than capacity");
		}
		size = a_size;
	}

	T& operator[](size_t index) {
		return data[index];
	}

	const T& operator[](size_t index) const {
		return data[index];
	}

	auto begin() {
		return data.begin();
	}
	auto end() {
		return data.begin() + size;
	}
	auto begin() const {
		return data.begin();
	}
	auto end() const {
		return data.begin() + size;
	}

	size_t Size() const {
		return size;
	}
	size_t Capacity() const {
		return N;
	}

	void PushBack(const T& value) {
		if(size == N) {
			throw overflow_error("full capacity is reached");
		}
		data[size++] = value;
	}

	T PopBack() {
		if(size == 0) {
			throw underflow_error("no elements to be removed");
		}
		return data[--size];
	}

private:
	array<T, N> data;
	int size = 0;
};
