#include "Schedule.h"
#include <iostream>

std::list<Query::parser_fn> Query::parsers;

void Query::register_parser(parser_fn p) {
    parsers.push_back(p);
}

Query* Query::do_parse(const std::string &query) {
    for (auto parser : parsers) {
        try {
            Query* result = parser(query);
            if (result != nullptr) {
                return result;
            }
        } catch (Exception &err) {
            return nullptr;
        }
    }
    return nullptr;
}
