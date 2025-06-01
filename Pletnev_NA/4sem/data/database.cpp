#include "database.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <limits>

namespace Validation {
    bool isValidNodeNamePart(const std::string& name_part) {
        if (name_part.empty()) return false;
        for (char c : name_part) {
            if (!std::isalnum(c) && c != '_' && c != '-') {
                if (c == '.' || c == ' ') continue;
                return false;
            }
        }
        return true;
    }

    bool isValidPath(const std::string& path, const Database* db) {
        if (path.empty() && path != "") return false;
        std::vector<std::string> parts = db->splitPath(path);
        if (parts.empty() && !path.empty()) return false;
        for (const std::string& part : parts) {
            if (!isValidNodeNamePart(part)) return false;
        }
        return true;
    }

    bool isValidEmployeeName(const std::string& name) {
        if (name.empty()) return false;
        for (char c : name) {
            if (c == '/' || c == '\'' || c == ':') return false;
        }
        return true;
    }

    bool isValidWorkloadType(const std::string& type) {
        if (type.empty()) return false;
        for (char c : type) {
            if (!std::isalnum(c) && c != '_' && c != '-') return false;
        }
        return true;
    }
}


std::string Database::toLower(const std::string& str) const {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}

std::vector<std::string> Database::tokenize(const std::string& cmd) const {
    std::vector<std::string> tokens;
    std::string current;
    bool inQuote = false;
    for (char c : cmd) {
        if (c == '\'' && !inQuote) {
            inQuote = true;
        } else if (c == '\'' && inQuote) {
            inQuote = false;
            tokens.push_back(current);
            current.clear();
        } else if (c == ' ' && !inQuote) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        } else {
            current += c;
        }
    }
    if (!current.empty()) {
        tokens.push_back(current);
    }
    return tokens;
}

Database::Database() {
    root = new Node("");
}

Database::~Database() {
    deleteTree(root);
}

void Database::deleteTree(Node* node) {
    if (!node) return;
    for (auto& pair : node->children) {
        deleteTree(pair.second);
    }
    delete node;
}

std::vector<std::string> Database::splitPath(const std::string& path) const {
    std::vector<std::string> parts;
    if (path.empty()) return parts;
    std::stringstream ss(path);
    std::string part;
    while (std::getline(ss, part, '/')) {
        if (!part.empty()) {
            parts.push_back(part);
        }
    }
    return parts;
}

Node* Database::getNode(const std::string& path) {
    std::vector<std::string> parts = splitPath(path);
    if (path.empty() && parts.empty()) return root;
    if (!path.empty() && parts.empty()) return nullptr;
    Node* current = root;
    for (const auto& part : parts) {
        auto it = current->children.find(part);
        if (it == current->children.end()) {
            return nullptr;
        }
        current = it->second;
    }
    return current;
}

Node* Database::createNodeByPath(const std::string& path) {
    std::vector<std::string> parts = splitPath(path);
    if (parts.empty() && !path.empty()) {
        std::cout << "Error: Invalid node path format '" << path << "'. Path cannot consist only of separators." << std::endl;
        return nullptr;
    }
    if (path.empty()){
         std::cout << "Error: Cannot create node with empty path." << std::endl;
        return nullptr;
    }
    Node* current = root;
    for (const auto& part : parts) {
        if (!Validation::isValidNodeNamePart(part)) {
            std::cout << "Error: Invalid character or empty segment in node path part: '" << part << "' from path '" << path << "'." << std::endl;
            return nullptr;
        }
        auto it = current->children.find(part);
        if (it == current->children.end()) {
            Node* newNode = new Node(part);
            current->children[part] = newNode;
            current = newNode;
        } else {
            current = it->second;
        }
    }
    return current;
}

std::vector<Employee> Database::getAllEmployeesRecursive(Node* node) const {
    std::vector<Employee> result;
    if (!node) return result;
    result = node->employees;
    for (auto& pair : node->children) {
        std::vector<Employee> subEmployees = getAllEmployeesRecursive(pair.second);
        result.insert(result.end(), subEmployees.begin(), subEmployees.end());
    }
    return result;
}

