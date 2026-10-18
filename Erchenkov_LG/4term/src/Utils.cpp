#include "../include/Library.hpp"

namespace Library::Func {

std::string genKey(const std::vector<Classifier>& classifiers) {
    std::string key;
    for (const auto& c : classifiers) {
        key += c.name + ":" + c.class_value + "|";
    }
    return key;
}

bool isMatching(const Book& book, const Query::Condition& condition) {
    switch (condition.field_) {
        case Field::TITLE:
            return book.title_ == condition.request_;
        case Field::AUTHOR_NAME:
            return book.authorName_ == condition.request_;
        case Field::AUTHOR_SURNAME:
            return book.authorSurname_ == condition.request_;
        case Field::PUBLISHER:
            return book.info_.publisher_ == condition.request_;
        case Field::CLASSIFIER:
            for (const auto& cl : book.classifiers_) {
                if (cl.class_value == condition.request_) return true;
            }
            return false;
    }
    return false;
}

}
