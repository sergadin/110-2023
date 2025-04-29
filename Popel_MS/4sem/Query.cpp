#include "Schedule.h"
#include <iostream>

std::list<Query::parser_fn> Query::parsers;

void Query::register_parser(parser_fn p) {
if (p == nullptr) {
        throw Exception(6,"Функция парсера не может быть нулевой");
    }
    parsers.push_back(p);
}

Query* Query::do_parse(const std::string &query) {
    for (auto parser : parsers) {
        try {
            Query* result = parser(query);
            std::cout << "Указатель на объект: " << reinterpret_cast<void*>(result) << std::endl;
            if (result != nullptr) {
                return result;
            }
        } catch (Exception &err) {
            return nullptr;
        }
    }
    return nullptr;
}
void Query::clear_parsers(){
  parsers.clear();
}
