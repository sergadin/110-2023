#include "../include/Library.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

namespace Library {

const std::string Core::DB_FILE = "library.txt";

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

void rebuild(std::unordered_map<std::string, std::vector<int>>& classifier_map, const std::vector<Book>& books) {
    classifier_map.clear();
    for (size_t i = 0; i < books.size(); ++i) {
        std::string key = Func::genKey(books[i].classifiers_);
        classifier_map[key].push_back(i);
    }
}

bool Core::add(const Book& book) {
    if (book.authorSurname_.empty() || book.title_.empty()) {
        throw Exception(1, "Invalid book data: surname and title cannot be empty");
    }
    books.push_back(book);
    std::sort(books.begin(), books.end());
    rebuild(classifier_map, books);
    std::cout << "Book added: " << book.title_ << " by \"" << book.authorSurname_ << "\"" << std::endl;
    return true;
}

bool Core::remove(size_t idx) {
    if (idx >= books.size()) {
        throw Exception(2, "Invalid index for removal");
    }
    std::cout << "Removing book at index " << idx << ": " << books[idx].title_ << std::endl;
    books.erase(books.begin() + idx);
    rebuild(classifier_map, books);
    return true;
}

bool Core::edit(size_t idx, const Book& book) {
    if (idx >= books.size()) {
        throw Exception(3, "Invalid index for editing");
    }
    if (book.authorSurname_.empty() || book.title_.empty()) {
        throw Exception(4, "Invalid book data: surname and title cannot be empty");
    }
    std::cout << "Editing book at index " << idx << " to: " << book.title_ << std::endl;
    books[idx] = book;
    std::sort(books.begin(), books.end());
    rebuild(classifier_map, books);
    return true;
}

bool Core::saveFile(const std::string& name) const {
    std::ofstream file(name);
    if (!file.is_open()) {
        throw Exception(5, "Failed to open file for writing: " + name);
    }
    
    for (const auto& book : books) {
        file << "Title: " << book.title_ << "\n";
        file << "AuthorName: " << book.authorName_ << "\n";
        file << "AuthorSurname: " << book.authorSurname_ << "\n";
        file << "Publisher: " << book.info_.publisher_ << "\n";
        file << "Pages: " << book.info_.pages_ << "\n";
        file << "Classifiers:\n";
        for (const auto& cl : book.classifiers_) {
            file << "  " << cl.name << ": " << cl.class_value << "\n";
        }
        file << "---\n";
    }
    
    file.close();
    std::cout << "Database saved to " << name << std::endl;
    return true;
}

bool Core::loadFile(const std::string& name) {
    std::ifstream file(name);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << name << " for reading" << std::endl;
        return false;
    }

    books.clear();
    classifier_map.clear();
    Book book;
    std::string line;
    bool in_classifiers = false;

    while (std::getline(file, line)) {
        if (line == "---") {
            if (!book.title_.empty() && !book.authorSurname_.empty()) {
                books.push_back(book);
            }
            book = Book();
            in_classifiers = false;
            continue;
        }

        if (line.find("Classifiers:") == 0) {
            in_classifiers = true;
            continue;
        }

        if (in_classifiers && !line.empty() && line[0] == ' ') {
            size_t pos = line.find(": ");
            if (pos != std::string::npos) {
                std::string name = trim(line.substr(2, pos - 2));
                std::string value = trim(line.substr(pos + 2));
                book.classifiers_.push_back(Classifier{name, value});
            }
            continue;
        }

        if (line.find("Title: ") == 0) {
            book.title_ = trim(line.substr(7));
        } else if (line.find("AuthorName: ") == 0) {
            book.authorName_ = trim(line.substr(12));
        } else if (line.find("AuthorSurname: ") == 0) {
            book.authorSurname_ = trim(line.substr(15));
        } else if (line.find("Publisher: ") == 0) {
            book.info_.publisher_ = trim(line.substr(11));
        } else if (line.find("Pages: ") == 0) {
            book.info_.pages_ = std::stoi(trim(line.substr(7)));
        }        
    }

    if (!book.title_.empty() && !book.authorSurname_.empty()) {
        books.push_back(book);
    }

    std::sort(books.begin(), books.end());
    rebuild(classifier_map, books);
    std::cout << "Database loaded from " << name << std::endl;
    return true;
}

