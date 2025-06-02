#include "database.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <limits>

// Пространство имен для функций валидации
namespace Validation {
    // Проверка валидности части имени узла
    bool isValidNodeNamePart(const std::string& name_part) {
        if (name_part.empty()) return false;
        for (char c : name_part) {
            if (!std::isalnum(c) && c != '_' && c != '-') {
                if (c == '.' || c == ' ') continue; // Допустимы для гибкости
                return false;
            }
        }
        return true;
    }

    // Проверка валидности всего пути
    bool isValidPath(const std::string& path, const Database* db) {
        if (path.empty() && path != "") return false; // Пустой путь "" может быть валиден для корня
        std::vector<std::string> parts = db->splitPath(path);
        if (parts.empty() && !path.empty()) return false; // Случай "///"
        for (const std::string& part : parts) {
            if (!isValidNodeNamePart(part)) return false;
        }
        return true;
    }

    // Проверка валидности имени сотрудника
    bool isValidEmployeeName(const std::string& name) {
        if (name.empty()) return false;
        for (char c : name) {
            if (c == '/' || c == '\'' || c == ':') return false; // Запрещенные символы
        }
        return true;
    }

    // Проверка валидности типа нагрузки
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
    root = new Node(""); // Инициализация корневого узла
}

Database::~Database() {
    deleteTree(root); // Очистка памяти при уничтожении объекта
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
    if (path.empty() && parts.empty()) return root; // Пустой путь -> корень
    if (!path.empty() && parts.empty()) return nullptr; // Невалидный путь типа "///"
    Node* current = root;
    for (const auto& part : parts) {
        auto it = current->children.find(part);
        if (it == current->children.end()) {
            return nullptr; // Узел не найден
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
    result = node->employees; // Сотрудники текущего узла
    for (auto& pair : node->children) { // Рекурсивно для дочерних
        std::vector<Employee> subEmployees = getAllEmployeesRecursive(pair.second);
        result.insert(result.end(), subEmployees.begin(), subEmployees.end());
    }
    return result;
}

void Database::addNode(const std::string& path) {
    if (!Validation::isValidPath(path, this)) {
        return; // Сообщение об ошибке выводится из isValidPath или createNodeByPath
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
    // Опциональная валидация имен столбцов
    for(const auto& col_name : columns) {
        if (toLower(col_name) != "name" && toLower(col_name) != "row_sum" && !Validation::isValidWorkloadType(col_name)){
            // Можно добавить вывод ошибки, если имя столбца невалидно
        }
    }
    Node* node = getNode(path);
    if (node == nullptr && !path.empty()) {
        std::cout << "Error: Node not found for query: '" << path << "'" << std::endl;
        return;
    }
    if (node == nullptr && path.empty()) node = root; // Запрос к корню
    auto allEmps = getAllEmployeesRecursive(node);
    if (allEmps.empty()) {
        std::cout << "No employees found under path: '" << path << "'" << std::endl;
        return;
    }
    std::vector<std::string> printColumns = columns;
    // Печать заголовков
    for (size_t i = 0; i < printColumns.size(); ++i) {
        std::cout << std::left << std::setw(15) << printColumns[i];
    }
    if (row_sum) {
        std::cout << std::left << std::setw(15) << "row_sum";
    }
    std::cout << std::endl;
    // Печать разделителя
    for (size_t i = 0; i < printColumns.size(); ++i) std::cout << std::string(15, '-');
    if (row_sum) std::cout << std::string(15, '-');
    std::cout << std::endl;
    // Печать данных
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
        // Можно либо запретить, либо извлечь только имя файла. Пока просто предупреждение.
    }
    std::ofstream out(filename);
    if (!out) {
        std::cout << "Error opening file for saving: '" << filename << "'" << std::endl;
        return;
    }
    // Рекурсивная лямбда для сохранения
    std::function<void(const Node*, const std::string&)> saveNodeRecursiveFunc =
        [&](const Node* currentNode, const std::string& currentPathStr) {
        if (!currentNode) return;
        if (currentNode != root && (!currentPathStr.empty())) {
             bool hasContent = !currentNode->employees.empty() || !currentNode->children.empty();
             if(hasContent || !currentNode->name.empty()){ // Сохраняем узел, если он не пуст или имеет имя
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
    saveNodeRecursiveFunc(root, ""); // Начинаем с корня
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
    deleteTree(root); // Очищаем текущую базу
    root = new Node("");
    std::cout << "Loading database from '" << filename << "'..." << std::endl;
    std::string line;
    int lineNum = 0;
    while (std::getline(in, line)) {
        lineNum++;
        auto tokens = this->tokenize(line);
        if (tokens.empty() || (!tokens.empty() && tokens[0].rfind('#', 0) == 0)) continue; // Пропуск пустых и комментариев
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
            if (tokens.size() >= 3) { // employee <path> '<name>' [workload...]
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

// --- Новые методы ---
void Database::removeNode(const std::string& path, bool recursive_delete) {
    if (!Validation::isValidPath(path, this) || path.empty()) {
        std::cout << "Error (removeNode): Invalid or empty path '" << path << "'." << std::endl;
        return;
    }
    std::vector<std::string> parts = splitPath(path);
    if (parts.empty()) {
        std::cout << "Error (removeNode): Cannot remove the root node." << std::endl;
        return;
    }
    Node* current_search = root;
    Node* parent_of_target = nullptr; // Инициализируем nullptr
    // Находим родителя целевого узла
    for (size_t i = 0; i < parts.size() - 1; ++i) { // Идем до предпоследнего элемента
        auto it = current_search->children.find(parts[i]);
        if (it == current_search->children.end()) {
            std::cout << "Error (removeNode): Path segment '" << parts[i] << "' not found in path '" << path << "'." << std::endl;
            return;
        }
        current_search = it->second;
    }
    parent_of_target = current_search; // Теперь current_search это родитель
    // Находим сам целевой узел
    auto target_it = parent_of_target->children.find(parts.back());
    if (target_it == parent_of_target->children.end()) {
        std::cout << "Error (removeNode): Target node '" << parts.back() << "' not found in parent '" << (parts.size() > 1 ? parts[parts.size()-2] : "root") << "' for path '" << path << "'." << std::endl;
        return;
    }
    Node* target_node = target_it->second;

    if (!recursive_delete && (!target_node->children.empty() || !target_node->employees.empty())) {
        std::cout << "Error (removeNode): Node '" << path << "' is not empty. Use recursive delete or remove contents first." << std::endl;
        return;
    }
    parent_of_target->children.erase(parts.back()); // Удаляем из карты родителя
    deleteTree(target_node); // Удаляем само поддерево (или узел, если пуст)
    std::cout << "Node '" << path << "' removed successfully." << std::endl;
}

void Database::removeEmployee(const std::string& node_path, const std::string& employee_name) {
    if (!Validation::isValidPath(node_path, this) || node_path.empty()) {
        std::cout << "Error (removeEmployee): Invalid or empty node path '" << node_path << "'." << std::endl;
        return;
    }
    if (!Validation::isValidEmployeeName(employee_name)) {
        std::cout << "Error (removeEmployee): Invalid employee name '" << employee_name << "'." << std::endl;
        return;
    }
    Node* node = getNode(node_path);
    if (!node) {
        std::cout << "Error (removeEmployee): Node not found at path '" << node_path << "'." << std::endl;
        return;
    }
    auto& emps = node->employees;
    auto it = std::remove_if(emps.begin(), emps.end(),
                             [&](const Employee& emp) { return emp.name == employee_name; });
    if (it != emps.end()) {
        emps.erase(it, emps.end());
        std::cout << "Employee '" << employee_name << "' removed from node '" << node_path << "'." << std::endl;
    } else {
        std::cout << "Error (removeEmployee): Employee '" << employee_name << "' not found in node '" << node_path << "'." << std::endl;
    }
}

void Database::editEmployeeWorkload(const std::string& node_path, 
                                    const std::string& employee_name,
                                    const std::vector<std::pair<std::string, int>>& new_workload) {
    if (!Validation::isValidPath(node_path, this) || node_path.empty()) {
        std::cout << "Error (editEmployeeWorkload): Invalid or empty node path '" << node_path << "'." << std::endl;
        return;
    }
    if (!Validation::isValidEmployeeName(employee_name)) {
        std::cout << "Error (editEmployeeWorkload): Invalid employee name '" << employee_name << "'." << std::endl;
        return;
    }
    if (new_workload.empty()){
        std::cout << "Warning (editEmployeeWorkload): New workload for employee '" << employee_name << "' is empty. Old workload will be cleared." << std::endl;
    }
    for(const auto& wl_item : new_workload){
        if(!Validation::isValidWorkloadType(wl_item.first)){
            std::cout << "Error (editEmployeeWorkload): Invalid new workload type '" << wl_item.first << "'." << std::endl;
            return;
        }
        if(wl_item.second < 0){
            std::cout << "Error (editEmployeeWorkload): New workload hours for type '" << wl_item.first << "' cannot be negative." << std::endl;
            return;
        }
    }
    Node* node = getNode(node_path);
    if (!node) {
        std::cout << "Error (editEmployeeWorkload): Node not found at path '" << node_path << "'." << std::endl;
        return;
    }
    for (auto& emp : node->employees) {
        if (emp.name == employee_name) {
            emp.workload = new_workload; // Замена старой нагрузки
            std::cout << "Workload for employee '" << employee_name << "' in node '" << node_path << "' updated." << std::endl;
            return;
        }
    }
    std::cout << "Error (editEmployeeWorkload): Employee '" << employee_name << "' not found in node '" << node_path << "'." << std::endl;
}

// Главный обработчик команд
void Database::processCommand(const std::string& command_line) {
    if (command_line.empty() || command_line.find_first_not_of(" \t\n\r") == std::string::npos) {
        return;
    }
    auto tokens = tokenize(command_line);
    if (tokens.empty()) return;
    std::string cmd_keyword = toLower(tokens[0]);

    if (cmd_keyword == "add") {
        if (tokens.size() < 2) {
            std::cout << "Error: 'add' command requires a subcommand (node or employee)." << std::endl; return;
        }
        std::string add_type = toLower(tokens[1]);
        if (add_type == "node") {
            if (tokens.size() == 3) { addNode(tokens[2]); } 
            else { std::cout << "Usage: add node <path>" << std::endl; }
        } else if (add_type == "employee") {
            if (tokens.size() >= 4) {
                std::string path = tokens[2]; std::string name = tokens[3];
                std::vector<std::pair<std::string, int>> workload;
                if (tokens.size() >= 5) {
                    for (size_t i = 4; i < tokens.size(); ++i) {
                        size_t colonPos = tokens[i].find(':');
                        if (colonPos != std::string::npos && colonPos > 0 && colonPos < tokens[i].length() - 1) {
                            std::string type = tokens[i].substr(0, colonPos);
                            std::string hours_str = tokens[i].substr(colonPos + 1);
                            try { workload.push_back({type, std::stoi(hours_str)}); } 
                            catch (const std::exception& e) { std::cout << "Error: Invalid hours in '" << tokens[i] << "': " << e.what() << std::endl; return; }
                        } else { std::cout << "Error: Invalid workload format '" << tokens[i] << "'. Expected type:hours" << std::endl; return; }
                    }
                }
                addEmployee(path, name, workload);
            } else { std::cout << "Usage: add employee <path> '<name>' [workload...]" << std::endl; }
        } else { std::cout << "Error: Unknown 'add' subcommand '" << tokens[1] << "'." << std::endl; }
    } else if (cmd_keyword == "query") {
        if (tokens.size() < 5 || toLower(tokens[1]) != "columns") { std::cout << "Usage: query columns <cols> where <path> [row_sum]" << std::endl; return; }
        std::vector<std::string> cols; size_t idx = 2;
        while(idx < tokens.size() && toLower(tokens[idx]) != "where") { cols.push_back(tokens[idx++]); }
        if (idx >= tokens.size() || toLower(tokens[idx]) != "where") { std::cout << "Error: 'where' missing in query." << std::endl; return; }
        idx++; if (idx >= tokens.size()) { std::cout << "Error: Path missing after 'where'." << std::endl; return; }
        std::string path = tokens[idx++]; bool row_sum = false;
        if (idx < tokens.size() && toLower(tokens[idx]) == "row_sum") { row_sum = true; idx++; }
        if (idx < tokens.size()) { std::cout << "Error: Unexpected args after query: '" << tokens[idx] << "...'" << std::endl; return; }
        if (cols.empty()){ std::cout << "Error: No columns for query." << std::endl; return; }
        query(cols, path, row_sum);
    } else if (cmd_keyword == "remove") {
        if (tokens.size() < 2) { std::cout << "Error: 'remove' needs subcommand (node/employee)." << std::endl; return; }
        std::string type = toLower(tokens[1]);
        if (type == "node") { // remove node <path> [-r]
            if (tokens.size() == 3) { removeNode(tokens[2], false); }
            else if (tokens.size() == 4 && (tokens[3] == "-r" || tokens[3] == "--recursive")) { removeNode(tokens[2], true); }
            else { std::cout << "Usage: remove node <path> [-r|--recursive]" << std::endl; }
        } else if (type == "employee") { // remove employee <node_path> '<employee_name>'
            if (tokens.size() == 4) { removeEmployee(tokens[2], tokens[3]); }
            else { std::cout << "Usage: remove employee <node_path> '<employee_name>'" << std::endl; }
        } else { std::cout << "Error: Unknown 'remove' subcommand '" << tokens[1] << "'." << std::endl; }
    } else if (cmd_keyword == "edit") {
        if (tokens.size() < 2) { std::cout << "Error: 'edit' needs subcommand (employee)." << std::endl; return; }
        std::string type = toLower(tokens[1]);
        if (type == "employee") { // edit employee <path> '<name>' workload <wl...>
            if (tokens.size() >= 6 && toLower(tokens[4]) == "workload") {
                std::string path = tokens[2]; std::string name = tokens[3];
                std::vector<std::pair<std::string, int>> new_wl;
                for (size_t i = 5; i < tokens.size(); ++i) {
                    size_t colon = tokens[i].find(':');
                    if (colon != std::string::npos && colon > 0 && colon < tokens[i].length() - 1) {
                        try { new_wl.push_back({tokens[i].substr(0, colon), std::stoi(tokens[i].substr(colon + 1))}); }
                        catch (const std::exception& e) { std::cout << "Error: Invalid hours in '" << tokens[i] << "': " << e.what() << std::endl; return; }
                    } else { std::cout << "Error: Invalid workload format '" << tokens[i] << "'." << std::endl; return; }
                }
                editEmployeeWorkload(path, name, new_wl);
            } else { std::cout << "Usage: edit employee <path> '<name>' workload <type:hours>..." << std::endl; }
        } else { std::cout << "Error: Unknown 'edit' subcommand '" << tokens[1] << "'." << std::endl; }
    } else if (cmd_keyword == "save") {
        if (tokens.size() == 2) { if (tokens.size() > 2) { std::cout << "Error: Too many args for 'save'." << std::endl; return; } save(tokens[1]); }
        else if (tokens.size() == 1) { std::cout << "Error: Missing filename for 'save'." << std::endl; std::cout << "Usage: save <filename>" << std::endl; }
        else { std::cout << "Error: Too many args for 'save'." << std::endl; std::cout << "Usage: save <filename>" << std::endl; }
    } else if (cmd_keyword == "load") {
        if (tokens.size() == 2) { if (tokens.size() > 2) { std::cout << "Error: Too many args for 'load'." << std::endl; return; } load(tokens[1]); }
        else if (tokens.size() == 1) { std::cout << "Error: Missing filename for 'load'." << std::endl; std::cout << "Usage: load <filename>" << std::endl; }
        else { std::cout << "Error: Too many args for 'load'." << std::endl; std::cout << "Usage: load <filename>" << std::endl; }
    } else {
        std::cout << "Unknown command: '" << tokens[0] << "'. Type 'help' for commands." << std::endl;
    }
}

void displayHelpInformation() {
    std::cout << "=== University Workload Database Management System ===" << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "  add node <path>" << std::endl;
    std::cout << "    - Adds an organizational node. Path segments are separated by '/'. " << std::endl;
    std::cout << "    - Example: add node faculty/science/mathematics" << std::endl;
    std::cout << std::endl;
    std::cout << "  add employee <path> '<name>' [<type1>:<hours1> <type2>:<hours2> ...]" << std::endl;
    std::cout << "    - Adds an employee to the specified node path with their workload." << std::endl;
    std::cout << "    - Employee name must be in single quotes if it contains spaces." << std::endl;
    std::cout << "    - Workload items are space-separated pairs of type:hours." << std::endl;
    std::cout << "    - Example: add employee faculty/science/mathematics 'Ivanov I.I.' lectures:40 seminars:60" << std::endl;
    std::cout << std::endl;
    std::cout << "  remove node <path> [-r | --recursive]" << std::endl;
    std::cout << "    - Removes an organizational node at the specified path." << std::endl;
    std::cout << "    - By default, only empty nodes (no children, no employees) can be removed." << std::endl;
    std::cout << "    - Use -r or --recursive to remove a node and all its contents (sub-nodes and employees)." << std::endl;
    std::cout << "    - Example (empty node): remove node faculty/arts/empty_dept" << std::endl;
    std::cout << "    - Example (recursive):  remove node faculty/science --recursive" << std::endl;
    std::cout << std::endl;
    std::cout << "  remove employee <node_path> '<employee_name>'" << std::endl;
    std::cout << "    - Removes an employee from the specified node." << std::endl;
    std::cout << "    - Employee name must be in single quotes if it contains spaces." << std::endl;
    std::cout << "    - Example: remove employee faculty/science/mathematics 'Ivanov I.I.'" << std::endl;
    std::cout << std::endl;
    std::cout << "  edit employee <node_path> '<employee_name>' workload [<new_type1>:<new_hours1> ...]" << std::endl;
    std::cout << "    - Replaces the entire workload of an existing employee." << std::endl;
    std::cout << "    - If no new workload items are provided, the employee's workload will be cleared." << std::endl;
    std::cout << "    - Example: edit employee faculty/science/mathematics 'Petrov P.P.' workload labs:50 project_new:30" << std::endl;
    std::cout << "    - Example (clear workload): edit employee faculty/science/mathematics 'Petrov P.P.' workload" << std::endl;
    std::cout << std::endl;
    std::cout << "  query columns <col1> [col2...] where <path> [row_sum]" << std::endl;
    std::cout << "    - Queries and displays employee data from the specified path and its sub-nodes." << std::endl;
    std::cout << "    - <cols>: Space-separated list of columns to display (e.g., name, lectures, seminars)." << std::endl;
    std::cout << "    - <path>: Path to the node to query." << std::endl;
    std::cout << "    - [row_sum]: Optional. If present, adds a column with the sum of numeric workload columns for each employee." << std::endl;
    std::cout << "    - Example: query columns name lectures seminars where faculty/science row_sum" << std::endl;
    std::cout << std::endl;
    std::cout << "  save <filename>" << std::endl;
    std::cout << "    - Saves the current state of the database to the specified file." << std::endl;
    std::cout << "    - Example: save my_database.txt" << std::endl;
    std::cout << std::endl;
    std::cout << "  load <filename>" << std::endl;
    std::cout << "    - Loads the database state from the specified file, overwriting current data." << std::endl;
    std::cout << "    - Example: load my_database.txt" << std::endl;
    std::cout << std::endl;
    std::cout << "  help" << std::endl;
    std::cout << "    - Shows this help message." << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
}