#include "parser.h"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>


std::string toUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}


std::vector<ParserToken> SQLParser::tokenize(const std::string& input) {
    std::vector<ParserToken> tokens;
    std::istringstream stream(input);
    std::string token;

    while (stream >> std::quoted(token)) {
        tokens.push_back(token);
    }

    return tokens;
}


void SQLParser::execute(const std::string& query) {
    auto tokens = tokenize(query);
    if (tokens.empty()) return;

    std::string command = tokens[0].upper;

    if (command == "INSERT") {
        handleInsert(tokens);
    }
    else if (command == "SELECT") {
        handleSelect(tokens);
    }
    else if (command == "UPDATE") {
        handleUpdate(tokens);
    }
    else if (command == "DELETE") {
        handleDelete(tokens);
    }
    else {
        std::cout << "Unknown command\n";
    }
}


void SQLParser::handleInsert(const std::vector<ParserToken>& tokens) {
    if (tokens.size() == 4 && tokens[1].original == "*" && tokens[2].upper == "FROM" && tokens[3].upper == "STUDENTS") {
        db.listAll();
        return;
    }

    if (tokens.size() >= 7 && tokens[1].original == "*" && tokens[2].upper == "FROM" && tokens[3].upper == "STUDENTS" && tokens[4].upper == "WHERE") {
        if (tokens[5].upper == "ID" && tokens[6].original == "=") {
            int id = std::stoi(tokens[7].original);
            auto student = db.getStudentById(id);
            if (student) student->print();
            else std::cout << "Student not found.\n";
            return;
        }

        if (tokens[5].upper == "GPA" && tokens[6].original == ">") {
            double threshold = std::stod(tokens[7].original);
            for (const auto& s : db.getAll()) {
                if (s.gpa > threshold) s.print();
            }
            return;
        }

        // Диапазон id: WHERE 210 - 215  или * - 215
        if (std::isdigit(tokens[5].original[0]) || tokens[5].original == "*") {
            int from = (tokens[5].original == "*") ? 0 : std::stoi(tokens[5].original);
            if (tokens[6].original == "-" && std::isdigit(tokens[7].original[0])) {
                int to = std::stoi(tokens[7].original);
                for (const auto& s : db.getAll()) {
                    if (s.id >= from && s.id <= to) s.print();
                }
                return;
            }
        }
    }

    std::cout << "Invalid SELECT syntax.\n";
}


void SQLParser::handleSelect(const std::vector<ParserToken>& tokens) {

    if (tokens.size() == 4 && tokens[3].upper == "STUDENTS") {
        db.listAll();
    }
    else if (tokens.size() >= 7 && tokens[4].upper == "WHERE" && tokens[5].upper == "ID") {
        int id = std::stoi(tokens[7].original);
        auto s = db.getStudentById(id);
        if (s) s->print();
        else std::cout << "Student not found.\n";
    }
    else {
        std::cout << "Invalid SELECT syntax.\n";
    }
}


void SQLParser::handleUpdate(const std::vector<ParserToken>& tokens) {
    if (tokens.size() < 10 || tokens[1].upper != "STUDENTS" || tokens[2].upper != "SET" || tokens[7].upper != "WHERE" || tokens[8].upper != "ID" || tokens[9].original != "=") {
        std::cout << "Invalid UPDATE syntax.\n";
        return;
    }

    std::string name = tokens[3].original;
    int group = std::stoi(tokens[4].original);
    double gpa = std::stod(tokens[5].original);
    std::string info = tokens[6].original;
    int id = std::stoi(tokens[10].original);

    auto student = db.getStudentById(id);
    if (student) {
        db.deleteStudent(id);
        db.addStudent(name, group, gpa, info);
        std::cout << "Student with ID " << id << " updated.\n";
    }
    else {
        std::cout << "Student with ID " << id << " not found.\n";
    }
}


void SQLParser::handleDelete(const std::vector<ParserToken>& tokens) {
    if (tokens.size() >= 7 && tokens[3].upper == "STUDENTS" && tokens[4].upper == "WHERE" && tokens[5].upper == "ID") {
        int id = std::stoi(tokens[7].original);
        if (db.deleteStudent(id)) std::cout << "Deleted.\n";
        else std::cout << "Student not found.\n";
    }
    else {
        std::cout << "Invalid DELETE syntax.\n";
    }
}
