#include "Schedule.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

Schedule::Schedule() {}

Schedule::Schedule(FILE* fin) {
    if (fin){

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fin)) {
        TimeHM time;
        int room;
        char subject_name[128];
        FullName teacher;
        int group;

        if (sscanf(buffer, "%d:%d-%d:%d %d %127s %63s %63s %63s %d",
            &time.startHour, &time.startMinute, &time.endHour, &time.endMinute,
            &room, subject_name,
            teacher.surname, teacher.name, teacher.patronymic, &group) == 9) {
            Entry* newEntry = new Entry(time, room, subject_name, teacher, group);
            schedule_.push_back(newEntry);

            } else {
                throw Exception(5, "Error parsing line: " + std::string(buffer));
            }
        }
        //buildInd();
    }else{

        throw Exception(1, "File isn't open");
    }
}



Schedule::~Schedule() {
    for (Entry* entry : schedule_) {
        delete entry;
    }
    schedule_.clear(); 
}

/*void Schedule::buildInd() {
    teacherInd.clear();

    groupInd.clear();
    roomInd.clear();
    timeInd.clear();

    subjectInd.clear();

    for (size_t i = 0; i < schedule_.size(); ++i) {

        Entry* entry = schedule_[i];

        teacherInd[entry->getTeacher()].push_back(i);

        groupInd[entry->getGroup()].push_back(i);

        roomInd[entry->getRoom()].push_back(i);

        timeInd[entry->getTime()].push_back(i);

        subjectInd[entry->getSubjectName()].push_back(i);
    }
}

std::vector<int> Schedule::getCritInd(const std::string& crit) {

    // Return indexes based on specified parameter
    return std::vector<int>();
}

std::vector<int> Schedule::intesectInd(const std::vector<int>& ind1, const std::vector<int>& ind2) {
    std::vector<int> result;
    std::set_intersection(ind1.begin(), ind1.end(), ind2.begin(), ind2.end(), std::back_inserter(result));
    return result;
}*/

bool Schedule::checkTimeCross(const TimeHM& time1, const TimeHM& time2) {
    if (time1.startHour < time2.endHour || (time1.startHour == time2.endHour && time1.startMinute <= time2.endMinute)) {
        if (time2.startHour < time1.endHour || (time2.startHour == time1.endHour && time2.startMinute <= time1.endMinute)) {
            return true; 
        }
    }
    return false;
}

void Schedule::addEntry(Entry* entry) {
     for (Entry* existingEntry : schedule_) {
        if (existingEntry->getRoom() == entry->getRoom() && checkTimeCross(existingEntry->getTime(), entry->getTime())) {
            std::cerr << "Error: Time conflict with existing entry in room " << entry->getRoom() << std::endl;
            delete entry; 
            return;
        }
    }
    schedule_.push_back(entry);
    //buildInd();
}

void Schedule::deleteEntry(const TimeHM& time, int room) {
    for (size_t i = 0; i < schedule_.size(); ++i) {
         Entry* entry = schedule_[i];
        if (entry->getTime().startHour == time.startHour &&
             entry->getTime().startMinute == time.startMinute &&
             entry->getRoom() == room) {

            delete entry;
            schedule_.erase(schedule_.begin() + i);
            //buildInd();
            return;
        }
    }
     std::cerr << "Error: Entry not found" << std::endl;
}

void Schedule::updateEntry(const TimeHM& time, int room, Entry* newEntry) {
     for (size_t i = 0; i < schedule_.size(); ++i) {
          Entry* entry = schedule_[i];
           if (entry->getTime().startHour == time.startHour &&
                entry->getTime().startMinute == time.startMinute &&
                entry->getRoom() == room) {
                // Found the entry to update
                delete entry;  // Remove old entry
                schedule_[i] = newEntry; // Replace with new entry
                //buildInd();
                return;
            }
        }
    std::cerr << "Error: Entry not found" << std::endl;
}

