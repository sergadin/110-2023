#include "database.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <map>

// --- Пространство имен Validation ---
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
        if (path.empty()) return false; // Пустой путь невалиден для команд, требующих путь
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
            if (!std::isalnum(c) && c != '_' && c != '-' && c != ' ') return false;
        }
        return true;
    }
    bool isValidSubjectId(const std::string& id) {
        if (id.empty()) return false;
        for (char c : id) { 
            if (!std::isalnum(c) && c != '-') return false;
        }
        return true;
    }
    bool isValidSubjectName(const std::string& name) {
        return !name.empty(); 
    }
    const std::vector<std::string> VALID_DAYS = {"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
    bool isValidDayOfWeek(const std::string& day, const Database* db) {
        std::string lower_day = db->toLowerInternal(day); 
        return std::find(VALID_DAYS.begin(), VALID_DAYS.end(), lower_day) != VALID_DAYS.end();
    }
    bool isValidTimeSlot(const std::string& time_slot) {
        if (time_slot.length() != 11) return false;
        if (time_slot[2] != ':' || time_slot[5] != '-' || time_slot[8] != ':') return false;
        for (int i : {0, 1, 3, 4, 6, 7, 9, 10}) {
            if (!std::isdigit(time_slot[i])) return false;
        }
        // TODO: Более строгая проверка корректности времени (00-23, 00-59, start < end)
        return true;
    }
     bool isValidActivityType(const std::string& type) {
        return !type.empty(); 
    }
} 

// --- Вспомогательная функция для вывода справки ---
void Database::displayHelpInformation() const { // Сделана методом класса
    std::cout << "=== University Workload Database Management System ===" << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "  add node <path>" << std::endl;
    std::cout << "    - Example: add node faculty/science/mathematics" << std::endl;
    std::cout << "  add employee <path> '<name>' [<type1>:<hours1> ...]" << std::endl;
    std::cout << "    - Example: add employee faculty/cs 'Ivanov I.I.' lectures:40" << std::endl;
    std::cout << "  add_subject <id> '<name>'" << std::endl;
    std::cout << "    - Example: add_subject CS101 'Intro to Programming'" << std::endl;
    std::cout << "  list_subjects" << std::endl;
    std::cout << "  assign_subject_to_employee <emp_path> '<emp_name>' <subj_id>" << std::endl;
    std::cout << "    - Example: assign_subject_to_employee faculty/cs 'Ivanov I.I.' CS101" << std::endl;
    std::cout << "  add_schedule <emp_path> '<emp_name>' <subj_id> <activity> <day> '<time>' [room]" << std::endl;
    std::cout << "    - Example: add_schedule faculty/cs 'Ivanov I.I.' CS101 лекция Monday '09:00-10:30' 'A101'" << std::endl;
    std::cout << "  view_schedule <emp_path> '<emp_name>'" << std::endl;
    std::cout << "    - Example: view_schedule faculty/cs 'Ivanov I.I.'" << std::endl;
    std::cout << "  remove node <path> [-r | --recursive]" << std::endl;
    std::cout << "    - Example (empty): remove node faculty/arts/empty_dept" << std::endl;
    std::cout << "    - Example (recursive):  remove node faculty/science --recursive" << std::endl;
    std::cout << "  remove employee <node_path> '<employee_name>'" << std::endl;
    std::cout << "    - Example: remove employee faculty/cs 'Ivanov I.I.'" << std::endl;
    std::cout << "  edit employee <node_path> '<employee_name>' workload [<new_wl1>:<new_hr1> ...]" << std::endl;
    std::cout << "    - Example: edit employee faculty/cs 'Petrov P.P.' workload labs:50" << std::endl;
    std::cout << "  query columns <col1> [col2...] where <path> [row_sum]" << std::endl;
    std::cout << "    - Example: query columns name lectures where faculty/science row_sum" << std::endl;
    std::cout << "  save <filename>" << std::endl;
    std::cout << "    - Example: save my_database.txt" << std::endl;
    std::cout << "  load <filename>" << std::endl;
    std::cout << "    - Example: load my_database.txt" << std::endl;
    std::cout << "  reset_database" << std::endl;
    std::cout << "    - Clears all data from the current database session." << std::endl;
    std::cout << "  help" << std::endl;
    std::cout << "    - Shows this help message." << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
}

