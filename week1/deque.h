#pragma once

#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque {
public:
	Deque() = default;

	bool Empty() const;

	size_t Size() const;

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	const T& At(size_t idx) const;
	T& At(size_t idx);

	const T& Front() const;
	T& Front();

	const T& Back() const;
	T& Back();

	void PushFront(const T& value);

	void PushBack(const T& value);

private:
	vector<T> front, back;

	const T& AtImpl(size_t index) const {
		if(front.size() > index)
			return front[front.size() - index - 1];
		return back[index - front.size()];
	}

	T& AtImpl(size_t index) {
		if(front.size() > index)
			return front[front.size() - index - 1];
		return back[index - front.size()];
	}
};

template <typename T>
bool Deque<T>::Empty() const {
	return front.empty() && back.empty();
}

template <typename T>
size_t Deque<T>::Size() const {
	return front.size() + back.size();
}

template <typename T>
const T& Deque<T>::operator[](size_t index) const {
	return AtImpl(index);
}

template <typename T>
T& Deque<T>::operator[](size_t index) {
	return AtImpl(index);
}

template <typename T>
const T& Deque<T>::At(size_t index) const {
	if(index >= Size())
		throw out_of_range("out of range");

	return AtImpl(index);
}

template <typename T>
T& Deque<T>::At(size_t index) {
	if(index >= Size())
		throw out_of_range("out of range");
		
	return AtImpl(index);
}

template <typename T>
const T& Deque<T>::Front() const {
	return operator[](0);
}

template <typename T>
T& Deque<T>::Front() {
	return operator[](0);
}

template <typename T>
const T& Deque<T>::Back() const {
	return operator[](Size() - 1);
}

template <typename T>
T& Deque<T>::Back() {
	return operator[](Size() - 1);
}

template <typename T>
void Deque<T>::PushFront(const T& value) {
	front.push_back(value);
}

template <typename T>
void Deque<T>::PushBack(const T& value) {
	back.push_back(value);
}