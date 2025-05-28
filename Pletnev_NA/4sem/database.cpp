#include "database.h"
#include <sstream>
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>

Database::Database() : root(new TreeNode("root")) {}

TreeNode* Database::findOrCreateNode(const std::string& path) {
    std::istringstream iss(path);
    std::string segment;
    TreeNode* current = root.get();

    while (getline(iss, segment, '/')) {
        auto it = find_if(current->children.begin(), current->children.end(),
                           [&](const auto& child) { return child->name == segment; });

        if (it == current->children.end()) {
            current->children.emplace_back(new TreeNode(segment));
            it = prev(current->children.end());
        }
        current = it->get();
    }
    return current;
}

void Database::addNode(const std::string& path) {
    findOrCreateNode(path);
}

void Database::addWorkloadToEmployee(const std::string& path, const std::string& name,
                          const std::vector<std::pair<std::string, int>>& workloadEntries) {
    TreeNode* node = findOrCreateNode(path);
    Employee emp{name, {}};
    for (const auto& [wl_name, hours] : workloadEntries) {
        emp.workloads[wl_name] = hours;
    }
    node->employees.push_back(emp);
}

std::vector<Employee*> Database::getEmployees(const std::string& nodeName) const {
    std::vector<Employee*> result;

    std::function<void(TreeNode*)> traverse = [&](TreeNode* node) {
        if (node->name == nodeName) {
            for (auto& emp : node->employees) {
                result.push_back(&emp);
            }
        }
        for (const auto& child : node->children) {
            traverse(child.get());
        }
    };

    traverse(root.get());
    return result;
}

void Database::printTable(const std::vector<Employee*>& employees,
                         const std::vector<std::string>& columns) const {
    // Header
    for (const auto& col : columns) {
        std::cout << col << "\t";
    }
    std::cout << "\n---------------------------------\n";

    // Rows
    for (const auto& emp : employees) {
        for (const auto& col : columns) {
            if (col == "node_name") {
                std::cout << emp->name << "\t";
            } else {
                auto it = emp->workloads.find(col);
                if (it != emp->workloads.end()) {
                    std::cout << it->second << "\t";
                } else {
                    std::cout << "0\t";
                }
            }
        }
        std::cout << "\n";
    }
}

void Database::processCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string action;
    iss >> action;

    if (action == "add") {
        std::string type;
        iss >> type;

        if (type == "node") {
            std::string path;
            getline(iss, path);
            if (!path.empty() && path[0] == ' ') {
                path = path.substr(1);
            }
            addNode(path);
        } else if (type == "workload") {
            std::string path, name;
            iss >> path >> name;

            std::vector<std::pair<std::string, int>> workloads;
            std::string wl;
            while (iss >> wl) {
                size_t colon = wl.find(':');
                if (colon != std::string::npos) {
                    try {
                        std::string wl_name = wl.substr(0, colon);
                        int hours = std::stoi(wl.substr(colon + 1));
                        workloads.emplace_back(wl_name, hours);
                    } catch (const std::exception& e) {
                        std::cerr << "Invalid workload format: " << wl << "\n";
                    }
                }
            }
            addWorkloadToEmployee(path, name, workloads);
        }
    } else if (action == "query") {
        std::vector<std::string> columns;
        std::string targetNode;
        std::string token;
        bool inColumns = false;

        while (iss >> token) {
            if (token == "columns") {
                inColumns = true;
                continue;
            }
            if (token == "where") {
                inColumns = false;
                continue;
            }

            if (inColumns) {
                columns.push_back(token);
            } else {
                targetNode = token;
            }
        }

        if (columns.empty() || targetNode.empty()) {
            std::cerr << "Invalid query format\n";
            return;
        }

        auto employees = getEmployees(targetNode);
        if (employees.empty()) {
            std::cout << "No employees found for node: " << targetNode << "\n";
            return;
        }

        printTable(employees, columns);
    } else if (action == "load") {
        std::string filename;
        iss >> filename;
        if (!loadFromFile(filename)) {
            std::cerr << "Error loading from file." << std::endl;
        } else {
            std::cout << "Loaded from " << filename << std::endl;
        }
    } else if (action == "save") {
        std::string filename;
        iss >> filename;
        if (!saveToFile(filename)) {
            std::cerr << "Error saving to file." << std::endl;
        } else {
            std::cout << "Saved to " << filename << std::endl;
        }
    } else {
        std::cerr << "Unknown command: " << action << "\n";
    }
}

bool Database::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for loading: " << filename << std::endl;
        return false;
    }
    //TODO: Implement loading logic
    file.close();
    return true;
}

bool Database::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for saving: " << filename << std::endl;
        return false;
    }
    //TODO: Implement saving logic
    file.close();
    return true;
}