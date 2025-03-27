#include "Schedule.h"
#include <iostream>
#include <sstream>
#include <regex>

void UpdateQuery::parse() {
    std::stringstream ss(SelectingQuery::getQueryString());
    std::string token;
    ComType parsingState = SELECT; 

    ss >> token;
    if (token == "UPDATE") {
        SelectingQuery::setCommand(UPDATE);
    } else {
        throw Exception(10,"Expected UPDATE");
    }

    while (ss >> token) {
        if (token == "WHERE") {
            parsingState = ASSIGN;
        } else if (token == "end") {
            break; // End of query
        } else {
            if (parsingState == SELECT) { 
                if (!SelectingQuery::parseTriple(token)) { 
                    throw Exception(13,"Incorrect syntax in UPDATE");
                }
            } else if (parsingState == ASSIGN) { 
                if (!AssigningQuery::parseAssigningTriple(token)) { 
                    throw Exception(13,"Incorrect syntax in UPDATE");
                }
            }
        }
    }
}
