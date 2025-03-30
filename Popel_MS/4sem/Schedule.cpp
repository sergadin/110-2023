#include "Schedule.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

Schedule::Schedule() : schedule_() {}

Schedule::Schedule(FILE* fin) : schedule_() {
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
}

Schedule::~Schedule() {
    for (Entry* entry : schedule_) {
        delete entry;
    }
    schedule_.clear();
}

bool Schedule::checkTimeCross(const Date& date1, const Date& date2) {
    return date1.day == date2.day && date1.month == date2.month;
}


void Schedule::addEntry(Entry* entry) {
     for (Entry* existingEntry : schedule_) {
        if (existingEntry->getRoom() == entry->getRoom() && checkTimeCross(existingEntry->getDate(), entry->getDate())) {
            //std::cerr << "Error: Time conflict with existing entry in room " << entry->getRoom() << std::endl;
            delete entry; 
            return;
        }
    }
    schedule_.push_back(entry);
    //buildInd();
}

void Schedule::deleteEntry(const Date& date, int lesson, int room) {
    for (auto it = schedule_.begin(); it != schedule_.end(); ++it) {
        if ((*it)->getDate().day == date.day && (*it)->getDate().month == date.month &&
            (*it)->getLesson() == lesson && (*it)->getRoom() == room) {
            delete *it;
            schedule_.erase(it);
            break;
        }
    }
}

void Schedule::updateEntry(const Date& date, int lesson, int room, Entry* newEntry) {
    for (Entry* entry : schedule_) {
        if (entry->getDate().day == date.day && entry->getDate().month == date.month &&
            entry->getLesson() == lesson && entry->getRoom() == room) {
            *entry = *newEntry;
            break;
        }
    }
}


std::vector<Entry*> Schedule::select(const std::vector<Cond>& crit) {
    std::vector<Entry*> result;
    for (Entry* entry : schedule_) {
        bool match = true;
        for (const Cond& condition : crit) {
            Field field = condition.getField();
            BinOp operation = condition.getOperation();
            Value value = condition.getVal();

            switch (field) {
                case DAY: {
                    Date date = entry->getDate();
                    Date condDate = std::get<Date>(value);
                    if (!compareDates(date, condDate, operation)) {
                        match = false;
                    }
                    break;
                }
                case LESSON_NUM: {
                    int lesson = entry->getLesson();
                    int condLessonNum = std::get<int>(value);
                    if (!compareLessons(lesson, condLessonNum, operation)) {
                        match = false;
                    }
                    break;
                }
                case ROOM: {
                    int room = entry->getRoom();
                    int condRoom = std::get<int>(value);
                    if (!compareInts(room, condRoom, operation)) {
                        match = false;
                    }
                    break;
                }
                case SUBJNAME: {
                    const char* subject = entry->getSubjectName();
                    std::string condSubject = std::get<std::string>(value);
                    if (!compareStrings(subject, condSubject, operation)) {
                        match = false;
                    }
                    break;
                }
                case TEACHERNAME: {
                    FullName teacher = entry->getTeacher();
                    std::string condName = std::get<std::string>(value);
                    if (!compareStrings(teacher.name, condName, operation)) {
                        match = false;
                    }
                    break;
                }
                case TEACHERLASTNAME: {
                    FullName teacher = entry->getTeacher();
                    std::string condSurname = std::get<std::string>(value);
                    if (!compareStrings(teacher.surname, condSurname, operation)) {
                        match = false;
                    }
                    break;
                }
                case TEACHERPATR: {
                    FullName teacher = entry->getTeacher();
                    std::string condPatronymic = std::get<std::string>(value);
                    if (!compareStrings(teacher.patronymic, condPatronymic, operation)) {
                        match = false;
                    }
                    break;
                }
                case GROUP: {
                    int group = entry->getGroup();
                    int condGroup = std::get<int>(value);
                    if (!compareInts(group, condGroup, operation)) {
                        match = false;
                    }
                    break;
                }
                default:
                    break;
            }
        }
        if (match) {
            result.push_back(entry);
        }
    }
    return result;
}

