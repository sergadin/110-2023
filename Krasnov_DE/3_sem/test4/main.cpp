#include <iostream>
#include <vector>
#include <map>
#include <ctime>


using namespace std;

// class for table reservations
class RestaurantBooking {
private:
    struct Reservation {
        int long long phone;
        time_t arrival;
        time_t departure;
        int table_number;
    };

    int total_tables;
    map<int, Reservation> bookings;  // search for a reservation in the alphabet by table number
    map<int long, time_t> phone_last_booking; // search for last time. reservations in alphabet by phone

    bool isTableAvailable(int table_number, time_t current_time) {
        if (bookings.find(table_number) == bookings.end())
            return true; //
        return current_time >= bookings[table_number].departure;
    }

    // output current time
    time_t getCurrentTime() {
        return time(0);
    }

public:
    RestaurantBooking(int tables) : total_tables(tables) {}

    // checking availability of a table
    int checkAvailability(time_t arrival_time) {
        for (int i = 1; i <= total_tables; ++i) {
            if (isTableAvailable(i, arrival_time)) {
                return i;
            }
        }
        return -1;
    }

    // make a table reservation
    bool bookTable(int long long phone, time_t arrival_time, int duration_minutes) {
        if (phone_last_booking.find(phone) != phone_last_booking.end() && phone_last_booking[phone] > arrival_time - 86400) {
            cout << "You cannot book two tables from one phone within one day\n";
            return false;
        }

        int available_table = checkAvailability(arrival_time);
        if (available_table == -1) {
            cout << "there are no tables available for the specified time\n";
            return false;
        }

        time_t departure_time = arrival_time + duration_minutes * 60;

        bookings[available_table] = {phone, arrival_time, departure_time, available_table};
        phone_last_booking[phone] = arrival_time;
        cout << "table number " << available_table << " was booked\n";
        return true;
    }

    // checking a record by phone number
    void checkBookingByPhone(int long long phone) {
        for (const auto& entry : bookings) {
            if (entry.second.phone == phone) {
                cout << "Telephon: " << phone << " Table: " << entry.second.table_number
                     << " Arrival time: " << ctime(&entry.second.arrival)
                     << " Time to leave: " << ctime(&entry.second.departure) << endl;
                return;
            }
        }
        cout << "There are no reservations for this phone\n";
    }

    // cancellation of reservation if 15 minutes late
    void cancelLateBookings() {
        time_t current_time = getCurrentTime();
        vector<int> tables_to_cancel;

        for (const auto& entry : bookings) {
            if (entry.second.arrival + 15 * 60 < current_time) {
                tables_to_cancel.push_back(entry.first);
            }
        }

        for (int table : tables_to_cancel) {
            cout << "Table reservation number " << table << " canceled due to more than 15 minutes late\n";
            bookings.erase(table);
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    RestaurantBooking restaurant(15); // fix the number of tables in the restaurant

    time_t current_time = time(0);
    // examples of bookings
    restaurant.bookTable(79874567302, current_time + 3600, 120);
    restaurant.bookTable(79174987230, current_time + 7200, 90);
    restaurant.bookTable(79236848147, current_time + 86400, 60);

    // check reservations
    restaurant.checkBookingByPhone(79174987230);
    restaurant.checkBookingByPhone(12345677701);
    restaurant.checkBookingByPhone(12345678901);

    //cancellation of overdue reservations
    restaurant.cancelLateBookings();

    return 0;
}