// --- Реализация методов Database ---
std::string Database::toLower(const std::string& str) const {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}
std::string Database::toLowerInternal(const std::string& str) const {
    return toLower(str);
}
std::vector<std::string> Database::tokenize(const std::string& cmd) const {
    std::vector<std::string> tokens; std::string current; bool inQuote = false;
    for (char c : cmd) {
        if (c == '\'' && !inQuote) { inQuote = true; } 
        else if (c == '\'' && inQuote) { inQuote = false; tokens.push_back(current); current.clear(); } 
        else if (c == ' ' && !inQuote) { if (!current.empty()) { tokens.push_back(current); current.clear(); } } 
        else { current += c; }
    }
    if (!current.empty()) { tokens.push_back(current); } return tokens;
}
Database::Database() { root = new Node(""); }
Database::~Database() { deleteTree(root); }
void Database::deleteTree(Node* node) {
    if (!node) return;
    for (auto& pair : node->children) { deleteTree(pair.second); }
    delete node;
}
std::vector<std::string> Database::splitPath(const std::string& path) const {
    std::vector<std::string> parts; if (path.empty()) return parts;
    std::stringstream ss(path); std::string part;
    while (std::getline(ss, part, '/')) { if (!part.empty()) { parts.push_back(part); } }
    return parts;
}
Node* Database::getNode(const std::string& path) {
    std::vector<std::string> parts = splitPath(path);
    if (path.empty() && parts.empty()) return root;
    if (!path.empty() && parts.empty() && path != "") return nullptr; 
    Node* current = root;
    for (const auto& part : parts) {
        auto it = current->children.find(part);
        if (it == current->children.end()) return nullptr;
        current = it->second;
    }
    return current;
}
Node* Database::createNodeByPath(const std::string& path) {
    std::vector<std::string> parts = splitPath(path);
    if (parts.empty() && !path.empty()) { std::cout << "Error: Invalid node path format '" << path << "'." << std::endl; return nullptr; }
    if (path.empty()){ std::cout << "Error: Cannot create node with empty path." << std::endl; return nullptr; } // Исправлено для CMD-11
    Node* current = root;
    for (const auto& part : parts) {
        if (!Validation::isValidNodeNamePart(part)) { std::cout << "Error: Invalid segment '" << part << "' in path '" << path << "'." << std::endl; return nullptr; }
        auto it = current->children.find(part);
        if (it == current->children.end()) { Node* newNode = new Node(part); current->children[part] = newNode; current = newNode; } 
        else { current = it->second; }
    }
    return current;
}
void Database::getAllEmployeesRecursive(Node* node, std::vector<Employee*>& emp_list) {
    if (!node) return;
    for (size_t i = 0; i < node->employees.size(); ++i) {
        emp_list.push_back(&(node->employees[i]));
    }
    for (auto& pair : node->children) {
        getAllEmployeesRecursive(pair.second, emp_list);
    }
}
Employee* Database::findEmployee(const std::string& node_path, const std::string& employee_name) {
    Node* node = getNode(node_path);
    if (!node) return nullptr;
    for (auto& emp : node->employees) {
        if (emp.name == employee_name) return &emp;
    }
    return nullptr;
}
bool Database::checkTimeSlotConflict(const Employee* employee, const std::string& day, const std::string& time_slot) const {
    if (!employee) return false;
    std::string lower_day = toLower(day);
    auto day_schedule_it = employee->schedule_by_day.find(lower_day);
    if (day_schedule_it != employee->schedule_by_day.end()) {
        for (const auto& entry : day_schedule_it->second) {
            if (entry.time_slot == time_slot) return true; // Упрощенная проверка
        }
    }
    return false;
}
int Database::dayOfWeekToIndex(const std::string& day) const {
    std::string lower_day = toLower(day);
    for (size_t i = 0; i < Validation::VALID_DAYS.size(); ++i) {
        if (Validation::VALID_DAYS[i] == lower_day) return i;
    }
    return Validation::VALID_DAYS.size(); 
}
void Database::addNode(const std::string& path) {
    if (path.empty()){ std::cout << "Error: Path for add node cannot be empty." << std::endl; return; }
    if (!Validation::isValidPath(path, this)) { std::cout << "Error: Invalid path format for add node: '" << path << "'" << std::endl; return; }
    Node* n = createNodeByPath(path);
    if (n) std::cout << "Node added/exists at path: " << path << std::endl;
}
void Database::addEmployee(const std::string& path, const std::string& name, const std::vector<std::pair<std::string, int>>& workload) {
    if (!Validation::isValidPath(path, this)) { std::cout << "Error: Invalid path: '" << path << "'" << std::endl; return; }
    if (!Validation::isValidEmployeeName(name)) { std::cout << "Error: Invalid employee name: '" << name << "'" << std::endl; return; }
    if (workload.empty()) std::cout << "Warning: Employee '" << name << "' added with no workload." << std::endl;
    for(const auto& wl : workload){
        if(!Validation::isValidWorkloadType(wl.first)){ std::cout << "Error: Invalid workload type '" << wl.first << "'" << std::endl; return; }
        if(wl.second < 0){ std::cout << "Error: Workload hours for '" << wl.first << "' cannot be negative." << std::endl; return; }
    }
    Node* n = getNode(path);
    if (!n) { std::cout << "Error: Node not found: '" << path << "'. Create node first." << std::endl; return; }
    for (const auto& emp : n->employees) if (emp.name == name) { std::cout << "Error: Employee '" << name << "' already exists in '" << path << "'" << std::endl; return; }
    n->employees.push_back({name, workload, {}, {}});
    std::cout << "Employee '" << name << "' added to node '" << path << "'" << std::endl;
}
void Database::query(const std::vector<std::string>& columns, const std::string& path, bool row_sum) {
    if (!Validation::isValidPath(path, this) && !path.empty()) { std::cout << "Error: Invalid query path: '" << path << "'" << std::endl; return; }
    if (columns.empty()) { std::cout << "Error: No columns for query." << std::endl; return; }
    Node* n = getNode(path);
    if (!n && !path.empty()) { std::cout << "Error: Node not found for query: '" << path << "'" << std::endl; return; }
    if (!n && path.empty()) n = root;
    std::vector<Employee*> allEmpPtrs; 
    getAllEmployeesRecursive(n, allEmpPtrs);
    if (allEmpPtrs.empty()) { std::cout << "No employees found under path: '" << path << "'" << std::endl; return; }
    for (const auto& col : columns) std::cout << std::left << std::setw(20) << col;
    if (row_sum) std::cout << std::left << std::setw(15) << "row_sum";
    std::cout << std::endl;
    for (size_t i = 0; i < columns.size(); ++i) std::cout << std::string(20, '-');
    if (row_sum) std::cout << std::string(15, '-');
    std::cout << std::endl;
    for (const auto* emp_ptr : allEmpPtrs) { 
        const Employee& emp = *emp_ptr; 
        int currentSum = 0;
        for (const auto& col_h : columns) {
            std::string lower_col_h = toLower(col_h);
            if (lower_col_h == "name") std::cout << std::left << std::setw(20) << emp.name;
            else {
                auto it = std::find_if(emp.workload.begin(), emp.workload.end(),
                    [this, &lower_col_h](const auto& p){ return this->toLower(p.first) == lower_col_h; });
                if (it != emp.workload.end()) { std::cout << std::left << std::setw(15) << it->second; if (row_sum) currentSum += it->second; } 
                else { std::cout << std::left << std::setw(15) << 0; }
            }
        }
        if (row_sum) std::cout << std::left << std::setw(15) << currentSum;
        std::cout << std::endl;
    }
}
void Database::addSubject(const std::string& id, const std::string& name) {
    if (!Validation::isValidSubjectId(id)) { std::cout << "Error: Subject ID '" << id << "' is invalid or empty." << std::endl; return; }
    if (!Validation::isValidSubjectName(name)) { std::cout << "Error: Subject name cannot be empty." << std::endl; return; }
    if (subject_catalog.count(id)) { std::cout << "Error: Subject with ID '" << id << "' already exists." << std::endl; return; }
    subject_catalog[id] = {id, name};
    std::cout << "Subject '" << name << "' (ID: " << id << ") added." << std::endl;
}
void Database::listSubjects() const {
    if (subject_catalog.empty()) { std::cout << "No subjects in catalog." << std::endl; return; }
    std::cout << std::left << std::setw(15) << "Subject ID" << "| " << "Subject Name" << std::endl;
    std::cout << std::string(15, '-') << "+-" << std::string(30, '-') << std::endl;
    for (const auto& pair : subject_catalog) { // unordered_map не гарантирует порядок, для тестов может быть ОК
        std::cout << std::left << std::setw(15) << pair.second.id << "| " << pair.second.name << std::endl;
    }
}
void Database::assignSubjectToEmployee(const std::string& node_path, const std::string& employee_name, const std::string& subject_id) {
    Employee* emp = findEmployee(node_path, employee_name);
    if (!emp) { std::cout << "Error: Employee '" << employee_name << "' not found at path '" << node_path << "'." << std::endl; return; }
    if (!subject_catalog.count(subject_id)) { std::cout << "Error: Subject with ID '" << subject_id << "' not found." << std::endl; return; }
    if (emp->assigned_subject_ids.count(subject_id)) {
        std::cout << "Info: Subject '" << subject_id << "' is already assigned to employee '" << employee_name << "'." << std::endl; return;
    }
    emp->assigned_subject_ids.insert(subject_id);
    std::cout << "Subject '" << subject_id << "' assigned to employee '" << employee_name << "'." << std::endl;
}
void Database::addScheduleEntry(const std::string& node_path, const std::string& employee_name,
                               const std::string& subject_id, const std::string& activity_type,
                               const std::string& day, const std::string& time_slot, const std::string& room) {
    Employee* emp = findEmployee(node_path, employee_name);
    if (!emp) { std::cout << "Error: Employee '" << employee_name << "' not found at path '" << node_path << "'." << std::endl; return; }
    if (!subject_catalog.count(subject_id)) { std::cout << "Error: Subject with ID '" << subject_id << "' not found." << std::endl; return; }
    if (!emp->assigned_subject_ids.count(subject_id)) {
        std::cout << "Error: Subject '" << subject_id << "' is not assigned to employee '" << employee_name << "'. Assign subject first." << std::endl; return;
    }
    if (!Validation::isValidActivityType(activity_type)) { std::cout << "Error: Activity type cannot be empty." << std::endl; return; }
    if (!Validation::isValidDayOfWeek(day, this)) { std::cout << "Error: Invalid day of week '" << day << "'." << std::endl; return; }
    if (!Validation::isValidTimeSlot(time_slot)) { std::cout << "Error: Invalid time slot format '" << time_slot << "'." << std::endl; return; }
    std::string lower_day = toLower(day);
    if (checkTimeSlotConflict(emp, lower_day, time_slot)) {
        std::cout << "Error: Time slot conflict for employee '" << employee_name << "' on " << day << " at " << time_slot << "." << std::endl; return;
    }
    emp->schedule_by_day[lower_day].push_back({subject_id, activity_type, lower_day, time_slot, room});
    std::sort(emp->schedule_by_day[lower_day].begin(), emp->schedule_by_day[lower_day].end());
    std::cout << "Scheduled: " << subject_id << " (" << activity_type << ") for " << employee_name 
              << " on " << day << " " << time_slot << (room.empty() ? "" : " in room '" + room + "'") << "." << std::endl;
}
void Database::viewSchedule(const std::string& node_path, const std::string& employee_name) const {
    const Employee* emp = const_cast<Database*>(this)->findEmployee(node_path, employee_name);
    if (!emp) { std::cout << "Error: Employee '" << employee_name << "' not found at path '" << node_path << "'." << std::endl; return; }
    if (emp->schedule_by_day.empty()) { std::cout << "No schedule found for employee '" << employee_name << "'." << std::endl; return; }
    std::cout << "Schedule for " << emp->name << ":" << std::endl;
    
    std::vector<std::pair<int, std::string>> sorted_day_keys;
    for(const auto& day_pair : emp->schedule_by_day) {
        sorted_day_keys.push_back({dayOfWeekToIndex(day_pair.first), day_pair.first});
    }
    std::sort(sorted_day_keys.begin(), sorted_day_keys.end());

    for (const auto& day_key_pair : sorted_day_keys) {
        const std::string& day_str = day_key_pair.second;
        const auto& entries = emp->schedule_by_day.at(day_str); // Используем at() для const доступа
        // Капитализация первого символа дня недели для вывода
        std::string display_day = day_str;
        if (!display_day.empty()) display_day[0] = std::toupper(display_day[0]);

        std::cout << "  " << display_day << ":" << std::endl;
        for (const auto& entry : entries) { 
            std::cout << "    " << entry.time_slot << ": "
                      << entry.subject_id << " (" << entry.activity_type << ")"
                      << (entry.room.empty() ? "" : " - Room '" + entry.room + "'") << std::endl;
        }
    }
}
void Database::resetDatabase() {
    deleteTree(root);
    root = new Node("");
    subject_catalog.clear();
    std::cout << "Database has been reset." << std::endl;
}
void Database::save(const std::string& filename) const {
    if (filename.empty()){ std::cout << "Error: Filename for save empty." << std::endl; return; }
    if (filename.find('/') != std::string::npos || filename.find('\\') != std::string::npos) {
        std::cout << "Error: Filename '" << filename << "' has path separators." << std::endl;
    }
    std::ofstream out(filename); if (!out) { std::cout << "Error opening file for saving: '" << filename << "'" << std::endl; return; }
    for(const auto& pair : subject_catalog){ out << "subject " << pair.second.id << " '" << pair.second.name << "'" << std::endl; }
    std::function<void(const Node*, const std::string&)> saveRec = 
        [&](const Node* curr, const std::string& cPath) {
        if (!curr) return;
        if (curr != root && (!cPath.empty())) {
             if(!curr->employees.empty() || !curr->children.empty() || !curr->name.empty()){
                out << "node " << cPath << std::endl;
             }
        }
        for (const auto& emp : curr->employees) {
            out << "employee " << cPath << " '" << emp.name << "'";
            for (const auto& wl : emp.workload) out << " " << wl.first << ":" << wl.second;
            out << std::endl;
            for (const std::string& subj_id : emp.assigned_subject_ids) {
                out << "emp_subject " << cPath << " '" << emp.name << "' " << subj_id << std::endl;
            }
            for (const auto& day_pair : emp.schedule_by_day) {
                for (const auto& entry : day_pair.second) {
                    out << "emp_schedule " << cPath << " '" << emp.name << "' "
                        << entry.subject_id << " " << entry.activity_type << " "
                        << entry.day_of_week << " '" << entry.time_slot << "' "
                        << (entry.room.empty() ? "NO_ROOM" : "'" + entry.room + "'") << std::endl;
                }
            }
        }
        for (const auto& pair : curr->children) {
            saveRec(pair.second, cPath.empty() ? pair.first : cPath + "/" + pair.first);
        }
    };
    saveRec(root, ""); out.close();
    std::cout << "Database saved to '" << filename << "'" << std::endl;
}
void Database::load(const std::string& filename) {
    if (filename.empty()){ std::cout << "Error: Filename for load empty." << std::endl; return; }
    std::ifstream in(filename); if (!in) { std::cout << "Error opening file for loading: '" << filename << "'" << std::endl; return; }
    resetDatabase(); 
    std::cout << "Loading database from '" << filename << "'..." << std::endl;
    std::string line; int lineNum = 0;
    while (std::getline(in, line)) {
        lineNum++; auto tokens = this->tokenize(line);
        if (tokens.empty() || (!tokens.empty() && tokens[0].rfind('#', 0) == 0)) continue;
        std::string cmd_type = toLower(tokens[0]);
        if (cmd_type == "node") {
            if (tokens.size() == 2) {
                if (!Validation::isValidPath(tokens[1], this)) { std::cout << "Warning(L" << lineNum << "): Invalid node path '" << tokens[1] << "'. Skip." << std::endl; continue; }
                this->createNodeByPath(tokens[1]);
            } else { std::cout << "Warning(L" << lineNum << "): Malformed 'node'. Skip." << std::endl; }
        } else if (cmd_type == "subject") { 
            if (tokens.size() == 3) { addSubject(tokens[1], tokens[2]); } 
            else { std::cout << "Warning(L" << lineNum << "): Malformed 'subject'. Skip." << std::endl; }
        } else if (cmd_type == "employee") {
            if (tokens.size() >= 3) { 
                std::string p_str = tokens[1]; std::string n_str = tokens[2];
                if (!Validation::isValidPath(p_str, this)) { std::cout << "Warning(L" << lineNum << "): Invalid path '" << p_str << "'. Skip." << std::endl; continue; }
                if (!Validation::isValidEmployeeName(n_str)) { std::cout << "Warning(L" << lineNum << "): Invalid emp name '" << n_str << "'. Skip." << std::endl; continue; }
                Node* nFE = getNode(p_str);
                if (!nFE) { nFE = createNodeByPath(p_str); if (!nFE) { std::cout << "Warning(L" << lineNum << "): Fail create/get node '" << p_str << "'. Skip." << std::endl; continue; } }
                std::vector<std::pair<std::string, int>> wl_v;
                for (size_t i = 3; i < tokens.size(); ++i) {
                    size_t cPos = tokens[i].find(':');
                    if (cPos!=std::string::npos && cPos>0 && cPos<tokens[i].length()-1) {
                        std::string t = tokens[i].substr(0,cPos), h=tokens[i].substr(cPos+1);
                        if(Validation::isValidWorkloadType(t)){try{int hv=std::stoi(h); if(hv>=0)wl_v.push_back({t,hv}); else std::cout<<"W(L"<<lineNum<<"): Neg hours. Skip item."<<std::endl;}catch(const std::exception&){std::cout<<"W(L"<<lineNum<<"): Inv hours. Skip item."<<std::endl;}}
                        else std::cout<<"W(L"<<lineNum<<"): Inv wl type. Skip item."<<std::endl;
                    } else {std::cout<<"W(L"<<lineNum<<"): Inv wl fmt. Skip item."<<std::endl;}
                }
                bool ex=false; for(const auto& e : nFE->employees) if(e.name==n_str) ex=true;
                if(!ex) nFE->employees.push_back({n_str, wl_v, {}, {}});
            } else { std::cout << "Warning(L" << lineNum << "): Malformed 'employee'. Skip." << std::endl; }
        } else if (cmd_type == "emp_subject") { 
            if (tokens.size() == 4) { assignSubjectToEmployee(tokens[1], tokens[2], tokens[3]); } 
            else { std::cout << "Warning(L" << lineNum << "): Malformed 'emp_subject'. Skip." << std::endl; }
        } else if (cmd_type == "emp_schedule") { 
            if (tokens.size() == 7 || tokens.size() == 8) { 
                std::string room_val = (tokens.size() == 8 && tokens[7] != "NO_ROOM") ? tokens[7] : "";
                addScheduleEntry(tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6], room_val);
            } else { std::cout << "Warning(L" << lineNum << "): Malformed 'emp_schedule'. Skip." << std::endl; }
        } else { std::cout << "Warning(L" << lineNum << "): Unknown line: '" << line << "'. Skip." << std::endl; }
    }
    in.close(); std::cout << "Database loaded from '" << filename << "'" << std::endl;
}
void Database::removeNode(const std::string& path, bool recursive_delete) {
    if (!Validation::isValidPath(path, this) || path.empty()) { std::cout << "Error: Invalid path '" << path << "'." << std::endl; return; }
    std::vector<std::string> parts = splitPath(path); if (parts.empty()) { std::cout << "Error: Cannot remove root." << std::endl; return; }
    Node* current_s = root; Node* parent_target = root; 
    if (parts.size() > 1) { 
        for (size_t i = 0; i < parts.size() - 1; ++i) {
            auto it = current_s->children.find(parts[i]);
            if (it == current_s->children.end()) { std::cout << "Error: Path segment '" << parts[i] << "' not found." << std::endl; return; }
            current_s = it->second;
        }
        parent_target = current_s;
    } 
    auto target_it = parent_target->children.find(parts.back());
    if (target_it == parent_target->children.end()) { std::cout << "Error: Target node '" << parts.back() << "' not found." << std::endl; return; }
    Node* target_n = target_it->second;
    if (!recursive_delete && (!target_n->children.empty() || !target_n->employees.empty())) {
        std::cout << "Error: Node '" << path << "' not empty. Use recursive delete." << std::endl; return;
    }
    parent_target->children.erase(parts.back()); deleteTree(target_n);
    std::cout << "Node '" << path << "' removed." << std::endl;
}
void Database::removeEmployee(const std::string& node_path, const std::string& employee_name) {
    if (!Validation::isValidPath(node_path, this) || node_path.empty()) { std::cout << "Error: Invalid node path '" << node_path << "'." << std::endl; return; }
    if (!Validation::isValidEmployeeName(employee_name)) { std::cout << "Error: Invalid employee name '" << employee_name << "'." << std::endl; return; }
    Node* n = getNode(node_path); if (!n) { std::cout << "Error: Node not found: '" << node_path << "'." << std::endl; return; }
    auto& emps = n->employees;
    auto it = std::remove_if(emps.begin(), emps.end(), [&](const Employee& e){ return e.name == employee_name; });
    if (it != emps.end()) { emps.erase(it, emps.end()); std::cout << "Employee '" << employee_name << "' removed from '" << node_path << "'." << std::endl; }
    else { std::cout << "Error: Employee '" << employee_name << "' not found in '" << node_path << "'." << std::endl; }
}
void Database::editEmployeeWorkload(const std::string& node_path, const std::string& employee_name, const std::vector<std::pair<std::string, int>>& new_workload) {
    if (!Validation::isValidPath(node_path, this) || node_path.empty()) { std::cout << "Error: Invalid node path '" << node_path << "'." << std::endl; return; }
    if (!Validation::isValidEmployeeName(employee_name)) { std::cout << "Error: Invalid employee name '" << employee_name << "'." << std::endl; return; }
    if (new_workload.empty()) std::cout << "Warning: New workload for '" << employee_name << "' is empty. Workload cleared." << std::endl;
    for(const auto& wl : new_workload){
        if(!Validation::isValidWorkloadType(wl.first)){ std::cout << "Error: Invalid new workload type '" << wl.first << "'." << std::endl; return; }
        if(wl.second < 0){ std::cout << "Error: New workload hours for '" << wl.first << "' cannot be negative." << std::endl; return; }
    }
    Employee* emp_ptr = findEmployee(node_path, employee_name); 
    if (!emp_ptr) { std::cout << "Error: Employee '" << employee_name << "' not found in '" << node_path << "'." << std::endl; return; }
    emp_ptr->workload = new_workload;
    std::cout << "Workload for '" << employee_name << "' in '" << node_path << "' updated." << std::endl;
}
void Database::processCommand(const std::string& command_line) {
    if (command_line.empty() || command_line.find_first_not_of(" \t\n\r") == std::string::npos) return;
    auto tokens = tokenize(command_line); if (tokens.empty()) return;
    std::string cmd = toLower(tokens[0]);
    if (cmd == "help") {
        if (tokens.size() == 1) displayHelpInformation();
        else std::cout << "Usage: help" << std::endl;
    } else if (cmd == "add") {
        if (tokens.size() < 2) { std::cout << "Error: 'add' needs subcommand." << std::endl; return; }
        std::string type = toLower(tokens[1]);
        if (type == "node") { if (tokens.size() == 3) addNode(tokens[2]); else std::cout << "Usage: add node <path>" << std::endl; }
        else if (type == "employee") {
            if (tokens.size() >= 4) {
                std::string p = tokens[2], n_emp = tokens[3]; std::vector<std::pair<std::string, int>> wl;
                if (tokens.size() >= 5) for (size_t i=4; i<tokens.size(); ++i) {
                    size_t c = tokens[i].find(':');
                    if (c!=std::string::npos && c>0 && c<tokens[i].length()-1) { try {wl.push_back({tokens[i].substr(0,c), std::stoi(tokens[i].substr(c+1))});} catch (const std::exception& e){std::cout<<"Err: Invalid hours '"<<tokens[i]<<"': "<<e.what()<<std::endl;return;}}
                    else {std::cout<<"Err: Invalid wl format '"<<tokens[i]<<"'."<<std::endl;return;}
                } addEmployee(p,n_emp,wl);
            } else std::cout << "Usage: add employee <path> '<name>' [wl...]" << std::endl;
        } else if (type == "subject") { 
            if (tokens.size() == 4) addSubject(tokens[2], tokens[3]); // add subject ID 'Name'
            else std::cout << "Usage: add subject <id> '<name>'" << std::endl;
        } else if (type == "schedule") { 
            if (tokens.size() == 8 || tokens.size() == 9) { // add schedule path name subj_id activity day 'time' [room]
                 // tokens[0]=add, [1]=schedule, [2]=path, [3]=name, [4]=subj_id, [5]=activity, [6]=day, [7]=time, [8]=room(opt)
                addScheduleEntry(tokens[2], tokens[3], tokens[4], tokens[5], tokens[6], tokens[7], (tokens.size() == 9 ? tokens[8] : ""));
            } else { std::cout << "Usage: add schedule <emp_path> '<emp_name>' <subj_id> <activity> <day> '<time_slot>' [room]" << std::endl; }
        }
        else { std::cout << "Error: Unknown 'add' subcommand '" << tokens[1] << "'." << std::endl; }
    } else if (cmd == "list_subjects") {
        if (tokens.size() == 1) listSubjects(); else std::cout << "Usage: list_subjects" << std::endl;
    } else if (cmd == "assign_subject_to_employee") {
        // assign_subject_to_employee <emp_path> '<emp_name>' <subj_id>
        // tokens: [0]command, [1]path, [2]name, [3]subj_id --> size 4
        if (tokens.size() == 4) { 
            assignSubjectToEmployee(tokens[1], tokens[2], tokens[3]);
        } else { 
            std::cout << "Usage: assign_subject_to_employee <emp_path> '<emp_name>' <subj_id>" << std::endl; 
        }
    } else if (cmd == "view_schedule") {
        // view_schedule <emp_path> '<emp_name>'
        // tokens: [0]command, [1]path, [2]name --> size 3
        if (tokens.size() == 3) {
            viewSchedule(tokens[1], tokens[2]);
        } else { 
            std::cout << "Usage: view_schedule <emp_path> '<emp_name>'" << std::endl; 
        }
    }
     else if (cmd == "query") {
        if (tokens.size()<5 || toLower(tokens[1])!="columns") {std::cout<<"Usage: query columns <c> where <p> [row_sum]"<<std::endl;return;}
        std::vector<std::string> cols; size_t i=2; while(i<tokens.size() && toLower(tokens[i])!="where") cols.push_back(tokens[i++]);
        if (i>=tokens.size() || toLower(tokens[i])!="where") {std::cout<<"Err: 'where' missing."<<std::endl;return;} i++;
        if (i>=tokens.size()) {std::cout<<"Err: Path missing."<<std::endl;return;} std::string p=tokens[i++]; bool rs=false;
        if (i<tokens.size() && toLower(tokens[i])=="row_sum") {rs=true; i++;}
        if (i<tokens.size()) {std::cout<<"Err: Unexpected args: '"<<tokens[i]<<"..."<<std::endl;return;}
        if (cols.empty()){std::cout<<"Err: No columns."<<std::endl;return;} query(cols,p,rs);
    } else if (cmd == "remove") {
        if (tokens.size()<2) {std::cout<<"Err: 'remove' needs subcommand."<<std::endl;return;} std::string t=toLower(tokens[1]);
        if (t=="node") { if (tokens.size()==3) removeNode(tokens[2],false); else if (tokens.size()==4 && (tokens[3]=="-r"||tokens[3]=="--recursive")) removeNode(tokens[2],true); else std::cout<<"Usage: remove node <p> [-r]"<<std::endl;}
        else if (t=="employee") { if (tokens.size()==4) removeEmployee(tokens[2],tokens[3]); else std::cout<<"Usage: remove employee <p> '<name>' "<<std::endl;}
        else std::cout<<"Err: Unknown 'remove' subcommand '"<<tokens[1]<<"'."<<std::endl;
    } else if (cmd == "edit") {
        if (tokens.size()<2) {std::cout<<"Err: 'edit' needs subcommand."<<std::endl;return;} std::string t=toLower(tokens[1]);
        if (t=="employee") {
            if (tokens.size()>=6 && toLower(tokens[4])=="workload") {
                std::string p=tokens[2], n_emp=tokens[3]; std::vector<std::pair<std::string,int>> wl;
                for(size_t i=5; i<tokens.size(); ++i) { size_t c=tokens[i].find(':');
                    if(c!=std::string::npos && c>0 && c<tokens[i].length()-1){ try {wl.push_back({tokens[i].substr(0,c),std::stoi(tokens[i].substr(c+1))});} catch(const std::exception&e){std::cout<<"Err: Invalid hours '"<<tokens[i]<<"': "<<e.what()<<std::endl;return;}}
                    else {std::cout<<"Err: Invalid wl format '"<<tokens[i]<<"'."<<std::endl;return;}
                } editEmployeeWorkload(p,n_emp,wl);
            } else std::cout<<"Usage: edit employee <p> '<name>' workload <type:h>..."<<std::endl;
        } else std::cout<<"Err: Unknown 'edit' subcommand '"<<tokens[1]<<"'."<<std::endl;
    } else if (cmd == "save") {
        if (tokens.size()==2) {if(tokens.size()>2){std::cout<<"Err: Too many args 'save'."<<std::endl;return;} save(tokens[1]);}
        else if (tokens.size()==1) {std::cout<<"Err: Missing filename 'save'."<<std::endl;std::cout<<"Usage: save <fn>"<<std::endl;}
        else {std::cout<<"Err: Too many args 'save'."<<std::endl;std::cout<<"Usage: save <fn>"<<std::endl;}
    } else if (cmd == "load") {
        if (tokens.size()==2) {if(tokens.size()>2){std::cout<<"Err: Too many args 'load'."<<std::endl;return;} load(tokens[1]);}
        else if (tokens.size()==1) {std::cout<<"Err: Missing filename 'load'."<<std::endl;std::cout<<"Usage: load <fn>"<<std::endl;}
        else {std::cout<<"Err: Too many args 'load'."<<std::endl;std::cout<<"Usage: load <fn>"<<std::endl;}
    } else if (cmd == "reset_database") { 
        if (tokens.size() == 1) resetDatabase();
        else std::cout << "Usage: reset_database" << std::endl;
    }
    else {
        std::cout << "Unknown command: '" << tokens[0] << "'. Type 'help' for commands." << std::endl;
    }
}