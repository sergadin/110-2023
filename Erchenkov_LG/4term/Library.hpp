#include <string>
#include <vector>
#include <unordered_map>


namespace Library {

using std::string;
using std::vector;

/* publication data structure  */
struct Publication {
    string publisher_;
    int pages_;

    Publication(const string& publisher = "", int pages = 0) : publisher_(publisher), pages_(pages) {}

};

/* classifer structure */
struct Classifier {
    string name;
    string class_value;
};


/* book structure */
struct Book {
    string title_;
    string authorName_;
    string authorSurname_;
    Publication info_;
    vector<Classifier> classifiers_;  // provide hierarchy of classifiers

    Book(
        const string& title = "", 
        const string& authorName = "", 
        const string& authorSurname = "", 
        const Publication& info = Publication()
        ) : title_(title), authorName_(authorName), authorSurname_(authorSurname), info_(info) {}

    // surname sort
    bool operator<(const Book& other) const {
        return authorSurname_ < other.authorSurname_;
    }
};

/* basic operation */
enum class Op {AND, OR, NOT, LT, GT, EQ, LT_EQ, GT_EQ, NEQ};
enum class Field {TITLE, AUTHOR_NAME, AUTHOR_SURNAME, PUBLISHER, CLASSIFIER};


/* allow us to keep query data */
struct Query {
   Query() = default;
   virtual ~Query() = default; 

   struct Condition {
       Field field_;
       string request_;

       Condition(Field field = Field::TITLE, const string& request = "") : field_(field), request_(request) {}
   };

   vector<Op> operations;
   vector<Condition> conditions;
   vector<Query> Queries;

};

/* library core */
class Entry {
private:
    vector<Book> books;
    std::unordered_map<string, vector<int>> classifier_map; // stores classifier indices

public:
    Entry() = default;
    virtual ~Entry() = default;

    bool add(const Book& book);
    bool remove(size_t idx);
    bool edit(const Book& book);
    bool saveFile(const string& name) const; 
    bool loadFile(const string& name) const;

    vector<Book> findByName(const Book& query) const;
    vector<Book> findByAuthor(const string& name) const;
    vector<Book> findByClassifier(const string& name) const;

};

namespace Func {
    std::string genKey(const std::vector<Classifier>& classifiers); // generate key for classifier index
    bool isMatching(const Book& book, const Query::Condition& conditions); // verifies that user request is correct
}

}

/* exception class 
 * provides error handling
 * */

class Exception {
    private:
        int code_;
        std::string msg_;
    public:
        Exception(int code, const std::string& msg) : code_(code), msg_(msg) {}
        int getCode() const { return code_; }
        std::string getMsg() const { return msg_; }
};

