#include "database.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <limits>

// --- Реализация вспомогательных функций для DayOfWeek ---
std::string dayOfWeekToString(DayOfWeek day) {
    switch (day) {
        case DayOfWeek::MONDAY:    return "Monday";
        case DayOfWeek::TUESDAY:   return "Tuesday";
        case DayOfWeek::WEDNESDAY: return "Wednesday";
        case DayOfWeek::THURSDAY:  return "Thursday";
        case DayOfWeek::FRIDAY:    return "Friday";
        case DayOfWeek::SATURDAY:  return "Saturday";
        default:                   return "Unknown";
    }
}

DayOfWeek stringToDayOfWeek(const std::string& s_day_in) {
    std::string s_day = s_day_in;
    std::transform(s_day.begin(), s_day.end(), s_day.begin(), ::tolower);
    if (s_day == "monday" || s_day == "mon" || s_day == "пн") return DayOfWeek::MONDAY;
    if (s_day == "tuesday" || s_day == "tue" || s_day == "вт") return DayOfWeek::TUESDAY;
    if (s_day == "wednesday" || s_day == "wed" || s_day == "ср") return DayOfWeek::WEDNESDAY;
    if (s_day == "thursday" || s_day == "thu" || s_day == "чт") return DayOfWeek::THURSDAY;
    if (s_day == "friday" || s_day == "fri" || s_day == "пт") return DayOfWeek::FRIDAY;
    if (s_day == "saturday" || s_day == "sat" || s_day == "сб") return DayOfWeek::SATURDAY;
    return DayOfWeek::UNKNOWN;
}


// --- Функции валидации ---
namespace Validation {
    bool isValidNodeNamePart(const std::string& name_part) {
        if (name_part.empty()) {
            return false;
        }
        for (char c : name_part) {
            if (!std::isalnum(c) && c != '_' && c != '-') {
                if (c == '.' || c == ' ') continue;
                return false;
            }
        }
        return true;
    }

    bool isValidPath(const std::string& path, const Database* db) {
        if (path.empty() && path != "") {
            std::cout << "Error: Path (non-root) cannot be effectively empty if specified." << std::endl;
            return false;
        }
        std::vector<std::string> parts = db->splitPath(path);
        if (parts.empty() && !path.empty()) {
            std::cout << "Error: Path '" << path << "' results in no valid segments." << std::endl;
            return false;
        }
        for (const std::string& part : parts) {
            if (!isValidNodeNamePart(part)) {
                std::cout << "Error: Path segment '" << part << "' in path '" << path << "' is invalid." << std::endl;
                return false;
            }
        }
        return true;
    }

    bool isValidEmployeeName(const std::string& name) {
        if (name.empty()) {
            std::cout << "Error: Employee name cannot be empty." << std::endl;
            return false;
        }
        for (char c : name) {
            if (c == '/' || c == '\'' || c == ':') {
                std::cout << "Error: Employee name '" << name << "' contains invalid character '" << c << "'." << std::endl;
                return false;
            }
        }
        return true;
    }

    bool isValidTypeFormat(const std::string& type) {
        if (type.empty()) {
            std::cout << "Error: Workload/Class type cannot be empty." << std::endl;
            return false;
        }
        for (char c : type) {
            if (!std::isalnum(c) && c != '_' && c != '-' && c != ' ') {
                std::cout << "Error: Workload/Class type '" << type << "' contains invalid character '" << c << "'." << std::endl;
                return false;
            }
        }
        return true;
    }


    bool isValidSubjectId(const std::string& id) {
        if (id.empty()) {
            std::cout << "Error: Subject ID cannot be empty." << std::endl;
            return false;
        }
        for (char c : id) {
            if (!std::isalnum(c) && c != '-') {
                std::cout << "Error: Subject ID '" << id << "' contains invalid character '" << c << "'. Allowed: alphanumeric, '-'." << std::endl;
                return false;
            }
        }
        return true;
    }
    bool isValidSubjectName(const std::string& name) {
        if (name.empty()) {
            std::cout << "Error: Subject name cannot be empty." << std::endl;
            return false;
        }
        return true;
    }
     bool isValidTimeSlot(const std::string& time_slot) {
        if (time_slot.empty()) {
            std::cout << "Error: Time slot cannot be empty." << std::endl;
            return false;
        }
        return true;
    }
    bool isValidRoom(const std::string& room) {
        for (char c : room) {
            if (c == '/' || c == '\'' || c == ':') {
                std::cout << "Error: Room name '" << room << "' contains invalid character '" << c << "'." << std::endl;
                return false;
            }
        }
        return true;
    }
}


