#include "rest.h"
#include <algorithm>
#include <chrono>

ReservationJournal::ReservationJournal(int num_tables, std::time_t open_time, std::time_t close_time) :
	num_tables_(num_tables), open_time_(open_time), close_time_(close_time) {
		if (num_tables_ <= 0) {
			throw ReservationJournalError(1, "Количество столов  больше нуля.");
		}
		if (open_time_ >= close_time_) {
			throw ReservationJournalError(2, "Время открытия раньше времени закрытия.");
		}
	}

bool ReservationJournal::isTableAvailable(std::time_t arrival_time) const {
	if (!isValidTime(arrival_time)) {
		throw ReservationJournalError(3, "Некорректное время.");
	}
	return findFreeTable(arrival_time) != -1;
}


std::time_t ReservationJournal::getMaxVisitTime(std::time_t arrival_time) const {
	if (!isValidTime(arrival_time)) {
		throw ReservationJournalError(3, "Некорректное время.");
	}    std::time_t max_visit_time = arrival_time + 3 * 3600;
	if (max_visit_time > close_time_) {
		max_visit_time = close_time_;
	}
	return max_visit_time;
}


std::time_t ReservationJournal::findNextAvailableTime(std::time_t arrival_time) const {
	if (!isValidTime(arrival_time)) {
		throw ReservationJournalError(3, "Некорректное время.");
	}
	std::time_t current_time = arrival_time;
	while (current_time < close_time_) {
		if (findFreeTable(current_time) != -1) {
			return current_time;
		}
		current_time += 15 * 60; 
	}
	return close_time_;
}

void ReservationJournal::makeReservation(long long phone_number, std::time_t arrival_time) {
	if (!isValidTime(arrival_time)) {
		throw ReservationJournalError(3, "Некорректное время.");
	}
	if (hasReservation(phone_number)) {
		throw ReservationJournalError(4, "Уже есть бронь на сегодня.");
	}
	int table_number = findFreeTable(arrival_time);
	if (table_number == -1) {
		throw ReservationJournalError(5, "Свободных столиков нет на это время.");
	}
	reservations_.push_back({phone_number, arrival_time, table_number});
}
bool ReservationJournal::hasReservation(long long phone_number) const {
	return findTableByPhoneNumber(phone_number) != -1;
}

int ReservationJournal::getTableNumber(long long phone_number) const {
	int table_number = findTableByPhoneNumber(phone_number);
	if (table_number == -1) {
		throw ReservationJournalError(6, "Брони по этому номеру телефона нет.");
	}
	return table_number;
}
void ReservationJournal::checkIn(long long phone_number) {
	for (auto& reservation : reservations_) {
		if (reservation.phone_number == phone_number) {
			if (std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now() - std::chrono::system_clock::from_time_t(reservation.arrival_time)).count() > 15) {
				throw ReservationJournalError(7, "Бронь просрочена.");
			}
			reservation.arrival_time = std::time(nullptr);
			break;
		}
	}
}

void ReservationJournal::checkOut(long long phone_number) {
	for (auto it = reservations_.begin(); it != reservations_.end(); ++it) {
		if (it->phone_number == phone_number) {
			reservations_.erase(it);
			break;
		}
	}
}
bool ReservationJournal::isValidTime(std::time_t time) const {
	return time >= open_time_ && time < close_time_;
}

bool ReservationJournal::isReservationValid(const Reservation& reservation) const {
	return isValidTime(reservation.arrival_time) &&
		std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now() - std::chrono::system_clock::from_time_t(reservation.arrival_time)).count() <= 15;
}

int ReservationJournal::findFreeTable(std::time_t arrival_time) const {
	for (int i = 0; i < num_tables_; ++i) {
		bool table_is_free = true;
		for (const auto& reservation : reservations_) {
			if (isReservationValid(reservation) &&
					reservation.arrival_time <= arrival_time &&
					arrival_time < reservation.arrival_time + 3 * 3600 &&
					reservation.table_number == i) {
				table_is_free = false;
				break;
			}
		}
		if (table_is_free) {
			return i;
		}
	}
	return -1;
}

int ReservationJournal::findTableByPhoneNumber(long long phone_number) const {
	for (size_t i = 0; i < reservations_.size(); ++i) {
		if (reservations_[i].phone_number == phone_number) {
			return reservations_[i].table_number;
		}
	}
	return -1;
}