std::vector<Book> Core::find(const Query& query) const {
    std::vector<Book> result;
    
    for (const auto& book : books) {
        bool matches = true;
        for (size_t i = 0; i < query.conditions.size(); ++i) {
            bool conditionResult = Func::isMatching(book, query.conditions[i]);
            
            if (i < query.operations.size()) {
                switch (query.operations[i]) {
                    case Op::AND:
                        matches = matches && conditionResult;
                        break;
                    case Op::OR:
                        matches = matches || conditionResult;
                        break;
                    case Op::NOT:
                        matches = matches && !conditionResult;
                        break;
                    default:
                        throw Exception(9, "Unsupported operation in query");
                }
            } else {
                matches = conditionResult;
            }
        }
        
        if (matches) {
            result.push_back(book);
        }
    }
    
    std::cout << "Query found " << result.size() << " books" << std::endl;
    return result;
}

std::vector<Book> Core::findByName(const Book& query) const {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (query.authorName_.empty() || book.authorName_ == query.authorName_) {
            if (query.authorSurname_.empty() || book.authorSurname_ == query.authorSurname_) {
                if (query.title_.empty() || book.title_ == query.title_) {
                    result.push_back(book);
                }
            }
        }
    }
    std::cout << "FindByName found " << result.size() << " books" << std::endl;
    return result;
}

std::vector<Book> Core::findByAuthor(const std::string& surname) const {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (book.authorSurname_ == surname) {
            result.push_back(book);
        }
    }
    return result;
}


std::vector<Book> Core::findByClassifier(const std::string& name, const std::string& value) const {
    std::vector<Book> result;
    std::cout << "Searching for classifier value: \"" << value << "\"" << std::endl;
    for (const auto& book : books) {
        for (const auto& cl : book.classifiers_) {
            if (cl.class_value == value) {
                result.push_back(book);
                break; 
            }
        }
    }
    std::cout << "FindByClassifier found " << result.size() << " books for classifier value \"" << value << "\"" << std::endl;
    return result;
}

