#include "deque.h"
#include "test_runner.h"

using namespace std;

void TestDeque() {
	Deque<int> d;
	ASSERT(d.Empty());

	d.PushBack(1);
	ASSERT_EQUAL(d.Front(), 1);
	ASSERT_EQUAL(d.Back(), 1);
	ASSERT_EQUAL(d.Size(), 1);
	ASSERT_EQUAL(d[0], 1);
	d[0] = 2;
	ASSERT_EQUAL(d[0], 2);

	d.PushFront(1);
	ASSERT_EQUAL(d.Front(), 1);
	ASSERT_EQUAL(d.Back(), 2);
	ASSERT_EQUAL(d.Size(), 2);
	ASSERT_EQUAL(d[1], 2);
	ASSERT_EQUAL(d.At(1), 2);

}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestDeque);
	return 0;
}