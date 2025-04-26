#include "Schedule.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>

Schedule::Schedule() : schedule_(), teacher_index_(), group_index_(), room_index_(), lesson_index_(), subject_index_() {
    loadFromFile("schedule.txt");
    buildIndexes();
}

void Schedule::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    int day, month, lesson, room, group;
    char subject_name[128];
    std::string teacher;
    while (file >> day >> month >> lesson >> room >> subject_name >> teacher >> group) {
        Entry* entry = new Entry(day, month, lesson, room, subject_name, teacher, group);
        schedule_.push_back(entry);
    }

    file.close();
}

Schedule::~Schedule() {
    for (Entry* entry : schedule_) {
        delete entry;
    }
    schedule_.clear();
}

void Schedule::buildIndexes() {
    teacher_index_.clear();
    group_index_.clear();
    room_index_.clear();
    lesson_index_.clear();
    subject_index_.clear();

    for (size_t i = 0; i < schedule_.size(); ++i) {
        Entry* entry = schedule_[i];
        std::string teacher = entry->getTeacher();
        std::string teacherKey = teacher;
        teacher_index_[teacherKey].push_back(i);
        group_index_[entry->getGroup()].push_back(i);
        room_index_[entry->getRoom()].push_back(i);
        lesson_index_[entry->getLesson()].push_back(i);
        subject_index_[entry->getSubjectName()].push_back(i);
    }
}

bool Schedule::checkTimeCross(int day, int month, int lesson, std::string teacher, int room, int group) {
    for (const auto& entry : schedule_) {
        if (entry->getDay() == day && entry->getMonth() == month && entry->getLesson() == lesson) {
            if (entry->getRoom() == room || entry->getGroup() == group || entry->getTeacher() == teacher) {
                return true;
            }
        }
    }
    return false;
}

void Schedule::addEntry(Entry* entry) {
    if (checkTimeCross(entry->getDay(), entry->getMonth(), entry->getLesson(), entry->getTeacher(), entry->getRoom(), entry->getGroup())) {
        delete entry;
        return;
    }
    schedule_.push_back(entry);
    buildIndexes();
}

void Schedule::deleteEntry(int day, int month, int lesson, int room) {
    auto it = std::remove_if(schedule_.begin(), schedule_.end(), [&](Entry* entry) {
        return entry->getDay() == day && entry->getMonth() == month && entry->getLesson() == lesson && entry->getRoom() == room;
    });

    for (auto iter = it; iter != schedule_.end(); ++iter) {
        delete *iter;
    }

    schedule_.erase(it, schedule_.end());
    buildIndexes();
}

void Schedule::updateEntry(int day, int month, int lesson, int room, Entry* newEntry) {
    for (Entry* entry : schedule_) {
        if (entry->getDay() == day && entry->getMonth() == month && entry->getLesson() == lesson && entry->getRoom() == room) {
            *entry = *newEntry;
            break;
        }
    }
    buildIndexes();
}

