#include "Schedule.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>

Schedule::Schedule() : schedule_(), teacher_index_(), group_index_(), room_index_(), lesson_index_(), subject_index_() {
    buildIndexes();
}

Schedule::Schedule(FILE* fin) : schedule_(), teacher_index_(), group_index_(), room_index_(), lesson_index_(), subject_index_() {
    if (fin) {
        Date date;
        int lesson;
        int room;
        char subject_name[128];
        FullName teacher;
        int group;

        while (fscanf(fin, "%d %d %d %d %63s %31s %63s %127s %d",
                       &date.day, &date.month, &lesson, &room,
                       teacher.surname, teacher.name, teacher.patronymic,
                       subject_name, &group) == 9) {
            Entry* newEntry = new Entry(date, lesson, room, subject_name, teacher, group);
            schedule_.push_back(newEntry);
        }
    }

    buildIndexes();
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
        FullName teacher = entry->getTeacher();
        std::string teacherKey = std::string(teacher.surname) + " " + teacher.name + " " + teacher.patronymic;
        teacher_index_[teacherKey].push_back(i);
        group_index_[entry->getGroup()].push_back(i);
        room_index_[entry->getRoom()].push_back(i);
        lesson_index_[entry->getLesson()].push_back(i);
        subject_index_[entry->getSubjectName()].push_back(i);
    }
}

bool Schedule::checkTimeCross(const Date& date, int lesson, const FullName& teacher, int room, int group) {
    for (const auto& entry : schedule_) {
        if (entry->getDate().day == date.day && entry->getDate().month == date.month &&
            entry->getLesson() == lesson) {
            if (entry->getRoom() == room || entry->getGroup() == group ||
                (strcmp(entry->getTeacher().surname, teacher.surname) == 0 &&
                 strcmp(entry->getTeacher().name, teacher.name) == 0 &&
                 strcmp(entry->getTeacher().patronymic, teacher.patronymic) == 0)) {
                return true;
            }
        }
    }
    return false;
}

void Schedule::addEntry(Entry* entry) {
    if (checkTimeCross(entry->getDate(), entry->getLesson(), entry->getTeacher(), entry->getRoom(), entry->getGroup())) {
        delete entry;
        return;
    }
    schedule_.push_back(entry);
    buildIndexes();
}

void Schedule::deleteEntry(const Date& date, int lesson, int room) {
    auto it = std::remove_if(schedule_.begin(), schedule_.end(), [&](Entry* entry) {
        return entry->getDate().day == date.day && entry->getDate().month == date.month &&
               entry->getLesson() == lesson && entry->getRoom() == room;
    });

    for (auto iter = it; iter != schedule_.end(); ++iter) {
        delete *iter;
    }

    schedule_.erase(it, schedule_.end());
    buildIndexes();
}