// --- Реализация методов Database ---

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

Employee* Database::getEmployee(const std::string& path, const std::string& employee_name) {
    Node* node = getNode(path);
    if (!node) {
        return nullptr;
    }
    for (Employee& emp : node->employees) {
        if (emp.name == employee_name) {
            return &emp;
        }
    }
    return nullptr;
}


Node* Database::createNodeByPath(const std::string& path) {
    std::vector<std::string> parts = splitPath(path);
    if (parts.empty()) {
         std::cout << "Error: Cannot create node. Path '" << path << "' is invalid or results in no valid segments." << std::endl;
        return nullptr;
    }
    Node* current = root;
    for (const auto& part : parts) {
        if (!Validation::isValidNodeNamePart(part)) {
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

void Database::addNodeCmd(const std::vector<std::string>& args) {
    const std::string& path = args[2];
    if (!Validation::isValidPath(path, this)) {
        return;
    }
    Node* created_node = createNodeByPath(path);
    if (created_node) {
        std::cout << "Node added/exists at path: " << path << std::endl;
    }
}

void Database::addEmployeeCmd(const std::vector<std::string>& args) {
    const std::string& path = args[2];
    const std::string& name = args[3];
    
    if (!Validation::isValidPath(path, this)) { return; }
    if (!Validation::isValidEmployeeName(name)) { return; }

    std::vector<std::pair<std::string, int>> workload_vec;
    bool workload_provided = args.size() > 4;
    for (size_t i = 4; i < args.size(); ++i) {
        const std::string& wl_item_str = args[i];
        size_t colonPos = wl_item_str.find(':');
        if (colonPos != std::string::npos && colonPos > 0 && colonPos < wl_item_str.length() - 1) {
            std::string type = wl_item_str.substr(0, colonPos);
            std::string hours_str = wl_item_str.substr(colonPos + 1);
            if (!Validation::isValidTypeFormat(type)) { return; }
            try {
                int hours = std::stoi(hours_str);
                if (hours < 0) {
                    std::cout << "Error: Workload hours (" << hours << ") for type '" << type << "' cannot be negative." << std::endl; return;
                }
                workload_vec.push_back({type, hours});
            } catch (const std::invalid_argument& ) {
                std::cout << "Error: Invalid number format for hours in workload item '" << wl_item_str << "'." << std::endl; return;
            } catch (const std::out_of_range& ) {
                std::cout << "Error: Hours value out of range in workload item '" << wl_item_str << "'." << std::endl; return;
            }
        } else {
            std::cout << "Error: Invalid workload format for item '" << wl_item_str << "'. Expected type:hours" << std::endl; return;
        }
    }
    if (!workload_provided && args.size() == 4){
        std::cout << "Warning: Adding employee '" << name << "' with no workload specified." << std::endl;
    }

    Node* node = getNode(path);
    if (node == nullptr) {
        std::cout << "Error: Node not found at path: '" << path << "' to add employee. Please create the node first." << std::endl; return;
    }
    for (const auto& emp : node->employees) {
        if (emp.name == name) {
            std::cout << "Error: Employee '" << name << "' already exists in node '" << path << "'. Use a different name or update mechanism." << std::endl; return;
        }
    }
    node->employees.push_back({name, workload_vec, {}, {}});
    std::cout << "Employee '" << name << "' added to node '" << path << "'" << std::endl;
}

void Database::queryCmd(const std::vector<std::string>& args) {
    std::vector<std::string> cols_vec;
    size_t current_token_idx = 2; 
    while(current_token_idx < args.size() && toLower(args[current_token_idx]) != "where") {
        cols_vec.push_back(args[current_token_idx]);
        current_token_idx++;
    }
    if (cols_vec.empty()) { 
        std::cout << "Error: No columns specified for query." << std::endl; return;
    }
    if (current_token_idx >= args.size() || toLower(args[current_token_idx]) != "where") {
        std::cout << "Error: 'where' keyword missing or misplaced in query." << std::endl; return;
    }
    current_token_idx++; 
    if (current_token_idx >= args.size()) {
        std::cout << "Error: Path missing after 'where' in query." << std::endl; return;
    }
    std::string path_str = args[current_token_idx];
    current_token_idx++;
    bool row_sum_flag = false;
    if (current_token_idx < args.size() && toLower(args[current_token_idx]) == "row_sum") {
        row_sum_flag = true;
    }

    if (!Validation::isValidPath(path_str, this) && !path_str.empty()) {
         std::cout << "Error: Invalid path format for query: '" << path_str << "'" << std::endl; return;
    }
    for(const auto& col_name : cols_vec) {
        if (toLower(col_name) != "name" && toLower(col_name) != "row_sum" && !Validation::isValidTypeFormat(col_name)){
             std::cout << "Warning: Column name '" << col_name << "' has an unusual format or contains invalid characters for a workload type." << std::endl;
        }
    }
    Node* node = getNode(path_str);
    if (node == nullptr && !path_str.empty()) {
        std::cout << "Error: Node not found for query: '" << path_str << "'" << std::endl; return;
    }
    if (node == nullptr && path_str.empty()) node = root;
    auto allEmps = getAllEmployeesRecursive(node);
    if (allEmps.empty()) {
        std::cout << "No employees found under path: '" << path_str << "'" << std::endl; return;
    }
    std::vector<std::string> printColumns = cols_vec;
    for (size_t i = 0; i < printColumns.size(); ++i) {
        std::cout << std::left << std::setw(15) << printColumns[i];
    }
    if (row_sum_flag) {
        std::cout << std::left << std::setw(15) << "row_sum";
    }
    std::cout << std::endl;
    for (size_t i = 0; i < printColumns.size(); ++i) std::cout << std::string(15, '-');
    if (row_sum_flag) std::cout << std::string(15, '-');
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
                    if (row_sum_flag) currentRowSum += it->second;
                } else {
                    std::cout << std::left << std::setw(15) << 0;
                }
            }
        }
        if (row_sum_flag) {
            std::cout << std::left << std::setw(15) << currentRowSum;
        }
        std::cout << std::endl;
    }
}

