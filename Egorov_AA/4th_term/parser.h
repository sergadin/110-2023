#ifndef PARSER_H
#define PARSER_H

#include "database.h"
#include <string>

std::string toUpper(const std::string& str);

struct ParserToken{
    std::string original;
    std::string upper;

    ParserToken(const std::string& str) : original(str), upper(toUpper(str)) {}
};

class SQLParser {
public:
    SQLParser(StudentDB& db) : db(db) {}
    void execute(const std::string& query);

private:
    StudentDB& db;
    std::vector<ParserToken> tokenize(const std::string& input);
    void handleInsert(const std::vector<ParserToken>& tokens);
    void handleSelect(const std::vector<ParserToken>& tokens);
    void handleUpdate(const std::vector<ParserToken>& tokens);
    void handleDelete(const std::vector<ParserToken>& tokens);
};

#endif  // PARSER_H