std::vector<Entry*> Schedule::select(const std::vector<Cond>& crit) {
    if (crit.empty()) {
        return schedule_;
    }

    std::unordered_set<int> result_indices;
    bool first = true;

    for (const auto& cond : crit) {
        std::unordered_set<int> current_indices;
        switch (cond.getField()) {
            case TEACHERNAME: {
                std::string teacher = std::get<std::string>(cond.getVal());
                for (size_t i = 0; i < schedule_.size(); ++i) {
                    if (compareStrings(schedule_[i]->getTeacher(), teacher, cond.getOperation())) {
                        current_indices.insert(i);
                    }
                }
                break;
            }
            case GROUP: {
                try {
                    int group = std::get<int>(cond.getVal());
                    for (const auto& pair : group_index_) {
                        if (compareInts(pair.first, group, cond.getOperation())) {
                            current_indices.insert(pair.second.begin(), pair.second.end());
                        }
                    }
                } catch (const std::bad_variant_access&) {
                    std::string groupStr = std::get<std::string>(cond.getVal());
                    for (const auto& pair : group_index_) {
                        if (compareIntStr(std::to_string(pair.first), groupStr, cond.getOperation())) {
                            current_indices.insert(pair.second.begin(), pair.second.end());
                        }
                    }
                }
                break;
            }
            case ROOM: {
                try {
                    int room = std::get<int>(cond.getVal());
                    for (const auto& pair : room_index_) {
                        if (compareInts(pair.first, room, cond.getOperation())) {
                            current_indices.insert(pair.second.begin(), pair.second.end());
                        }
                    }
                } catch (const std::bad_variant_access&) {
                    std::string roomStr = std::get<std::string>(cond.getVal());
                    for (const auto& pair : room_index_) {
                        if (compareIntStr(std::to_string(pair.first), roomStr, cond.getOperation())) {
                            current_indices.insert(pair.second.begin(), pair.second.end());
                        }
                    }
                }
                break;
            }
            case LESSON_NUM: {
                try {
                    int lesson = std::get<int>(cond.getVal());
                    for (const auto& pair : lesson_index_) {
                        if (compareInts(pair.first, lesson, cond.getOperation())) {
                            current_indices.insert(pair.second.begin(), pair.second.end());
                        }
                    }
                } catch (const std::bad_variant_access&) {
                    std::string lessonStr = std::get<std::string>(cond.getVal());
                    for (const auto& pair : lesson_index_) {
                        if (compareIntStr(std::to_string(pair.first), lessonStr, cond.getOperation())) {
                            current_indices.insert(pair.second.begin(), pair.second.end());
                        }
                    }
                }
                break;
            }
            case SUBJNAME: {
                std::string subject = std::get<std::string>(cond.getVal());
                for (size_t i = 0; i < schedule_.size(); ++i) {
                    if (compareStrings(schedule_[i]->getSubjectName(), subject, cond.getOperation())) {
                        current_indices.insert(i);
                    }
                }
                break;
            }
            case DAY: {
                try {
                    int day = std::get<int>(cond.getVal());
                    for (size_t i = 0; i < schedule_.size(); ++i) {
                        if (compareInts(schedule_[i]->getDay(), day, cond.getOperation())) {
                            current_indices.insert(i);
                        }
                    }
                } catch (const std::bad_variant_access&) {
                    std::string dayStr = std::get<std::string>(cond.getVal());
                    for (size_t i = 0; i < schedule_.size(); ++i) {
                        if (compareIntStr(std::to_string(schedule_[i]->getDay()), dayStr, cond.getOperation())) {
                            current_indices.insert(i);
                        }
                    }
                }
                break;
            }
            case MONTH: {
                try {
                    int month = std::get<int>(cond.getVal());
                    for (size_t i = 0; i < schedule_.size(); ++i) {
                        if (compareInts(schedule_[i]->getMonth(), month, cond.getOperation())) {
                            current_indices.insert(i);
                        }
                    }
                } catch (const std::bad_variant_access&) {
                    std::string monthStr = std::get<std::string>(cond.getVal());
                    for (size_t i = 0; i < schedule_.size(); ++i) {
                        if (compareIntStr(std::to_string(schedule_[i]->getMonth()), monthStr, cond.getOperation())) {
                            current_indices.insert(i);
                        }
                    }
                }
                break;
            }
            default:
                break;
        }

        if (first) {
            result_indices = current_indices;
            first = false;
        } else {
            std::unordered_set<int> intersection;
            std::set_intersection(result_indices.begin(), result_indices.end(),
                                  current_indices.begin(), current_indices.end(),
                                  std::inserter(intersection, intersection.begin()));
            result_indices = intersection;
        }
    }

    std::vector<Entry*> result;
    for (int index : result_indices) {
        result.push_back(schedule_[index]);
    }
    return result;
}