void Database::addNode(const std::string& path) {
    if (!Validation::isValidPath(path, this)) {
        return;
    }
    Node* created_node = createNodeByPath(path);
    if (created_node) {
        std::cout << "Node added/exists at path: " << path << std::endl;
    }
}

void Database::addEmployee(const std::string& path, const std::string& name, const std::vector<std::pair<std::string, int>>& workload) {
    if (!Validation::isValidPath(path, this)) {
        std::cout << "Error: Invalid path format for adding employee: '" << path << "'" << std::endl;
        return;
    }
    if (!Validation::isValidEmployeeName(name)) {
        std::cout << "Error: Invalid employee name: '" << name << "'. Name cannot be empty or contain '/', ':', or '\\''." << std::endl;
        return;
    }
    if (workload.empty()){
        std::cout << "Warning: Adding employee '" << name << "' with no workload specified." << std::endl;
    }
    for(const auto& wl_item : workload){
        if(!Validation::isValidWorkloadType(wl_item.first)){
            std::cout << "Error: Invalid workload type '" << wl_item.first << "' for employee '" << name << "'." << std::endl;
            return;
        }
        if(wl_item.second < 0){
            std::cout << "Error: Workload hours for type '" << wl_item.first << "' cannot be negative for employee '" << name << "'." << std::endl;
            return;
        }
    }
    Node* node = getNode(path);
    if (node == nullptr) {
        std::cout << "Error: Node not found at path: '" << path << "' to add employee. Please create the node first." << std::endl;
        return;
    }
    for (const auto& emp : node->employees) {
        if (emp.name == name) {
            std::cout << "Error: Employee '" << name << "' already exists in node '" << path << "'. Use a different name or update mechanism." << std::endl;
            return;
        }
    }
    node->employees.push_back({name, workload});
    std::cout << "Employee '" << name << "' added to node '" << path << "'" << std::endl;
}

void Database::query(const std::vector<std::string>& columns, const std::string& path, bool row_sum) {
    if (!Validation::isValidPath(path, this) && !path.empty()) {
        std::cout << "Error: Invalid path format for query: '" << path << "'" << std::endl;
        return;
    }
    if (columns.empty()) {
        std::cout << "Error: No columns specified for query." << std::endl;
        return;
    }
    for(const auto& col_name : columns) {
        if (toLower(col_name) != "name" && toLower(col_name) != "row_sum" && !Validation::isValidWorkloadType(col_name)){
        }
    }
    Node* node = getNode(path);
    if (node == nullptr && !path.empty()) {
        std::cout << "Error: Node not found for query: '" << path << "'" << std::endl;
        return;
    }
    if (node == nullptr && path.empty()) node = root;
    auto allEmps = getAllEmployeesRecursive(node);
    if (allEmps.empty()) {
        std::cout << "No employees found under path: '" << path << "'" << std::endl;
        return;
    }
    std::vector<std::string> printColumns = columns;
    for (size_t i = 0; i < printColumns.size(); ++i) {
        std::cout << std::left << std::setw(15) << printColumns[i];
    }
    if (row_sum) {
        std::cout << std::left << std::setw(15) << "row_sum";
    }
    std::cout << std::endl;
    for (size_t i = 0; i < printColumns.size(); ++i) std::cout << std::string(15, '-');
    if (row_sum) std::cout << std::string(15, '-');
    std::cout << std::endl;
    for (const auto& emp : allEmps) {
        int currentRowSum = 0;
        for (const auto& col_header : printColumns) {
            std::string lower_col_header = toLower(col_header);
            if (lower_col_header == "name") {
                std::cout << std::left << std::setw(15) << emp.name;
            } else {
                auto it = std::find_if(emp.workload.begin(), emp.workload.end(),
                                       [this, &lower_col_header](const auto& wl_pair){ return this->toLower(wl_pair.first) == lower_col_header; });
                if (it != emp.workload.end()) {
                    std::cout << std::left << std::setw(15) << it->second;
                    if (row_sum) currentRowSum += it->second;
                } else {
                    std::cout << std::left << std::setw(15) << 0;
                }
            }
        }
        if (row_sum) {
            std::cout << std::left << std::setw(15) << currentRowSum;
        }
        std::cout << std::endl;
    }
}

