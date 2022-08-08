#pragma once

#include <algorithm>
#include <cstdlib>

template <typename T>
class SimpleVector {
public:
	SimpleVector() = default;

	explicit SimpleVector(size_t size)
		: size(size), capacity(size) {
			data = new T[size];
	}

	~SimpleVector() {
		delete[] data;
	}

	T& operator[](size_t index) {
		return *(data + index);
	}

	T* begin() {
		return data;
	}
	T* end() {
		return data + size;
	}

	size_t Size() const {
		return size;
	}
	size_t Capacity() const {
		return capacity;
	}
	void PushBack(const T& value) {
		if(capacity == 0) {
			data = new T[1];
			capacity = 1;
		}
		else if(size == capacity) {
			T* new_data = new T[2 * capacity];
			std::copy(data, data + size, new_data);
			delete[] data;
			data = new_data;
			capacity *= 2;
		}
		*(data + size) = value;
		size += 1;
	}

private:
	int capacity = 0, size = 0;
	T* data{};
};