std::vector<Entry*> Schedule::reselect(const std::vector<Entry*>& selected, const std::vector<Cond>& crit) {
    if (crit.empty()) {
        return selected;
    }

    std::unordered_set<int> selected_indices;
    for (const auto& entry : selected) {
        selected_indices.insert(std::find(schedule_.begin(), schedule_.end(), entry) - schedule_.begin());
    }

    std::unordered_set<int> result_indices;
    bool first = true;

    for (const auto& cond : crit) {
        std::unordered_set<int> current_indices;
        switch (cond.getField()) {
            case TEACHERNAME: {
                std::string teacher = std::get<std::string>(cond.getVal());
                for (size_t i = 0; i < schedule_.size(); ++i) {
                    if (compareStrings(schedule_[i]->getTeacher(), teacher, cond.getOperation())) {
                        current_indices.insert(i);
                    }
                }
                break;
            }
            case GROUP: {
                try {
                    int group = std::get<int>(cond.getVal());
                    for (const auto& pair : group_index_) {
                        if (compareInts(pair.first, group, cond.getOperation())) {
                            current_indices.insert(pair.second.begin(), pair.second.end());
                        }
                    }
                } catch (const std::bad_variant_access&) {
                    std::string groupStr = std::get<std::string>(cond.getVal());
                    for (const auto& pair : group_index_) {
                        if (compareIntStr(std::to_string(pair.first), groupStr, cond.getOperation())) {
                            current_indices.insert(pair.second.begin(), pair.second.end());
                        }
                    }
                }
                break;
            }
            case ROOM: {
                try {
                    int room = std::get<int>(cond.getVal());
                    for (const auto& pair : room_index_) {
                        if (compareInts(pair.first, room, cond.getOperation())) {
                            current_indices.insert(pair.second.begin(), pair.second.end());
                        }
                    }
                } catch (const std::bad_variant_access&) {
                    std::string roomStr = std::get<std::string>(cond.getVal());
                    for (const auto& pair : room_index_) {
                        if (compareIntStr(std::to_string(pair.first), roomStr, cond.getOperation())) {
                            current_indices.insert(pair.second.begin(), pair.second.end());
                        }
                    }
                }
                break;
            }
            case LESSON_NUM: {
                try {
                    int lesson = std::get<int>(cond.getVal());
                    for (const auto& pair : lesson_index_) {
                        if (compareInts(pair.first, lesson, cond.getOperation())) {
                            current_indices.insert(pair.second.begin(), pair.second.end());
                        }
                    }
                } catch (const std::bad_variant_access&) {
                    std::string lessonStr = std::get<std::string>(cond.getVal());
                    for (const auto& pair : lesson_index_) {
                        if (compareIntStr(std::to_string(pair.first), lessonStr, cond.getOperation())) {
                            current_indices.insert(pair.second.begin(), pair.second.end());
                        }
                    }
                }
                break;
            }
            case SUBJNAME: {
                std::string subject = std::get<std::string>(cond.getVal());
                for (size_t i = 0; i < schedule_.size(); ++i) {
                    if (compareStrings(schedule_[i]->getSubjectName(), subject, cond.getOperation())) {
                        current_indices.insert(i);
                    }
                }
                break;
            }
            case DAY: {
                try {
                    int day = std::get<int>(cond.getVal());
                    for (size_t i = 0; i < schedule_.size(); ++i) {
                        if (compareInts(schedule_[i]->getDay(), day, cond.getOperation())) {
                            current_indices.insert(i);
                        }
                    }
                } catch (const std::bad_variant_access&) {
                    std::string dayStr = std::get<std::string>(cond.getVal());
                    for (size_t i = 0; i < schedule_.size(); ++i) {
                        if (compareIntStr(std::to_string(schedule_[i]->getDay()), dayStr, cond.getOperation())) {
                            current_indices.insert(i);
                        }
                    }
                }
                break;
            }
            case MONTH: {
                try {
                    int month = std::get<int>(cond.getVal());
                    for (size_t i = 0; i < schedule_.size(); ++i) {
                        if (compareInts(schedule_[i]->getMonth(), month, cond.getOperation())) {
                            current_indices.insert(i);
                        }
                    }
                } catch (const std::bad_variant_access&) {
                    std::string monthStr = std::get<std::string>(cond.getVal());
                    for (size_t i = 0; i < schedule_.size(); ++i) {
                        if (compareIntStr(std::to_string(schedule_[i]->getMonth()), monthStr, cond.getOperation())) {
                            current_indices.insert(i);
                        }
                    }
                }
                break;
            }
            default:
                break;
        }

        if (first) {
            result_indices = current_indices;
            first = false;
        } else {
            std::unordered_set<int> intersection;
            std::set_intersection(result_indices.begin(), result_indices.end(),
                                  current_indices.begin(), current_indices.end(),
                                  std::inserter(intersection, intersection.begin()));
            result_indices = intersection;
        }
    }

    std::unordered_set<int> final_indices;
    std::set_intersection(result_indices.begin(), result_indices.end(),
                          selected_indices.begin(), selected_indices.end(),
                          std::inserter(final_indices, final_indices.begin()));

    std::vector<Entry*> result;
    for (int index : final_indices) {
        result.push_back(schedule_[index]);
    }
    return result;
}
void Schedule::print(const std::vector<Entry*>& entries) {
    for (const auto& entry : entries) {
        std::cout << entry->toString() << std::endl;
    }
}

