#include "Schedule.h"
#include <iostream>
#include <sstream>
#include <regex>

void SelectingQuery::parse() {
    std::stringstream ss(getQueryString());
    std::string token;

    ss >> token;
    if (token == "SELECT") {
        setCommand(SELECT);
    } else if (token == "RESELECT") {
        setCommand(RESELECT);
    } else {
        throw Exception(5,"Expected SELECT or RESELECT");
    }

    while (ss >> token) {
        if (token == "end") {
            break; 
        } else {
            if (!parseTriple(token)) {
                throw Exception(13,"Incorrect syntax in SELECT/RESELECT query");
            }
        }
    }
}

bool SelectingQuery::parseTriple(const std::string& triple) {
    size_t opPos = triple.find_first_of("=><!~");
    if (opPos == std::string::npos) {
        return false;
    }

    std::string fieldStr = triple.substr(0, opPos);
    Field field = parseField(fieldStr);
    if (field == NONE_FIELD) {
        return false;
    }

    std::string opStr = triple.substr(opPos, 1);
    if (triple[opPos] == '~') {
        opStr = "LIKE";
    }
    BinOp operation = parseBinOp(opStr);

    std::string valueStr = triple.substr(opPos + opStr.length());
    Value value = parseValue(valueStr);

    condition_.push_back(Cond(field, operation, value));
    return true;
}
