#include <iostream>
#include <string>
#include <iomanip>
#include <deque>
#include <map>
#include <set>

using namespace std;



class HotelManager {
public:

	void Book(int64_t time, string hotel_name, int client_id, int room_count) {
		Booking booking{time, hotel_name, client_id, room_count};
		bookings.push_front(booking);
		rooms[hotel_name] += room_count;
		clients[hotel_name][client_id] += room_count;
		
		DeleteOldBookings();
	}

	int Clients(const string& hotel_name) const {
		return clients.count(hotel_name) != 0 ? clients.at(hotel_name).size() : 0;
	}

	int Rooms(const string& hotel_name) const {
		return rooms.count(hotel_name) != 0 ? rooms.at(hotel_name) : 0;
	}

private:
	struct Booking {
		int64_t time;
		string hotel_name;
		int client_id;
		int room_count;
	};

	deque<Booking> bookings;
	map<string, map<int, int>> clients; // key -> hotel_name, value -> key -> client_id, value -> room_count;
	map<string, int> rooms;				// key -> hotel_name, value -> room_count;

	void DeleteOldBookings() {
		int64_t current_time = bookings.front().time;
		while(current_time - bookings.back().time >= 86400) {
			auto booking = bookings.back();
			bookings.pop_back();

			rooms[booking.hotel_name] -= booking.room_count;
			if(rooms[booking.hotel_name] == 0)
				rooms.erase(booking.hotel_name);
			
			clients[booking.hotel_name][booking.client_id] -= booking.room_count;
			if(clients[booking.hotel_name][booking.client_id] == 0)
				clients[booking.hotel_name].erase(booking.client_id);
			if(clients[booking.hotel_name].size() == 0)
				clients.erase(booking.hotel_name);
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	HotelManager manager;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id) {
		string query_type, hotel_name;
		cin >> query_type;

		if (query_type == "BOOK") {
			int64_t time;
			int client_id, room_count;
			cin >> time >> hotel_name >> client_id >> room_count;
			manager.Book(time, hotel_name, client_id, room_count);
		} else if (query_type == "CLIENTS") {
			cin >> hotel_name;
			cout << manager.Clients(hotel_name) << '\n';
		} else if (query_type == "ROOMS") {
			cin >> hotel_name;
			cout << manager.Rooms(hotel_name) << '\n';
		}
	}

	return 0;
}