void Database::handleAddSubject(const std::vector<std::string>& args) {
    const std::string& id = args[1];
    const std::string& name = args[2];
    if (!Validation::isValidSubjectId(id)) { return; }
    if (!Validation::isValidSubjectName(name)) { return; }
    if (subjects_catalog_.count(id)) {
        std::cout << "Error: Subject with ID '" << id << "' already exists." << std::endl; return;
    }
    subjects_catalog_[id] = {id, name};
    std::cout << "Subject '" << name << "' (ID: " << id << ") added." << std::endl;
}

void Database::handleListSubjects(const std::vector<std::string>& args) {
    if (subjects_catalog_.empty()) {
        std::cout << "No subjects in catalog." << std::endl; return;
    }
    std::cout << "Available subjects:" << std::endl;
    std::cout << std::left << std::setw(15) << "ID" << std::setw(30) << "Name" << std::endl;
    std::cout << std::string(45, '-') << std::endl;
    for (const auto& pair : subjects_catalog_) {
        std::cout << std::left << std::setw(15) << pair.second.id << std::setw(30) << pair.second.name << std::endl;
    }
}

void Database::handleAssignSubject(const std::vector<std::string>& args) {
    const std::string& path = args[1];
    const std::string& emp_name = args[2];
    const std::string& subject_id = args[3];

    if (!Validation::isValidPath(path, this)) { return; }
    if (!Validation::isValidEmployeeName(emp_name)) { return; }
    if (!Validation::isValidSubjectId(subject_id)) { return; }

    Employee* emp = getEmployee(path, emp_name);
    if (!emp) {
        std::cout << "Error: Employee '" << emp_name << "' not found at path '" << path << "'." << std::endl; return;
    }
    if (!subjects_catalog_.count(subject_id)) {
        std::cout << "Error: Subject with ID '" << subject_id << "' not found in catalog." << std::endl; return;
    }
    for (const std::string& assigned_id : emp->taught_subject_ids) {
        if (assigned_id == subject_id) {
            std::cout << "Info: Subject '" << subject_id << "' is already assigned to employee '" << emp_name << "'." << std::endl; return;
        }
    }
    emp->taught_subject_ids.push_back(subject_id);
    std::cout << "Subject '" << subjects_catalog_.at(subject_id).name << "' (ID: " << subject_id << ") assigned to employee '" << emp_name << "'." << std::endl;
}

