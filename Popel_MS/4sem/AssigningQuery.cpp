#include "Schedule.h"
#include <iostream>
#include <sstream>
#include <regex>

void AssigningQuery::parse() {
    std::stringstream ss(getQueryString());
    std::string token;
    ss >> token;
    printf("HelloWorld from Assign!\n");
    if (token == "INSERT") {
        setCommand(INSERT);
    }else {
        throw Exception(6,"Expected INSERT or DELETE");
    }

    while (ss >> token) {
        if (token == "end") {
            break; 
        } else {
            if (!parseAssigningTriple(token)) {;
                throw Exception(15,"Incorrect syntax in INSERT/DELETE query");
            }
        }
    }
}

bool AssigningQuery::parseAssigningTriple(const std::string& triple) {
    size_t eqPos = triple.find('=');
    if (eqPos == std::string::npos) {
        return false;
    }

    std::string fieldStr = triple.substr(0, eqPos);
    Field field = parseField(fieldStr);
    if (field == NONE_FIELD) {
        return false;
    }  
    std::string valueStr = triple.substr(eqPos + 1);
    Value value = parseValue(valueStr);
    values_.push_back(std::make_pair(field, value));
    return true;
}