void Database::save(const std::string& filename) const {
    if (filename.empty()){
        std::cout << "Error: Filename for save cannot be empty." << std::endl;
        return;
    }
    if (filename.find('/') != std::string::npos || filename.find('\\') != std::string::npos) {
        std::cout << "Error: Filename '" << filename << "' should not contain path separators. Saving in current directory." << std::endl;
    }
    std::ofstream out(filename);
    if (!out) {
        std::cout << "Error opening file for saving: '" << filename << "'" << std::endl;
        return;
    }
    std::function<void(const Node*, const std::string&)> saveNodeRecursiveFunc =
        [&](const Node* currentNode, const std::string& currentPathStr) {
        if (!currentNode) return;
        if (currentNode != root && (!currentPathStr.empty())) {
             bool hasContent = !currentNode->employees.empty() || !currentNode->children.empty();
             if(hasContent || !currentNode->name.empty()){
                out << "node " << currentPathStr << std::endl;
             }
        }
        for (const auto& emp : currentNode->employees) {
            out << "employee " << currentPathStr << " '" << emp.name << "'";
            for (const auto& wl : emp.workload) {
                out << " " << wl.first << ":" << wl.second;
            }
            out << std::endl;
        }
        for (const auto& pair : currentNode->children) {
            std::string childPathStr = currentPathStr.empty() ? pair.first : currentPathStr + "/" + pair.first;
            saveNodeRecursiveFunc(pair.second, childPathStr);
        }
    };
    saveNodeRecursiveFunc(root, "");
    out.close();
    std::cout << "Database saved to '" << filename << "'" << std::endl;
}

