#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <numeric>

using namespace std;

class ReadingManager {
public:
	ReadingManager()
		:	users_at_page(1001, 0)
		{
		}

	void Read(int user_id, int page_count) {
		if(pages_of_user.count(user_id) != 0)
			--users_at_page[pages_of_user[user_id]];
		
		++users_at_page[page_count];
		pages_of_user[user_id] = page_count;
	}

	double Cheer(int user_id) const {
		int user_count = pages_of_user.size();
		if(pages_of_user.count(user_id) == 0)
			return 0;
		if(user_count == 1)
			return 1;
		
		int users_behind = accumulate(
								users_at_page.begin(), 
								users_at_page.begin() + pages_of_user.at(user_id), 
								0);
		return (users_behind * 1.0) / (user_count - 1);
	}

private:
	map<int, int> pages_of_user;
	vector<int> users_at_page;
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ReadingManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type;
		cin >> query_type;
		int user_id;
		cin >> user_id;

		if (query_type == "READ") {
			int page_count;
			cin >> page_count;
			manager.Read(user_id, page_count);
		} else if (query_type == "CHEER") {
			cout << setprecision(6) << manager.Cheer(user_id) << "\n";
		}
	}

	return 0;
}