std::vector<Entry*> Schedule::select(const std::vector<Cond>& crit) {
    std::vector<Entry*> selectedEntries;
    for (Entry* entry : schedule_) {
        bool match = true;
        for (const Cond& condition : crit) {
            Field field = condition.getField();
            BinOp operation = condition.getOperation();
            Value value = condition.getVal();

            switch (field) {
            case TIME:{
                  TimeHM timeValue = std::get<TimeHM>(value);
                    if (operation == EQ &&
                        (entry->getTime().startHour != timeValue.startHour ||
                         entry->getTime().startMinute != timeValue.startMinute ||
                         entry->getTime().endHour != timeValue.endHour ||
                         entry->getTime().endMinute != timeValue.endMinute)) {
                        match = false;
                    }
                  break;
            }

            case ROOM: {
                int roomValue = std::get<int>(value);
                if (operation == EQ && entry->getRoom() != roomValue) {
                    match = false;
                } else if (operation == NEQ && entry->getRoom() == roomValue) {
                    match = false;
                } else if (operation == LT && entry->getRoom() >= roomValue) {
                    match = false;
                } else if (operation == GT && entry->getRoom() <= roomValue) {
                    match = false;
                } else if (operation == LT_EQ && entry->getRoom() > roomValue) {
                    match = false;
                } else if (operation == GT_EQ && entry->getRoom() < roomValue) {
                    match = false;
                }
                break;
            }
            case SUBJNAME: {
                std::string subjNameValue = std::get<std::string>(value);
                if (operation == LIKE) {
                    std::regex pattern(subjNameValue);
                    if (!std::regex_match(entry->getSubjectName(), pattern)) {
                        match = false;
                    }
                } else if (operation == EQ && std::strcmp(entry->getSubjectName(), subjNameValue.c_str()) != 0) {
                    match = false;
                } else if (operation == NEQ && std::strcmp(entry->getSubjectName(), subjNameValue.c_str()) == 0) {
                    match = false;
                }
                break;
            }
             case TEACHERNAME: {
                std::string teacherNameValue = std::get<std::string>(value);
                if (operation == EQ && std::strcmp(entry->getTeacher().name, teacherNameValue.c_str()) != 0) {
                    match = false;
                } else if (operation == NEQ && std::strcmp(entry->getTeacher().name, teacherNameValue.c_str()) == 0) {
                    match = false;
                }
                break;
            }
            case TEACHERLASTNAME: {
                std::string teacherLastNameValue = std::get<std::string>(value);
                if (operation == EQ && std::strcmp(entry->getTeacher().surname, teacherLastNameValue.c_str()) != 0) {
                    match = false;
                } else if (operation == NEQ && std::strcmp(entry->getTeacher().surname, teacherLastNameValue.c_str()) == 0) {
                    match = false;
                }
                break;
            }
            case TEACHERPATR: {
                std::string teacherPatrValue = std::get<std::string>(value);
                if (operation == EQ && std::strcmp(entry->getTeacher().patronymic, teacherPatrValue.c_str()) != 0) {
                    match = false;
                } else if (operation == NEQ && std::strcmp(entry->getTeacher().patronymic, teacherPatrValue.c_str()) == 0) {
                    match = false;
                }
                break;
            }
            case GROUP: {
                int groupValue = std::get<int>(value);
                if (operation == EQ && entry->getGroup() != groupValue) {
                    match = false;
                } else if (operation == NEQ && entry->getGroup() == groupValue) {
                    match = false;
                } else if (operation == LT && entry->getGroup() >= groupValue) {
                    match = false;
                } else if (operation == GT && entry->getGroup() <= groupValue) {
                    match = false;
                } else if (operation == LT_EQ && entry->getGroup() > groupValue) {
                    match = false;
                } else if (operation == GT_EQ && entry->getGroup() < groupValue) {
                    match = false;
                }
                break;
            }
            default:
                break;
            }
        }
        if (match) {
            selectedEntries.push_back(entry);
        }
    }
    return selectedEntries;
}