void Database::load(const std::string& filename) {
    if (filename.empty()){
        std::cout << "Error: Filename for load cannot be empty." << std::endl;
        return;
    }
    std::ifstream in(filename);
    if (!in) {
        std::cout << "Error opening file for loading: '" << filename << "'" << std::endl;
        return;
    }
    deleteTree(root);
    root = new Node("");
    std::cout << "Loading database from '" << filename << "'..." << std::endl;
    std::string line;
    int lineNum = 0;
    while (std::getline(in, line)) {
        lineNum++;
        auto tokens = this->tokenize(line);
        if (tokens.empty() || (!tokens.empty() && tokens[0].rfind('#', 0) == 0)) continue;
        std::string command_type = toLower(tokens[0]);
        if (command_type == "node") {
            if (tokens.size() == 2) {
                if (!Validation::isValidPath(tokens[1], this)) {
                     std::cout << "Warning (load line " << lineNum << "): Invalid node path '" << tokens[1] << "'. Skipping." << std::endl; continue;
                }
                this->createNodeByPath(tokens[1]);
            } else {
                std::cout << "Warning (load line " << lineNum << "): Malformed 'node' command. Expected 'node <path>'. Skipping." << std::endl;
            }
        } else if (command_type == "employee") {
            if (tokens.size() >= 3) {
                std::string path_str = tokens[1];
                std::string name_str = tokens[2];
                if (!Validation::isValidPath(path_str, this)) {
                    std::cout << "Warning (load line " << lineNum << "): Invalid path '" << path_str << "' for employee. Skipping." << std::endl; continue;
                }
                if (!Validation::isValidEmployeeName(name_str)) {
                    std::cout << "Warning (load line " << lineNum << "): Invalid employee name '" << name_str << "'. Skipping." << std::endl; continue;
                }
                Node* nodeForEmployee = getNode(path_str);
                if (!nodeForEmployee) {
                    nodeForEmployee = createNodeByPath(path_str);
                    if (!nodeForEmployee) { std::cout << "Warning (load line " << lineNum << "): Failed to create/get node for employee at path '" << path_str << "'. Skipping." << std::endl; continue; }
                    std::cout << "Info (load line " << lineNum << "): Created missing node path for employee: '" << path_str << "'" << std::endl;
                }
                std::vector<std::pair<std::string, int>> workload_vec;
                for (size_t i = 3; i < tokens.size(); ++i) {
                    size_t colonPos = tokens[i].find(':');
                    if (colonPos != std::string::npos && colonPos > 0 && colonPos < tokens[i].length() - 1) {
                        std::string type_str = tokens[i].substr(0, colonPos);
                        std::string hours_str = tokens[i].substr(colonPos + 1);
                        if (!Validation::isValidWorkloadType(type_str)) {
                             std::cout << "Warning (load line " << lineNum << "): Invalid workload type '" << type_str << "'. Skipping this workload item." << std::endl; continue;
                        }
                        try {
                            int hours_val = std::stoi(hours_str);
                            if (hours_val < 0) {
                                std::cout << "Warning (load line " << lineNum << "): Negative hours (" << hours_val << ") for workload type '" << type_str << "'. Skipping this workload item." << std::endl; continue;
                            }
                            workload_vec.push_back({type_str, hours_val});
                        } catch (const std::invalid_argument& ) {
                            std::cout << "Warning (load line " << lineNum << "): Invalid number format for hours in '" << tokens[i] << "'. Skipping this workload item." << std::endl;
                        } catch (const std::out_of_range& ) {
                            std::cout << "Warning (load line " << lineNum << "): Hours value out of range in '" << tokens[i] << "'. Skipping this workload item." << std::endl;
                        }
                    } else {
                        std::cout << "Warning (load line " << lineNum << "): Invalid workload format: '" << tokens[i] << "'. Expected type:hours. Skipping this workload item." << std::endl;
                    }
                }
                 if (nodeForEmployee) {
                     bool exists = false;
                     for(const auto& e : nodeForEmployee->employees) if(e.name == name_str) exists = true;
                     if(!exists) {
                        nodeForEmployee->employees.push_back({name_str, workload_vec});
                     } else {
                        std::cout << "Info (load line " << lineNum << "): Employee '" << name_str << "' already exists in '" << path_str << "'. Skipping." << std::endl;
                     }
                 }
            } else {
                 std::cout << "Warning (load line " << lineNum << "): Malformed 'employee' command. Expected 'employee <path> '<name>' [workload...]'. Skipping." << std::endl;
            }
        } else {
            std::cout << "Warning (load line " << lineNum << "): Unknown or malformed line in file: '" << line << "'. Skipping." << std::endl;
        }
    }
    in.close();
    std::cout << "Database loaded from '" << filename << "'" << std::endl;
}

