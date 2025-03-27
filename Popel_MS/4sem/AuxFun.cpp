#include <iostream>
#include <sstream>
#include <regex>

#include "Schedule.h"

Field parseField(const std::string& fieldStr) {
    if (fieldStr == "time") return TIME;
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

std::pair<TimeHM, TimeHM> parseTimeRange(const std::string& timeStr) {
    std::pair<TimeHM, TimeHM> timeRange;
    std::stringstream ss(timeStr);
    std::string startTime, endTime;

    if (std::getline(ss, startTime, '-') && std::getline(ss, endTime)) {
        size_t colonPosStart = startTime.find(':');
        size_t colonPosEnd = endTime.find(':');

        if (colonPosStart != std::string::npos && colonPosEnd != std::string::npos) {
            timeRange.first.startHour = std::stoi(startTime.substr(0, colonPosStart));
            timeRange.first.startMinute = std::stoi(startTime.substr(colonPosStart + 1));
            timeRange.second.endHour = std::stoi(endTime.substr(0, colonPosEnd));
            timeRange.second.endMinute = std::stoi(endTime.substr(colonPosEnd + 1));
        } else {
            throw Exception(11, "Time problems");
        }
    } else {
        throw Exception(11, "Time problems");
    }

    return timeRange;
}
