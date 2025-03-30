#include <iostream>
#include <sstream>
#include <regex>

#include "Schedule.h"

Field parseField(const std::string& fieldStr) {
    if (fieldStr == "day") return DAY;
    if (fieldStr == "lessonNum") return LESSON_NUM;
    if (fieldStr == "room") return ROOM;
    if (fieldStr == "subject") return SUBJNAME;
    if (fieldStr == "group") return GROUP;
    if (fieldStr == "teacherName") return TEACHERNAME;
    if (fieldStr == "teacherLastName") return TEACHERLASTNAME;
    if (fieldStr == "teacherPatr") return TEACHERPATR;
    return NONE_FIELD;
}

BinOp parseBinOp(const std::string& opStr) {
    if (opStr == "=") return EQ;
    if (opStr == "!=") return NEQ;
    if (opStr == "<") return LT;
    if (opStr == ">") return GT;
    if (opStr == "<=") return LT_EQ;
    if (opStr == ">=") return GT_EQ;
    if (opStr == "LIKE") return LIKE;
    return EQ; 
}

Value parseValue(const std::string& valueStr) {
    Value val;
    try {
        val = std::stoi(valueStr);
    }
    catch (const std::invalid_argument&) {
        try {
            val = std::stod(valueStr);
        }
        catch (const std::invalid_argument&) {
             val = valueStr;

        }
    }
    return val;
}

std::vector<std::pair<Date, Date>> parseDateRange(const std::string& dateStr) {
    std::vector<std::pair<Date, Date>> dateRanges;
    std::stringstream ss(dateStr);
    std::string token;

    while (std::getline(ss, token, ',')) {
        std::stringstream tokenStream(token);
        std::string startDate, endDate;

        if (std::getline(tokenStream, startDate, '-') && std::getline(tokenStream, endDate)) {
            size_t dotPosStart = startDate.find('.');
            size_t dotPosEnd = endDate.find('.');

            if (dotPosStart != std::string::npos && dotPosEnd != std::string::npos) {
                try {
                    Date start;
                    start.day = std::stoi(startDate.substr(0, dotPosStart));
                    start.month = std::stoi(startDate.substr(dotPosStart + 1));

                    Date end;
                    end.day = std::stoi(endDate.substr(0, dotPosEnd));
                    end.month = std::stoi(endDate.substr(dotPosEnd + 1));

                    dateRanges.push_back({start, end});
                } catch (const std::invalid_argument&) {
                    throw std::runtime_error("Invalid date format");
                }
            } else {
                throw std::runtime_error("Invalid date format");
            }
        } else {
            size_t dotPos = startDate.find('.');
            if (dotPos != std::string::npos) {
                try {
                    Date date;
                    date.day = std::stoi(startDate.substr(0, dotPos));
                    date.month = std::stoi(startDate.substr(dotPos + 1));

                    dateRanges.push_back({date, date});
                } catch (const std::invalid_argument&) {
                    throw std::runtime_error("Invalid date format");
                }
            } else {
                throw std::runtime_error("Invalid date format");
            }
        }
    }

    return dateRanges;
}

std::vector<std::pair<int, int>> parseLessonRange(const std::string& lessonStr) {
    std::vector<std::pair<int, int>> lessonRanges;
    std::stringstream ss(lessonStr);
    std::string token;

    while (std::getline(ss, token, ',')) {
        std::stringstream tokenStream(token);
        std::string startLesson, endLesson;

        if (std::getline(tokenStream, startLesson, '-') && std::getline(tokenStream, endLesson)) {
            try {
                int start = std::stoi(startLesson);
                int end = std::stoi(endLesson);
                lessonRanges.push_back({start, end});
            } catch (const std::invalid_argument&) {
                throw std::runtime_error("Invalid lesson format");
            }
        } else {
            try {
                int lesson = std::stoi(startLesson);
                lessonRanges.push_back({lesson, lesson});
            } catch (const std::invalid_argument&) {
                throw std::runtime_error("Invalid lesson format");
            }
        }
    }

    return lessonRanges;
}