std::vector<Entry*> Schedule::reselect(const std::vector<Entry*>& selected, const std::vector<Cond>& crit) {
    std::vector<Entry*> reselectedEntries;
    for (Entry* entry : selected) {
        bool match = true;
        for (const Cond& condition : crit) {
            Field field = condition.getField();
            BinOp operation = condition.getOperation();
            Value value = condition.getVal();

           switch (field) {
            case TIME:{
                  TimeHM timeValue = std::get<TimeHM>(value);
                    if (operation == EQ &&
                        (entry->getTime().startHour != timeValue.startHour ||
                         entry->getTime().startMinute != timeValue.startMinute ||
                         entry->getTime().endHour != timeValue.endHour ||
                         entry->getTime().endMinute != timeValue.endMinute)) {
                        match = false;
                    }
                  break;
            }

            case ROOM: {
                int roomValue = std::get<int>(value);
                if (operation == EQ && entry->getRoom() != roomValue) {
                    match = false;
                } else if (operation == NEQ && entry->getRoom() == roomValue) {
                    match = false;
                } else if (operation == LT && entry->getRoom() >= roomValue) {
                    match = false;
                } else if (operation == GT && entry->getRoom() <= roomValue) {
                    match = false;
                } else if (operation == LT_EQ && entry->getRoom() > roomValue) {
                    match = false;
                } else if (operation == GT_EQ && entry->getRoom() < roomValue) {
                    match = false;
                }
                break;
            }
            case SUBJNAME: {
                std::string subjNameValue = std::get<std::string>(value);
                if (operation == LIKE) {
                    std::regex pattern(subjNameValue);
                    if (!std::regex_match(entry->getSubjectName(), pattern)) {
                        match = false;
                    }
                } else if (operation == EQ && std::strcmp(entry->getSubjectName(), subjNameValue.c_str()) != 0) {
                    match = false;
                } else if (operation == NEQ && std::strcmp(entry->getSubjectName(), subjNameValue.c_str()) == 0) {
                    match = false;
                }
                break;
            }
             case TEACHERNAME: {
                std::string teacherNameValue = std::get<std::string>(value);
                if (operation == EQ && std::strcmp(entry->getTeacher().name, teacherNameValue.c_str()) != 0) {
                    match = false;
                } else if (operation == NEQ && std::strcmp(entry->getTeacher().name, teacherNameValue.c_str()) == 0) {
                    match = false;
                }
                break;
            }
            case TEACHERLASTNAME: {
                std::string teacherLastNameValue = std::get<std::string>(value);
                if (operation == EQ && std::strcmp(entry->getTeacher().surname, teacherLastNameValue.c_str()) != 0) {
                    match = false;
                } else if (operation == NEQ && std::strcmp(entry->getTeacher().surname, teacherLastNameValue.c_str()) == 0) {
                    match = false;
                }
                break;
            }
            case TEACHERPATR: {
                std::string teacherPatrValue = std::get<std::string>(value);
                if (operation == EQ && std::strcmp(entry->getTeacher().patronymic, teacherPatrValue.c_str()) != 0) {
                    match = false;
                } else if (operation == NEQ && std::strcmp(entry->getTeacher().patronymic, teacherPatrValue.c_str()) == 0) {
                    match = false;
                }
                break;
            }
            case GROUP: {
                int groupValue = std::get<int>(value);
                if (operation == EQ && entry->getGroup() != groupValue) {
                    match = false;
                } else if (operation == NEQ && entry->getGroup() == groupValue) {
                    match = false;
                } else if (operation == LT && entry->getGroup() >= groupValue) {
                    match = false;
                } else if (operation == GT && entry->getGroup() <= groupValue) {
                    match = false;
                } else if (operation == LT_EQ && entry->getGroup() > groupValue) {
                    match = false;
                } else if (operation == GT_EQ && entry->getGroup() < groupValue) {
                    match = false;
                }
                break;
            }
            default:
                break;
            }
        }
        if (match) {
            reselectedEntries.push_back(entry);
        }
    }
    return reselectedEntries;
}

void Schedule::print(const std::vector<Entry*>& entries) {
    for (Entry* entry : entries) {
        std::cout << "Time: " << entry->getTime().startHour << ":" << entry->getTime().startMinute << "-" << entry->getTime().endHour << ":" << entry->getTime().endMinute
            << ", Room: " << entry->getRoom()
            << ", Subject: " << entry->getSubjectName()
            << ", Teacher: " << entry->getTeacher().surname << " " << entry->getTeacher().name << " " << entry->getTeacher().patronymic
            << ", Group: " << entry->getGroup() << std::endl;
    }
}

void Schedule::saveToFile(FILE* fout) {
    if (!fout) {
        throw Exception(2, "File is not open for writing");
    }

    for (Entry* entry : schedule_) {
        TimeHM time = entry->getTime();
        int room = entry->getRoom();
        const char* subjectName = entry->getSubjectName();
        FullName teacher = entry->getTeacher();
        int group = entry->getGroup();

        fprintf(fout, "%02d:%02d-%02d:%02d,%d,%s,%s,%s,%s,%d\n",
                time.startHour, time.startMinute, time.endHour, time.endMinute,
                room, subjectName, teacher.surname, teacher.name, teacher.patronymic, group);
    }
}