std::string Core::processCommand(const std::string& command) {
    std::stringstream ss(command);
    std::string action;
    ss >> action;

    if (action == "ADD") {
        std::string first_word;
        ss >> first_word;
        ss.clear();
        ss.seekg(0);
        ss >> action;

        if (first_word[0] == '"') {
            Book book;
            std::string title, authorName, authorSurname, publisher, classifiers_str;
            int pages = 0, year = 0;

            try {
                std::getline(ss, title, '"'); 
                std::getline(ss, title, '"');
                std::getline(ss, authorName, '"');
                std::getline(ss, authorName, '"');
                std::getline(ss, authorSurname, '"');
                std::getline(ss, authorSurname, '"');
                std::getline(ss, publisher, '"');
                std::getline(ss, publisher, '"');
                ss >> pages;
                ss >> year;
                std::getline(ss, classifiers_str, '"');
                std::getline(ss, classifiers_str, '"');
            } catch (...) {
                throw Exception(10, "Invalid ADD command format");
            }

            book.title_ = trim(title);
            book.authorName_ = trim(authorName);
            book.authorSurname_ = trim(authorSurname);
            book.info_.publisher_ = trim(publisher);
            book.info_.pages_ = pages;

            if (!classifiers_str.empty()) {
                std::stringstream cls_stream(classifiers_str);
                std::string classifier;
                while (std::getline(cls_stream, classifier, ',')) {
                    size_t pos = classifier.find(':');
                    if (pos != std::string::npos) {
                        std::string name = trim(classifier.substr(0, pos));
                        std::string value = trim(classifier.substr(pos + 1));
                        book.classifiers_.push_back(Classifier{name, value});
                        std::cout << "Parsed Classifier: \"" << name << ": " << value << "\"" << std::endl;
                    }
                }
            }

            if (book.title_.empty() || book.authorSurname_.empty()) {
                throw Exception(10, "Title or AuthorSurname cannot be empty");
            }

            if (add(book)) {
                return "Book added successfully";
            }
            throw Exception(10, "Failed to add book");
        } else {
            Book book;
            std::string temp;
            std::stringstream bookStream;
            std::getline(ss, temp);
            bookStream << temp << "\n";
            while (std::getline(ss, temp)) {
                bookStream << temp << "\n";
            }

            bool in_classifiers = false;
            while (std::getline(bookStream, temp)) {
                if (temp.find("Title: ") == 0) {
                    book.title_ = trim(temp.substr(7));
                    std::cout << "Parsed Title: \"" << book.title_ << "\"" << std::endl;
                } else if (temp.find("AuthorName: ") == 0) {
                    book.authorName_ = trim(temp.substr(12));
                    std::cout << "Parsed AuthorName: \"" << book.authorName_ << "\"" << std::endl;
                } else if (temp.find("AuthorSurname: ") == 0) {
                    book.authorSurname_ = trim(temp.substr(15));
                    std::cout << "Parsed AuthorSurname: \"" << book.authorSurname_ << "\"" << std::endl;
                } else if (temp.find("Publisher: ") == 0) {
                    book.info_.publisher_ = trim(temp.substr(11));
                    std::cout << "Parsed Publisher: \"" << book.info_.publisher_ << "\"" << std::endl;
                } else if (temp.find("Pages: ") == 0) {
                    book.info_.pages_ = std::stoi(trim(temp.substr(7)));
                    std::cout << "Parsed Pages: " << book.info_.pages_ << std::endl;
                } else if (temp.find("Classifiers:") == 0) {
                    in_classifiers = true;
                    std::cout << "Entering Classifiers section" << std::endl;
                } else if (in_classifiers && !temp.empty() && temp[0] == ' ') {
                    size_t pos = temp.find(": ");
                    if (pos != std::string::npos && temp[0] == ' ') {
                        std::string name = trim(temp.substr(2, pos - 2));
                        std::string value = trim(temp.substr(pos + 2));
                        book.classifiers_.push_back(Classifier{name, value});
                        std::cout << "Parsed Classifier: \"" << name << ": " << value << "\"" << std::endl;
                    }
                }
            }

            if (add(book)) {
                return "Book added successfully";
            }
            throw Exception(10, "Failed to add book");
        }
    } else if (action == "SAVE") {
        std::string filename;
        ss >> filename;
        if (saveFile(filename)) {
            return "Database saved successfully";
        }
        throw Exception(12, "Failed to save database");
    } else if (action == "LOAD") {
        std::string filename;
        ss >> filename;
        if (loadFile(filename)) {
            return "Database loaded successfully";
        }
        throw Exception(13, "Failed to load database");
    } else if (action == "FIND_BY_AUTHOR") {
        std::string author;
        std::getline(ss, author);
        author = trim(author);
        if (author.empty()) {
            throw Exception(14, "Author surname cannot be empty");
        }
        auto books = findByAuthor(author);
        if (books.empty()) {
            return "No books found for author: " + author;
        }
        std::stringstream result;
        result << "Found " << books.size() << " books for author: " << author << "\n";
        for (size_t i = 0; i < books.size(); ++i) {
            result << i << ": " << books[i].title_ << " by " << books[i].authorSurname_ << ", " << books[i].authorName_ 
                   << " (Publisher: " << books[i].info_.publisher_ << ", Pages: " << books[i].info_.pages_ << ")\n";
        }
        return result.str();
    } else if (action == "FIND_BY_TITLE") {
        std::string title;
        if (ss.peek() == '"') {
            ss.get();
            std::getline(ss, title, '"');
        } else {
            std::getline(ss, title);
            title = trim(title);
        }
        if (title.empty()) {
            throw Exception(15, "Title cannot be empty");
        }
        Book query;
        query.title_ = title;
        auto books = findByName(query);
        if (books.empty()) {
            return "No books found with title: " + title;
        }
        std::stringstream result;
        result << "Found " << books.size() << " books with title: " << title << "\n";
        for (size_t i = 0; i < books.size(); ++i) {
            result << i << ": " << books[i].title_ << " by " << books[i].authorSurname_ << ", " << books[i].authorName_ 
                   << " (Publisher: " << books[i].info_.publisher_ << ", Pages: " << books[i].info_.pages_ << ")\n";
        }
        return result.str();
    } else if (action == "FIND_BY_CLASSIFIER") {
        std::string code;
        std::getline(ss, code);
        code = trim(code);
        if (code.empty()) {
            throw Exception(16, "Classifier code cannot be empty");
        }
        auto books = findByClassifier("", code); 
        if (books.empty()) {
            return "No books found for classifier code: " + code;
        }
        std::stringstream result;
        result << "Found " << books.size() << " books for classifier code: " << code << "\n";
        for (size_t i = 0; i < books.size(); ++i) {
            result << i << ": " << books[i].title_ << " by " << books[i].authorSurname_ << ", " << books[i].authorName_ 
                   << " (Publisher: " << books[i].info_.publisher_ << ", Pages: " << books[i].info_.pages_ << ")\n";
        }
        return result.str();
    } else if (action == "EXIT") {
        return "EXIT";
    }
    return "Unknown command";
}

}
