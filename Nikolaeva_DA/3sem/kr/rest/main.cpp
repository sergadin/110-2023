#include <iostream>
#include <ctime>
#include "rest.h"

int main() {
	try {

		std::time_t now = std::time(nullptr);
		std::time_t open_time = now;
		std::time_t close_time = open_time + 12 * 3600; 

		ReservationJournal journal(5, open_time, close_time);
		journal.makeReservation(1234567890, open_time + 1 * 3600); 
		journal.makeReservation(9876543210, open_time + 2 * 3600); 
		std::cout << "Свободный столик в 3 часа после открытия: "
			<< (journal.isTableAvailable(open_time + 3 * 3600) ? "да" : "нет")
			<< std::endl;
		std::time_t next_available_time = journal.findNextAvailableTime(open_time + 2 * 3600);
		std::cout << "Ближайшее свободное время: "
			<< std::ctime(&next_available_time)
			<< std::endl;
		std::cout << "Бронь для номера 1234567890: "
			<< (journal.hasReservation(1234567890) ? "да" : "нет")
			<< std::endl;
		std::cout << "Номер столика для 1234567890: "
			<< journal.getTableNumber(1234567890)
			<< std::endl;
		journal.checkIn(1234567890);
		journal.checkOut(1234567890);

	} catch (const ReservationJournalError& e) {
		std::cerr << "Error code: " << e.getErrorCode() << ", Error message: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Standard exception: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown exception." << std::endl;
	}

	return 0;
}