std::vector<Entry*> Schedule::deleteEntries(const std::vector<Cond>& crit) {
    std::vector<Entry*> deletedEntries;
    std::vector<Entry*> remainingEntries; 

    for (Entry* entry : schedule_) {
        bool match = true;
        for (const Cond& condition : crit) {
            Field field = condition.getField();
            BinOp operation = condition.getOperation();
            Value value = condition.getVal();

            switch (field) {
             case TIME:{
                  TimeHM timeValue = std::get<TimeHM>(value);
                    if (operation == EQ &&
                        (entry->getTime().startHour != timeValue.startHour ||
                         entry->getTime().startMinute != timeValue.startMinute ||
                         entry->getTime().endHour != timeValue.endHour ||
                         entry->getTime().endMinute != timeValue.endMinute)) {
                        match = false;
                    }
                  break;
            }
            case ROOM: {
                int roomValue = std::get<int>(value);
                if (operation == EQ && entry->getRoom() != roomValue) {
                    match = false;
                } else if (operation == NEQ && entry->getRoom() == roomValue) {
                    match = false;
                } else if (operation == LT && entry->getRoom() >= roomValue) {
                    match = false;
                } else if (operation == GT && entry->getRoom() <= roomValue) {
                    match = false;
                } else if (operation == LT_EQ && entry->getRoom() > roomValue) {
                    match = false;
                } else if (operation == GT_EQ && entry->getRoom() < roomValue) {
                    match = false;
                }
                break;
            }
            case SUBJNAME: {
                std::string subjNameValue = std::get<std::string>(value);
                if (operation == LIKE) {
                    std::regex pattern(subjNameValue);
                    if (!std::regex_match(entry->getSubjectName(), pattern)) {
                        match = false;
                    }
                } else if (operation == EQ && std::strcmp(entry->getSubjectName(), subjNameValue.c_str()) != 0) {
                    match = false;
                } else if (operation == NEQ && std::strcmp(entry->getSubjectName(), subjNameValue.c_str()) == 0) {
                    match = false;
                }
                break;
            }
               case TEACHERNAME: {
                std::string teacherNameValue = std::get<std::string>(value);
                if (operation == EQ && std::strcmp(entry->getTeacher().name, teacherNameValue.c_str()) != 0) {
                    match = false;
                } else if (operation == NEQ && std::strcmp(entry->getTeacher().name, teacherNameValue.c_str()) == 0) {
                    match = false;
                }
                break;
            }
            case TEACHERLASTNAME: {
                std::string teacherLastNameValue = std::get<std::string>(value);
                if (operation == EQ && std::strcmp(entry->getTeacher().surname, teacherLastNameValue.c_str()) != 0) {
                    match = false;
                } else if (operation == NEQ && std::strcmp(entry->getTeacher().surname, teacherLastNameValue.c_str()) == 0) {
                    match = false;
                }
                break;
            }
            case TEACHERPATR: {
                std::string teacherPatrValue = std::get<std::string>(value);
                if (operation == EQ && std::strcmp(entry->getTeacher().patronymic, teacherPatrValue.c_str()) != 0) {
                    match = false;
                } else if (operation == NEQ && std::strcmp(entry->getTeacher().patronymic, teacherPatrValue.c_str()) == 0) {
                    match = false;
                }
                break;
            }
            case GROUP: {
                int groupValue = std::get<int>(value);
                if (operation == EQ && entry->getGroup() != groupValue) {
                    match = false;
                } else if (operation == NEQ && entry->getGroup() == groupValue) {
                    match = false;
                } else if (operation == LT && entry->getGroup() >= groupValue) {
                    match = false;
                } else if (operation == GT && entry->getGroup() <= groupValue) {
                    match = false;
                } else if (operation == LT_EQ && entry->getGroup() > groupValue) {
                    match = false;
                } else if (operation == GT_EQ && entry->getGroup() < groupValue) {
                    match = false;
                }
                break;
            }
            default:
                break;
            }
        }
        if (match) {
            deletedEntries.push_back(entry);
            delete entry; 
        } else {
            remainingEntries.push_back(entry); 
        }
    }
    schedule_ = remainingEntries; 
    return deletedEntries;
}
