#include "test_runner.h"
#include <vector>
#include <utility>

using namespace std;

template <typename T>
class Table {
public:
	Table(size_t row_count, size_t col_count) {
		table.resize(row_count, vector<T>(col_count));
	}

	const vector<T>& operator[](size_t i) const {
		return table[i];
	}

	vector<T>& operator[](size_t i) {
		return table[i];
	}

	void Resize(size_t new_row_count, size_t new_col_count) {
		for(auto& row : table) {
			row.resize(new_col_count);
		}
		table.resize(new_row_count, vector<T>(new_col_count));
	}

	pair<size_t, size_t> Size() const {
		if(table.empty() || table[0].empty())
			return {0, 0};
		return {table.size(), table[0].size()};
	}

private:
	vector<vector<T>> table;
};

void TestTable() {
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestTable);
	return 0;
}