void Database::handleAddSchedule(const std::vector<std::string>& args) {
    const std::string& path = args[1];
    const std::string& emp_name = args[2];
    const std::string& subject_id = args[3];
    const std::string& class_type = args[4];
    const std::string& day_str = args[5];
    const std::string& time_slot = args[6];
    std::string room = (args.size() == 8) ? args[7] : "";

    if (!Validation::isValidPath(path, this)) { return; }
    if (!Validation::isValidEmployeeName(emp_name)) { return; }
    if (!Validation::isValidSubjectId(subject_id)) { return; }
    if (!Validation::isValidTypeFormat(class_type)) { return; }
    DayOfWeek day = stringToDayOfWeek(day_str);
    if (day == DayOfWeek::UNKNOWN) {
        std::cout << "Error: Invalid day of week '" << day_str << "'. Use full name (e.g., Monday) or short (Mon, пн)." << std::endl; return;
    }
    if (!Validation::isValidTimeSlot(time_slot)) { return; }
    if (!Validation::isValidRoom(room)) { return; }

    Employee* emp = getEmployee(path, emp_name);
    if (!emp) {
        std::cout << "Error: Employee '" << emp_name << "' not found at path '" << path << "'." << std::endl; return;
    }
    if (!subjects_catalog_.count(subject_id)) {
        std::cout << "Error: Subject with ID '" << subject_id << "' not found in catalog." << std::endl; return;
    }
    bool subject_is_assigned_to_emp = false;
    for(const auto& id : emp->taught_subject_ids) if(id == subject_id) subject_is_assigned_to_emp = true;
    if(!subject_is_assigned_to_emp){
        std::cout << "Warning: Subject '" << subject_id << "' (Name: " << subjects_catalog_.at(subject_id).name
                  << ") is not explicitly assigned to '" << emp_name << "', but adding to schedule." << std::endl;
    }
    for (const auto& existing_class : emp->schedule) {
        if (existing_class.day == day && existing_class.time_slot == time_slot) {
            std::cout << "Error: Time slot conflict for employee '" << emp_name << "' on "
                      << dayOfWeekToString(day) << " at " << time_slot << ". Class already scheduled." << std::endl;
            return;
        }
    }
    emp->schedule.push_back({subject_id, class_type, day, time_slot, room});
    std::cout << "Scheduled class added for '" << emp_name << "': "
              << subjects_catalog_.at(subject_id).name << " (ID: " << subject_id << "), Type: " << class_type
              << ", On: " << dayOfWeekToString(day) << " at " << time_slot
              << (room.empty() ? "" : ", Room: " + room) << "." << std::endl;
}

void Database::handleViewSchedule(const std::vector<std::string>& args) {
    const std::string& path = args[1];
    const std::string& emp_name = args[2];
    if (!Validation::isValidPath(path, this)) { return; }
    if (!Validation::isValidEmployeeName(emp_name)) { return; }
    Employee* emp = getEmployee(path, emp_name);
    if (!emp) {
        std::cout << "Error: Employee '" << emp_name << "' not found at path '" << path << "'." << std::endl; return;
    }
    if (emp->schedule.empty()) {
        std::cout << "No schedule found for employee '" << emp_name << "'." << std::endl; return;
    }
    std::cout << "Schedule for " << emp_name << ":" << std::endl;
    std::cout << std::left
              << std::setw(12) << "Day"
              << std::setw(18) << "Time Slot"
              << std::setw(25) << "Subject Name (ID)"
              << std::setw(15) << "Class Type"
              << std::setw(12) << "Room" << std::endl;
    std::cout << std::string(82, '-') << std::endl;
    std::vector<ScheduledClass> sorted_schedule = emp->schedule;
    std::sort(sorted_schedule.begin(), sorted_schedule.end(), [](const ScheduledClass& a, const ScheduledClass& b){
        if (a.day != b.day) return a.day < b.day;
        return a.time_slot < b.time_slot; 
    });
    for (const auto& cls : sorted_schedule) {
        std::string subj_display_name = cls.subject_id;
        if(subjects_catalog_.count(cls.subject_id)){
            subj_display_name = subjects_catalog_.at(cls.subject_id).name + " (" + cls.subject_id + ")";
        }
        std::cout << std::left
                  << std::setw(12) << dayOfWeekToString(cls.day)
                  << std::setw(18) << cls.time_slot
                  << std::setw(25) << subj_display_name
                  << std::setw(15) << cls.class_type
                  << std::setw(12) << (cls.room.empty() ? "-" : cls.room) << std::endl;
    }
}