void Database::processCommand(const std::string& command_line) {
    if (command_line.empty() || command_line.find_first_not_of(" \t\n\r") == std::string::npos) {
        return;
    }
    auto tokens = tokenize(command_line);
    if (tokens.empty()) return;
    std::string cmd_keyword = toLower(tokens[0]);
    if (cmd_keyword == "add") {
        if (tokens.size() < 2) {
            std::cout << "Error: 'add' command requires a subcommand (node or employee)." << std::endl;
            return;
        }
        std::string add_type = toLower(tokens[1]);
        if (add_type == "node") {
            if (tokens.size() == 3) {
                addNode(tokens[2]);
            } else {
                std::cout << "Usage: add node <path>" << std::endl;
            }
        } else if (add_type == "employee") {
            if (tokens.size() >= 4) {
                std::string path = tokens[2];
                std::string name = tokens[3];
                std::vector<std::pair<std::string, int>> workload;
                if (tokens.size() >= 5) {
                    for (size_t i = 4; i < tokens.size(); ++i) {
                        size_t colonPos = tokens[i].find(':');
                        if (colonPos != std::string::npos && colonPos > 0 && colonPos < tokens[i].length() - 1) {
                            std::string type = tokens[i].substr(0, colonPos);
                            std::string hours_str = tokens[i].substr(colonPos + 1);
                            try {
                                int hours = std::stoi(hours_str);
                                workload.push_back({type, hours});
                            } catch (const std::invalid_argument& ) {
                                std::cout << "Error: Invalid number format for hours in workload item '" << tokens[i] << "'." << std::endl;
                                return;
                            } catch (const std::out_of_range& ) {
                                std::cout << "Error: Hours value out of range in workload item '" << tokens[i] << "'." << std::endl;
                                return;
                            }
                        } else {
                            std::cout << "Error: Invalid workload format for item '" << tokens[i] << "'. Expected type:hours" << std::endl;
                            return;
                        }
                    }
                }
                addEmployee(path, name, workload);
            } else {
                std::cout << "Usage: add employee <path> '<name>' [workload1:hours1 ...]" << std::endl;
            }
        } else {
            std::cout << "Error: Unknown 'add' subcommand '" << tokens[1] << "'. Use 'node' or 'employee'." << std::endl;
        }
    } else if (cmd_keyword == "query") {
        if (tokens.size() < 5 || toLower(tokens[1]) != "columns") {
            std::cout << "Usage: query columns <col1> [col2...] where <path> [row_sum]" << std::endl;
            return;
        }
        std::vector<std::string> cols;
        size_t current_token_idx = 2;
        while(current_token_idx < tokens.size() && toLower(tokens[current_token_idx]) != "where") {
            cols.push_back(tokens[current_token_idx]);
            current_token_idx++;
        }
        if (current_token_idx >= tokens.size() || toLower(tokens[current_token_idx]) != "where") {
            std::cout << "Error: 'where' keyword missing or misplaced in query." << std::endl;
            return;
        }
        current_token_idx++;
        if (current_token_idx >= tokens.size()) {
            std::cout << "Error: Path missing after 'where' in query." << std::endl;
            return;
        }
        std::string path = tokens[current_token_idx];
        current_token_idx++;
        bool row_sum_flag = false;
        if (current_token_idx < tokens.size() && toLower(tokens[current_token_idx]) == "row_sum") {
            row_sum_flag = true;
            current_token_idx++;
        }
        if (current_token_idx < tokens.size()){
            std::cout << "Error: Unexpected arguments after query specification: '" << tokens[current_token_idx] << "...'" << std::endl;
            return;
        }
        if (cols.empty()){
             std::cout << "Error: No columns specified for query." << std::endl;
            return;
        }
        query(cols, path, row_sum_flag);
    } else if (cmd_keyword == "save") {
        if (tokens.size() == 2) {
             if (tokens.size() > 2) { std::cout << "Error: Too many arguments for 'save' command." << std::endl; return; }
            save(tokens[1]);
        } else if (tokens.size() == 1) {
            std::cout << "Error: Missing filename for 'save' command." << std::endl;
             std::cout << "Usage: save <filename>" << std::endl;
        }
        else {
            std::cout << "Error: Too many arguments for 'save' command." << std::endl;
            std::cout << "Usage: save <filename>" << std::endl;
        }
    } else if (cmd_keyword == "load") {
        if (tokens.size() == 2) {
            if (tokens.size() > 2) { std::cout << "Error: Too many arguments for 'load' command." << std::endl; return; }
            load(tokens[1]);
        } else if (tokens.size() == 1) {
            std::cout << "Error: Missing filename for 'load' command." << std::endl;
            std::cout << "Usage: load <filename>" << std::endl;
        }
         else {
            std::cout << "Error: Too many arguments for 'load' command." << std::endl;
            std::cout << "Usage: load <filename>" << std::endl;
        }
    } else {
        std::cout << "Unknown command: '" << tokens[0] << "'. Type 'help' for commands." << std::endl;
    }
}