#include "Schedule.h"
#include <iostream>
#include <sstream>

void InsertQuery::parse() {
    setCommand(INSERT);
    AssigningQuery::parse();
}

void PrintQuery::parse() {
    std::stringstream ss(getQueryString());
    std::string token;
    ss >> token;
    std::cout << token << std::endl;
    if (token == "PRINT") {
        setCommand(PRINT);
    } else {
        throw Exception(7, "Expected PRINT");
    }

    while (ss >> token) {
        std::cout << token << std::endl;
        if (token == "sort") {
            ss >> token;
            Field sortField = parseField(token);
            if (sortField == NONE_FIELD) {
                throw Exception(16, "Invalid sort field in PRINT query");
            }

            ss >> token;
            Order sortOrder = (token == "ASC") ? ASC : DESC;
            sort_fields_.push_back(std::make_pair(sortField, sortOrder));
        } else if (token == "end") {
            break;
        } else {
            Field field = parseField(token);
            if (field == NONE_FIELD) {
                throw Exception(16, "Invalid field in PRINT query");
            }
            fields_.push_back(field);
        }
    }
}


void DeleteQuery::parse() {
    std::stringstream ss(getQueryString());
    std::string token;
    ss >> token;
    if (token == "DELETE") {
        setCommand(DELETE);
    } else {
        throw Exception(8,"Expected DELETE");
    }
    while (ss >> token) {
        if (token == "end") {
            break;
        } else {
            if (!SelectingQuery::parseTriple(token)) {
                throw Exception(17,"Incorrect syntax in DELETE query");
            }
        }
    }
}