void Schedule::updateEntry(const Date& date, int lesson, int room, Entry* newEntry) {
    for (Entry* entry : schedule_) {
        if (entry->getDate().day == date.day && entry->getDate().month == date.month &&
            entry->getLesson() == lesson && entry->getRoom() == room) {
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
            case TEACHERNAME:
            case TEACHERPATR:
            case TEACHERLASTNAME: {
                std::string teacherKey = std::get<std::string>(cond.getVal());
                auto it = teacher_index_.find(teacherKey);
                if (it != teacher_index_.end()) {
                    current_indices.insert(it->second.begin(), it->second.end());
                }
                break;
            }
            case GROUP: {
                int group = std::get<int>(cond.getVal());
                auto it = group_index_.find(group);
                if (it != group_index_.end()) {
                    current_indices.insert(it->second.begin(), it->second.end());
                }
                break;
            }
            case ROOM: {
                int room = std::get<int>(cond.getVal());
                auto it = room_index_.find(room);
                if (it != room_index_.end()) {
                    current_indices.insert(it->second.begin(), it->second.end());
                }
                break;
            }
            case LESSON_NUM: {
                int lesson = std::get<int>(cond.getVal());
                auto it = lesson_index_.find(lesson);
                if (it != lesson_index_.end()) {
                    current_indices.insert(it->second.begin(), it->second.end());
                }
                break;
            }
            case SUBJNAME: {
                std::string subject = std::get<std::string>(cond.getVal());
                auto it = subject_index_.find(subject);
                if (it != subject_index_.end()) {
                    current_indices.insert(it->second.begin(), it->second.end());
                }
                break;
            }
            case DAY: {
                Date date = std::get<Date>(cond.getVal());
                for (size_t i = 0; i < schedule_.size(); ++i) {
                    if (schedule_[i]->getDate().day == date.day && schedule_[i]->getDate().month == date.month) {
                        current_indices.insert(i);
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
    std::unordered_set<int> selected_indices;
    for (const auto& entry : selected) {
        selected_indices.insert(std::find(schedule_.begin(), schedule_.end(), entry) - schedule_.begin());
    }

    if (crit.empty()) {
        return selected;
    }

    std::unordered_set<int> result_indices;
    bool first = true;

    for (const auto& cond : crit) {
        std::unordered_set<int> current_indices;
        switch (cond.getField()) {
            case TEACHERNAME:
            case TEACHERPATR:
            case TEACHERLASTNAME: {
                std::string teacherKey = std::get<std::string>(cond.getVal());
                auto it = teacher_index_.find(teacherKey);
                if (it != teacher_index_.end()) {
                    current_indices.insert(it->second.begin(), it->second.end());
                }
                break;
            }
            case GROUP: {
                int group = std::get<int>(cond.getVal());
                auto it = group_index_.find(group);
                if (it != group_index_.end()) {
                    current_indices.insert(it->second.begin(), it->second.end());
                }
                break;
            }
            case ROOM: {
                int room = std::get<int>(cond.getVal());
                auto it = room_index_.find(room);
                if (it != room_index_.end()) {
                    current_indices.insert(it->second.begin(), it->second.end());
                }
                break;
            }
            case LESSON_NUM: {
                int lesson = std::get<int>(cond.getVal());
                auto it = lesson_index_.find(lesson);
                if (it != lesson_index_.end()) {
                    current_indices.insert(it->second.begin(), it->second.end());
                }
                break;
            }
            case SUBJNAME: {
                std::string subject = std::get<std::string>(cond.getVal());
                auto it = subject_index_.find(subject);
                if (it != subject_index_.end()) {
                    current_indices.insert(it->second.begin(), it->second.end());
                }
                break;
            }
            case DAY: {
                Date date = std::get<Date>(cond.getVal());
                for (size_t i = 0; i < schedule_.size(); ++i) {
                    if (schedule_[i]->getDate().day == date.day && schedule_[i]->getDate().month == date.month) {
                        current_indices.insert(i);
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
        fout << entry->getDate().day << " " << entry->getDate().month << " "
             << entry->getLesson() << " " << entry->getRoom() << " "
             << entry->getSubjectName() << " "
             << entry->getTeacher().surname << " " << entry->getTeacher().name << " " << entry->getTeacher().patronymic << " "
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

bool compareDates(const Date& date1, const Date& date2, BinOp operation) {
    switch (operation) {
        case EQ:
            return date1.day == date2.day && date1.month == date2.month;
        case NEQ:
            return date1.day != date2.day || date1.month != date2.month;
        case LT:
            return date1.month < date2.month || (date1.month == date2.month && date1.day < date2.day);
        case GT:
            return date1.month > date2.month || (date1.month == date2.month && date1.day > date2.day);
        case LT_EQ:
            return date1.month < date2.month || (date1.month == date2.month && date1.day <= date2.day);
        case GT_EQ:
            return date1.month > date2.month || (date1.month == date2.month && date1.day >= date2.day);
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
        case LIKE:
            return str1.find(str2) != std::string::npos;
        default:
            return false;
    }
}