void Schedule::saveToFile(std::ofstream& fout) {
    for (const auto& entry : schedule_) {
        fout << entry->getDay() << " " << entry->getMonth() << " "
             << entry->getLesson() << " " << entry->getRoom() << " "
             << entry->getSubjectName() << " "
             << entry->getTeacher() << " "
             << entry->getGroup() << std::endl;
    }
}

std::vector<Entry*> Schedule::deleteEntries(const std::vector<Cond>& crit) {
    std::vector<Entry*> result = select(crit);
    for (const auto& entry : result) {
        schedule_.erase(std::remove(schedule_.begin(), schedule_.end(), entry), schedule_.end());
        delete entry;
    }
    buildIndexes();
    return result;
}

bool compareDates(int day1, int month1, int day2, int month2, BinOp operation) {
    switch (operation) {
        case EQ:
            return day1 == day2 && month1 == month2;
        case NEQ:
            return day1 != day2 || month1 != month2;
        case LT:
            return month1 < month2 || (month1 == month2 && day1 < day2);
        case GT:
            return month1 > month2 || (month1 == month2 && day1 > day2);
        case LT_EQ:
            return month1 < month2 || (month1 == month2 && day1 <= day2);
        case GT_EQ:
            return month1 > month2 || (month1 == month2 && day1 >= day2);
        default:
            return false;
    }
}

bool compareLessons(int lesson, int lessonNum, BinOp operation) {
    switch (operation) {
        case EQ:
            return lesson == lessonNum;
        case NEQ:
            return lesson != lessonNum;
        case LT:
            return lesson < lessonNum;
        case GT:
            return lesson > lessonNum;
        case LT_EQ:
            return lesson <= lessonNum;
        case GT_EQ:
            return lesson >= lessonNum;
        default:
            return false;
    }
}

bool compareInts(int val1, int val2, BinOp operation) {
    switch (operation) {
        case EQ:
            return val1 == val2;
        case NEQ:
            return val1 != val2;
        case LT:
            return val1 < val2;
        case GT:
            return val1 > val2;
        case LT_EQ:
            return val1 <= val2;
        case GT_EQ:
            return val1 >= val2;
        default:
            return false;
    }
}

bool compareStrings(const std::string& str1, const std::string& str2, BinOp operation) {
    switch (operation) {
        case EQ:
            return str1 == str2;
        case NEQ:
            return str1 != str2;
        case LT:
            return str1 < str2;
        case GT:
            return str1 > str2;
        case LT_EQ:
            return str1 <= str2;
        case GT_EQ:
            return str1 >= str2;
        case LIKE: {
            std::string pattern = str2;
            std::string regexPattern="^";
            for (char c : pattern) {
                if (c == '*') {
                    regexPattern += ".";
                } else if (c == '^') {
                    regexPattern += ".*";
                } else {
                    regexPattern += std::regex_replace(std::string(1, c), std::regex("\\W"), "\\$&");
                }
            }
            regexPattern += "$";
            std::regex re(regexPattern);
            return std::regex_search(str1, re);
        }
        default:
            return false;
    }
}

bool compareIntStr(const std::string& str1, const std::string& str2, BinOp operation) {
    switch (operation) {
        case LIKE: {
            std::string pattern = str2;
            std::string regexPattern="^";
            for (char c : pattern) {
                if (c == '*') {
                    regexPattern += ".";
                } else if (c == '^') {
                    regexPattern += ".*";
                } else {
                    regexPattern += std::regex_replace(std::string(1, c), std::regex("\\W"), "\\$&");
                }
            }
            regexPattern += "$";
            std::regex re(regexPattern);
            return std::regex_search(str1, re);
        }
        default:
            return false;
    }
}
