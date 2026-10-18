#ifndef REST_H
#define REST_H

#include <vector>
#include <stdexcept>
#include <string>
#include <ctime>

class ReservationJournalError : public std::runtime_error {
	public:
		ReservationJournalError(int errorCode, const std::string& msg)
			: std::runtime_error(msg), errorCode_(errorCode) {}

		int getErrorCode() const { return errorCode_; }

	private:
		int errorCode_;
};

struct Reservation {
	long long phone_number;
	std::time_t arrival_time;
	int table_number;
};


class ReservationJournal {
	public:

		ReservationJournal(int num_tables, std::time_t open_time, std::time_t close_time);


		bool isTableAvailable(std::time_t arrival_time) const;
		std::time_t getMaxVisitTime(std::time_t arrival_time) const;
		std::time_t findNextAvailableTime(std::time_t arrival_time) const;
		void makeReservation(long long phone_number, std::time_t arrival_time);
		bool hasReservation(long long phone_number) const;
		int getTableNumber(long long phone_number) const;
		void checkIn(long long phone_number);
		void checkOut(long long phone_number);

	private:
		int num_tables_;
		std::time_t open_time_;
		std::time_t close_time_;
		std::vector<Reservation> reservations_;

		bool isValidTime(std::time_t time) const;
		bool isReservationValid(const Reservation& reservation) const;
		int findFreeTable(std::time_t arrival_time) const;
		int findTableByPhoneNumber(long long phone_number) const;
};

#endif