void Database::save(const std::string& filename) const {
    if (filename.empty()){
        std::cout << "Error: Filename for save cannot be empty." << std::endl; return;
    }
    if (filename.find('/') != std::string::npos || filename.find('\\') != std::string::npos) {
        std::cout << "Error: Filename '" << filename << "' should not contain path separators. Please provide a simple filename to save in the current directory." << std::endl;
    }
    std::ofstream out(filename);
    if (!out) {
        std::cout << "Error opening file for saving: '" << filename << "'" << std::endl; return;
    }
    std::cout << "Saving database to '" << filename << "'..." << std::endl;
    for (const auto& pair : subjects_catalog_) {
        out << "subject " << pair.second.id << " '" << pair.second.name << "'" << std::endl;
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
            for (const std::string& subj_id : emp.taught_subject_ids) {
                out << "emp_subject " << currentPathStr << " '" << emp.name << "' " << subj_id << std::endl;
            }
            for (const auto& sc : emp.schedule) {
                out << "emp_schedule " << currentPathStr << " '" << emp.name << "' "
                    << sc.subject_id << " " << sc.class_type << " "
                    << dayOfWeekToString(sc.day) << " '" << sc.time_slot << "' '" << sc.room << "'" << std::endl;
            }
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
        std::cout << "Error: Filename for load cannot be empty." << std::endl; return;
    }
    std::ifstream in(filename);
    if (!in) {
        std::cout << "Error opening file for loading: '" << filename << "'" << std::endl; return;
    }
    deleteTree(root);
    root = new Node("");
    subjects_catalog_.clear();
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
                if (!Validation::isValidPath(tokens[1], this)) { std::cout << "Warning (load line " << lineNum << "): Invalid node path '" << tokens[1] << "'. Skipping." << std::endl; continue; }
                this->createNodeByPath(tokens[1]);
            } else { std::cout << "Warning (load line " << lineNum << "): Malformed 'node' command. Skipping." << std::endl;}
        } else if (command_type == "subject") {
            if (tokens.size() == 3) {
                 const std::string& id = tokens[1];
                 const std::string& name = tokens[2];
                 if (Validation::isValidSubjectId(id) && Validation::isValidSubjectName(name)) {
                    subjects_catalog_[id] = {id, name};
                 } else { std::cout << "Warning (load line " << lineNum << "): Invalid subject data. Skipping." << std::endl; }
            } else { std::cout << "Warning (load line " << lineNum << "): Malformed 'subject' command. Skipping." << std::endl; }
        }
        else if (command_type == "employee") {
            if (tokens.size() >= 3) {
                std::string path_str = tokens[1];
                std::string name_str = tokens[2];
                if (!Validation::isValidPath(path_str, this)) { std::cout << "Warning (load line " << lineNum << "): Invalid path for employee. Skipping." << std::endl; continue; }
                if (!Validation::isValidEmployeeName(name_str)) { std::cout << "Warning (load line " << lineNum << "): Invalid name for employee. Skipping." << std::endl; continue; }
                Node* nodeForEmployee = getNode(path_str);
                if (!nodeForEmployee) nodeForEmployee = createNodeByPath(path_str);
                if (!nodeForEmployee) { std::cout << "Warning (load line " << lineNum << "): Failed to get/create node for employee. Skipping." << std::endl; continue; }
                std::vector<std::pair<std::string, int>> workload_vec;
                for (size_t i = 3; i < tokens.size(); ++i) {
                    size_t colonPos = tokens[i].find(':');
                    if (colonPos != std::string::npos && colonPos > 0 && colonPos < tokens[i].length() - 1) {
                        std::string type = tokens[i].substr(0, colonPos);
                        std::string hours_str = tokens[i].substr(colonPos + 1);
                        if (!Validation::isValidTypeFormat(type)) {std::cout << "Warning (load line " << lineNum << "): Invalid workload type '"<<type<<"'. Skipping item." << std::endl; continue;}
                        try { 
                            int hours = std::stoi(hours_str);
                            if(hours < 0) {std::cout << "Warning (load line " << lineNum << "): Negative hours for workload. Skipping item." << std::endl; continue;}
                            workload_vec.push_back({type, hours});
                        }
                        catch (const std::exception&) { std::cout << "Warning (load line " << lineNum << "): Invalid hours format for workload. Skipping item." << std::endl;}
                    } else { std::cout << "Warning (load line " << lineNum << "): Invalid workload item format. Skipping item." << std::endl;}
                }
                 bool exists = false;
                 for(const auto& e : nodeForEmployee->employees) if(e.name == name_str) exists = true;
                 if(!exists) {
                    nodeForEmployee->employees.push_back({name_str, workload_vec, {}, {}});
                 } else { std::cout << "Info (load line " << lineNum << "): Employee '" << name_str << "' already exists. Skipping." << std::endl;}
            } else { std::cout << "Warning (load line " << lineNum << "): Malformed 'employee' command. Skipping." << std::endl;}
        } else if (command_type == "emp_subject") {
            if (tokens.size() == 4) {
                Employee* emp = getEmployee(tokens[1], tokens[2]);
                const std::string& subj_id_to_assign = tokens[3];
                if (emp && subjects_catalog_.count(subj_id_to_assign) && Validation::isValidSubjectId(subj_id_to_assign)) {
                    bool already_assigned = false;
                    for(const auto& sid : emp->taught_subject_ids) if(sid == subj_id_to_assign) already_assigned = true;
                    if(!already_assigned) emp->taught_subject_ids.push_back(subj_id_to_assign);
                } else { std::cout << "Warning (load line " << lineNum << "): Cannot assign subject. Employee or subject not found, or invalid subject ID. Skipping." << std::endl;}
            } else { std::cout << "Warning (load line " << lineNum << "): Malformed 'emp_subject' command. Skipping." << std::endl;}
        } else if (command_type == "emp_schedule") {
            if (tokens.size() == 8) {
                Employee* emp = getEmployee(tokens[1], tokens[2]);
                const std::string& subj_id_sched = tokens[3];
                const std::string& class_type_sched = tokens[4];
                DayOfWeek day_sched = stringToDayOfWeek(tokens[5]);
                const std::string& time_slot_sched = tokens[6];
                const std::string& room_sched = tokens[7];
                if (emp && subjects_catalog_.count(subj_id_sched) && Validation::isValidSubjectId(subj_id_sched) &&
                    Validation::isValidTypeFormat(class_type_sched) && day_sched != DayOfWeek::UNKNOWN &&
                    Validation::isValidTimeSlot(time_slot_sched) && Validation::isValidRoom(room_sched) ) {
                    emp->schedule.push_back({subj_id_sched, class_type_sched, day_sched, time_slot_sched, room_sched});
                } else { std::cout << "Warning (load line " << lineNum << "): Invalid data for schedule item. Skipping." << std::endl;}
            } else { std::cout << "Warning (load line " << lineNum << "): Malformed 'emp_schedule' command. Skipping." << std::endl;}
        }
        else { std::cout << "Warning (load line " << lineNum << "): Unknown command type '" << command_type << "' in file. Skipping." << std::endl; }
    }
    in.close();
    std::cout << "Database loaded from '" << filename << "'" << std::endl;
}

