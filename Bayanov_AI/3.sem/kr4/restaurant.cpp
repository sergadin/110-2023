#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <ctime>

class Reservation {
public:
    int TableNumber;
    int PhoneNumber;
    std::time_t ArrivalTime;
    std::time_t DepartureTime;

    Reservation(int TableNumber, int PhoneNumber, std::time_t ArrivalTime)
        : TableNumber(TableNumber), PhoneNumber(PhoneNumber), ArrivalTime(ArrivalTime) {
        DepartureTime = ArrivalTime + 3 * 3600;
    }
};

class Restaurant {
private:
    int N;
    std::vector<Reservation> reservations;
    std::time_t OpeningTime;
    std::time_t ClosingTime;

public:
    Restaurant(int NumTables, std::time_t OpenTime, std::time_t CloseTime)
        : N(NumTables), OpeningTime(OpenTime), ClosingTime(CloseTime) {}

    bool IsTableAvailable(std::time_t ArrivalTime) {
        std::time_t DepartureTime = ArrivalTime + 3 * 3600;
        for (const auto& res : reservations) {
            if ((ArrivalTime < res.DepartureTime) && (DepartureTime > res.ArrivalTime)) {
                return false;
                }
        }
        return true;
    }

    std::time_t FindMaxVisitTime(std::time_t ArrivalTime) {
        std::time_t MaxTime = ArrivalTime;
        while (MaxTime < ClosingTime) {
            if (IsTableAvailable(MaxTime)) {
                return MaxTime;
            }
            MaxTime += 3600;
        }
        throw std::runtime_error("No available table found.");
    }

    std::time_t FindNearestAvailableTime() {
        std::time_t CurrentTime = std::time(nullptr);
        if (CurrentTime < OpeningTime) {
            return OpeningTime;
        }
        while (CurrentTime < ClosingTime) {
            if (IsTableAvailable(CurrentTime)) {
                return CurrentTime;
            }
            CurrentTime += 3600;
        }
        throw std::runtime_error("No available time found.");
    }

    void MakeReservation(int PhoneNumber, std::time_t ArrivalTime) {
        if (ArrivalTime < OpeningTime || ArrivalTime > ClosingTime) {
            throw std::invalid_argument("Invalid Arrival time.");
        }
        if (!IsTableAvailable(ArrivalTime)) {
            throw std::runtime_error("No available table at the requested time.");
        }
        if (std::any_of(reservations.begin(), reservations.end(), [PhoneNumber](const Reservation& res) { return res.PhoneNumber == PhoneNumber; })) {
            throw std::runtime_error("Phone number already has a reservation.");
        }

        int TableNumber = (reservations.size() % N) + 1;
        reservations.emplace_back(TableNumber, PhoneNumber, ArrivalTime);
    }

    bool CheckReservation(int PhoneNumber) {
        return std::any_of(reservations.begin(), reservations.end(), 
                           [PhoneNumber](const Reservation& res) { return res.PhoneNumber == PhoneNumber; });
    }

    void MarkArrival(int PhoneNumber) {
        auto it = std::find_if(reservations.begin(), reservations.end(), 
                               [PhoneNumber](const Reservation& res) { return res.PhoneNumber == PhoneNumber; });
        if (it != reservations.end()) {
            std::cout << "Customer with phone number " << PhoneNumber 
                      << " has arrived at table " << it->TableNumber << ".\n";
            reservations.erase(it);
        } else {
            throw std::runtime_error("No reservation found for this phone number.");
        }
    }

    void CancelLateReservation(int PhoneNumber) {
        auto it = std::remove_if(reservations.begin(), reservations.end(), 
                                  [PhoneNumber](const Reservation& res) { return res.PhoneNumber == PhoneNumber; });
        if (it != reservations.end()) {
            reservations.erase(it, reservations.end());
        }
    }

    void CheckAndCancelLateReservations() {
        std::time_t CurrentTime = std::time(nullptr);
        for (auto it = reservations.begin(); it != reservations.end(); ) {
            if (std::difftime(CurrentTime, it->ArrivalTime) > 900) {
                it = reservations.erase(it);
                } else {
                ++it;
            }
        }
    }
};

int main() {
    std::time_t now = std::time(nullptr);
    std::tm* OpeningTm = std::localtime(&now);
    OpeningTm->tm_hour = 18;
    OpeningTm->tm_min = 0;
    OpeningTm->tm_sec = 0;
    std::time_t OpeningTime = std::mktime(OpeningTm);
    
    std::tm* ClosingTm = std::localtime(&now);
    ClosingTm->tm_hour = 23; 
    ClosingTm->tm_min = 0;
    ClosingTm->tm_sec = 0;
    std::time_t ClosingTime = std::mktime(ClosingTm);

    Restaurant restaurant(5, OpeningTime, ClosingTime); 
    try {
        restaurant.MakeReservation(123456789, OpeningTime + 3600);
        restaurant.MarkArrival(123456789);
        } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}