std::vector<Entry*> Schedule::reselect(const std::vector<Entry*>& selected, const std::vector<Cond>& crit) {
    std::vector<Entry*> result;
    for (Entry* entry : selected) {
        bool match = true;
        for (const Cond& condition : crit) {
            Field field = condition.getField();
            BinOp operation = condition.getOperation();
            Value value = condition.getVal();

            switch (field) {
                case DAY: {
                    Date date = entry->getDate();
                    Date condDate = std::get<Date>(value);
                    if (!compareDates(date, condDate, operation)) {
                        match = false;
                    }
                    break;
                }
                case LESSON_NUM: {
                    int lesson = entry->getLesson();
                    int condLessonNum = std::get<int>(value);
                    if (!compareLessons(lesson, condLessonNum, operation)) {
                        match = false;
                    }
                    break;
                }
                case ROOM: {
                    int room = entry->getRoom();
                    int condRoom = std::get<int>(value);
                    if (!compareInts(room, condRoom, operation)) {
                        match = false;
                    }
                    break;
                }
                case SUBJNAME: {
                    const char* subject = entry->getSubjectName();
                    std::string condSubject = std::get<std::string>(value);
                    if (!compareStrings(subject, condSubject, operation)) {
                        match = false;
                    }
                    break;
                }
                case TEACHERNAME: {
                    FullName teacher = entry->getTeacher();
                    std::string condName = std::get<std::string>(value);
                    if (!compareStrings(teacher.name, condName, operation)) {
                        match = false;
                    }
                    break;
                }
                case TEACHERLASTNAME: {
                    FullName teacher = entry->getTeacher();
                    std::string condSurname = std::get<std::string>(value);
                    if (!compareStrings(teacher.surname, condSurname, operation)) {
                        match = false;
                    }
                    break;
                }
                case TEACHERPATR: {
                    FullName teacher = entry->getTeacher();
                    std::string condPatronymic = std::get<std::string>(value);
                    if (!compareStrings(teacher.patronymic, condPatronymic, operation)) {
                        match = false;
                    }
                    break;
                }
                case GROUP: {
                    int group = entry->getGroup();
                    int condGroup = std::get<int>(value);
                    if (!compareInts(group, condGroup, operation)) {
                        match = false;
                    }
                    break;
                }
                default:
                    break;
            }
        }
        if (match) {
            result.push_back(entry);
        }
    }
    return result;
}

void Schedule::print(const std::vector<Entry*>& entries) {
    for (Entry* entry : entries) {
        std::cout << "Date: " << entry->getDate().day << "." << entry->getDate().month
                  << ", Lesson: " << entry->getLesson()
                  << ", Room: " << entry->getRoom()
                  << ", Subject: " << entry->getSubjectName()
                  << ", Teacher: " << entry->getTeacher().surname << " " << entry->getTeacher().name << " " << entry->getTeacher().patronymic
                  << ", Group: " << entry->getGroup() << std::endl;
    }
}

void Schedule::saveToFile(FILE* fout) {
    for (Entry* entry : schedule_) {
        fprintf(fout, "%d %d %d %d %s %s %s %s %d\n",
                entry->getDate().day, entry->getDate().month, entry->getLesson(), entry->getRoom(),
                entry->getTeacher().surname, entry->getTeacher().name, entry->getTeacher().patronymic,
                entry->getSubjectName(), entry->getGroup());
    }
}

std::vector<Entry*> Schedule::deleteEntries(const std::vector<Cond>& crit) {
    std::vector<Entry*> deletedEntries;
    for (auto it = schedule_.begin(); it != schedule_.end();) {
        bool match = true;
        for (const Cond& condition : crit) {
            Field field = condition.getField();
            BinOp operation = condition.getOperation();
            Value value = condition.getVal();

            switch (field) {
                case DAY: {
                    Date date = (*it)->getDate();
                    Date condDate = std::get<Date>(value);
                    if (!compareDates(date, condDate, operation)) {
                        match = false;
                    }
                    break;
                }
                case LESSON_NUM: {
                    int lesson = (*it)->getLesson();
                    int condLessonNum = std::get<int>(value);
                    if (!compareLessons(lesson, condLessonNum, operation)) {
                        match = false;
                    }
                    break;
                }
                case ROOM: {
                    int room = (*it)->getRoom();
                    int condRoom = std::get<int>(value);
                    if (!compareInts(room, condRoom, operation)) {
                        match = false;
                    }
                    break;
                }
                case SUBJNAME: {
                    const char* subject = (*it)->getSubjectName();
                    std::string condSubject = std::get<std::string>(value);
                    if (!compareStrings(subject, condSubject, operation)) {
                        match = false;
                    }
                    break;
                }
                case TEACHERNAME: {
                    FullName teacher = (*it)->getTeacher();
                    std::string condName = std::get<std::string>(value);
                    if (!compareStrings(teacher.name, condName, operation)) {
                        match = false;
                    }
                    break;
                }
                case TEACHERLASTNAME: {
                    FullName teacher = (*it)->getTeacher();
                    std::string condSurname = std::get<std::string>(value);
                    if (!compareStrings(teacher.surname, condSurname, operation)) {
                        match = false;
                    }
                    break;
                }
                case TEACHERPATR: {
                    FullName teacher = (*it)->getTeacher();
                    std::string condPatronymic = std::get<std::string>(value);
                    if (!compareStrings(teacher.patronymic, condPatronymic, operation)) {
                        match = false;
                    }
                    break;
                }
                case GROUP: {
                    int group = (*it)->getGroup();
                    int condGroup = std::get<int>(value);
                    if (!compareInts(group, condGroup, operation)) {
                        match = false;
                    }
                    break;
                }
                default:
                    break;
            }
        }
        if (match) {
            deletedEntries.push_back(*it);
            delete *it;
            it = schedule_.erase(it);
        } else {
            ++it;
        }
    }
    return deletedEntries;
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