// Вспомогательная функция для вывода справки, вызываемая из processCommand
void printDatabaseHelpContent(std::ostream& out_stream) {
    out_stream << "=== University Workload Database Management System ===" << std::endl;
    out_stream << "Available C++ application commands:" << std::endl;
    out_stream << "  add node <path>" << std::endl;
    out_stream << "  add employee <path> '<employee_name>' [workload_type:hours ...]" << std::endl;
    out_stream << "  add_subject <subject_id> '<subject_name>'" << std::endl;
    out_stream << "  list_subjects" << std::endl;
    out_stream << "  assign_subject_to_employee <employee_path> '<employee_name>' <subject_id>" << std::endl;
    out_stream << "  add_schedule <employee_path> '<employee_name>' <subject_id> <class_type> <day> '<time_slot>' ['<room>']" << std::endl;
    out_stream << "  view_schedule <employee_path> '<employee_name>'" << std::endl;
    out_stream << "  query columns <col1> [col2...] where <path> [row_sum]" << std::endl;
    out_stream << "  load <filename>" << std::endl;
    out_stream << "  save <filename>" << std::endl;
    out_stream << "  help - Show this help message" << std::endl;
    out_stream << "  exit - Disconnect from server and exit client program" << std::endl;
}

void Database::processCommand(const std::string& command_line) {
    if (command_line.empty() || command_line.find_first_not_of(" \t\n\r") == std::string::npos) {
        return;
    }
    auto tokens = tokenize(command_line);
    if (tokens.empty()) return;
    std::string cmd_keyword = toLower(tokens[0]);

    if (cmd_keyword == "add") {
        if (tokens.size() < 2) { std::cout << "Error: 'add' command requires a subcommand." << std::endl; return; }
        std::string add_type = toLower(tokens[1]);
        if (add_type == "node") {
            if(tokens.size() == 3) addNodeCmd(tokens);
            else std::cout << "Usage: add node <path>" << std::endl;
        } else if (add_type == "employee") {
            if(tokens.size() >= 4) addEmployeeCmd(tokens);
            else std::cout << "Usage: add employee <path> '<name>' [type:hours ...]" << std::endl;
        } else { std::cout << "Error: Unknown 'add' subcommand. Use 'node' or 'employee'." << std::endl; }
    } else if (cmd_keyword == "query") {
        if(tokens.size() >= 5 && toLower(tokens[1]) == "columns") queryCmd(tokens);
        else std::cout << "Usage: query columns <cols...> where <path> [row_sum]" << std::endl;
    }
    else if (cmd_keyword == "add_subject") {
        if(tokens.size() == 3) handleAddSubject({tokens[0], tokens[1], tokens[2]});
        else if(tokens.size() > 3) { // Обработка имени предмета с пробелами, если tokenize разбил
            std::string combined_name;
            for(size_t i = 2; i < tokens.size(); ++i) combined_name += (i > 2 ? " " : "") + tokens[i];
            handleAddSubject({tokens[0], tokens[1], combined_name});
        }
        else std::cout << "Usage: add_subject <id> \"<subject_name>\"" << std::endl;
    } else if (cmd_keyword == "list_subjects") {
        if(tokens.size() == 1) handleListSubjects(tokens);
        else std::cout << "Usage: list_subjects" << std::endl;
    } else if (cmd_keyword == "assign_subject_to_employee") {
        if(tokens.size() == 4) handleAssignSubject({tokens[0], tokens[1], tokens[2], tokens[3]});
        else if(tokens.size() > 4) { // Имя сотрудника с пробелами
            std::string combined_emp_name;
            for(size_t i = 2; i < tokens.size()-1; ++i) combined_emp_name += (i > 2 ? " " : "") + tokens[i];
             if(!combined_emp_name.empty()) handleAssignSubject({tokens[0], tokens[1], combined_emp_name, tokens.back()});
             else std::cout << "Usage: assign_subject_to_employee <employee_path> '<employee_name>' <subject_id>" << std::endl;
        }
        else std::cout << "Usage: assign_subject_to_employee <employee_path> '<employee_name>' <subject_id>" << std::endl;
    } else if (cmd_keyword == "add_schedule") {
        if(tokens.size() >= 7) handleAddSchedule(tokens);
        else std::cout << "Usage: add_schedule <employee_path> '<employee_name>' <subject_id> <class_type> <day_str> <time_slot> [room_str]" << std::endl;
    } else if (cmd_keyword == "view_schedule") {
        if(tokens.size() == 3) handleViewSchedule({tokens[0], tokens[1], tokens[2]});
         else if(tokens.size() > 3) { // Имя сотрудника с пробелами
            std::string combined_emp_name_vs;
            for(size_t i = 2; i < tokens.size(); ++i) combined_emp_name_vs += (i > 2 ? " " : "") + tokens[i];
            if(!combined_emp_name_vs.empty()) handleViewSchedule({tokens[0], tokens[1], combined_emp_name_vs});
            else std::cout << "Usage: view_schedule <employee_path> '<employee_name>'" << std::endl;
        }
        else std::cout << "Usage: view_schedule <employee_path> '<employee_name>'" << std::endl;
    }
    else if (cmd_keyword == "save") {
        if (tokens.size() == 2) { save(tokens[1]); }
        else { std::cout << "Usage: save <filename>" << std::endl; }
    } else if (cmd_keyword == "load") {
        if (tokens.size() == 2) { load(tokens[1]); }
        else { std::cout << "Usage: load <filename>" << std::endl; }
    } else if (cmd_keyword == "help") {
        if (tokens.size() == 1) {
            printDatabaseHelpContent(std::cout);
        } else {
            std::cout << "Usage: help" << std::endl;
        }
    }
    else {
        std::cout << "Unknown command: '" << tokens[0] << "'. Type 'help' for commands." << std::endl;
    }
}