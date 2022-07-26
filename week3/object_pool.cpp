#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
	T* Allocate() {
		auto ptr = TryAllocate();
		if(ptr != nullptr)
			return ptr;

		ptr = new T;
		allocated.insert(ptr);
		return ptr;
	}

	T* TryAllocate() {
		if(!deallocated.empty()) {
			auto ptr = deallocated.front();
			allocated.insert(ptr);
			deallocated.pop();
			return ptr;
		}
		return nullptr;
	}

	void Deallocate(T* object) {
		if(allocated.count(object) == 0) {
			throw invalid_argument("object has not been allocated");
		}

		deallocated.push(object);
		allocated.erase(object);
	}

	~ObjectPool() {
		while(!deallocated.empty()) {
			delete deallocated.front();
			deallocated.pop();
		}
		for(auto ptr : allocated)
			delete ptr;
	}

private:
	queue<T*> deallocated;
	set<T*> allocated;
};

void TestObjectPool() {
	ObjectPool<string> pool;

	auto p1 = pool.Allocate();
	auto p2 = pool.Allocate();
	auto p3 = pool.Allocate();

	*p1 = "first";
	*p2 = "second";
	*p3 = "third";

	pool.Deallocate(p2);
	ASSERT_EQUAL(*pool.Allocate(), "second");

	pool.Deallocate(p3);
	pool.Deallocate(p1);
	ASSERT_EQUAL(*pool.Allocate(), "third");
	ASSERT_EQUAL(*pool.Allocate(), "first");

	pool.Deallocate(p1);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestObjectPool);
	return 0;
}
