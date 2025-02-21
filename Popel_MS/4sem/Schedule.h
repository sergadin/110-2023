
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
//using namespace std;

struct TimeHM {
  int hour;
  int minute;
};

struct FullName {
  char surname[64];
  char name[32];
  char patrunymic[64];
};

typedef enum {SELECT, RESELECT, INSERT, UPDATE, DELETE, PRINT} ComType;
typedef enum {TIME, ROOM, SUBJNAME, TEACHER, GROUP} Field;
typedef enum {LT, GT, EQ, LT_EQ, GT_EQ, NEQ} BinOp;

class Query{
  private:
    ComType command_;
    std::vector<Cond> condition_;
    std::vector<Field> fields_;
  public:
    Query(const std::string &query);
};

class Cond{
  private: 
    Field field_;
    BinOp operation_;
    std::string value_;
  public:
    Cond(Field fld, BinOp optn, std::string val);
};



class Subject{
  private: 
    TimeHM time_;
    int room_;
    char subject_name_[128];
    FullName teacher_;
    int group_;
    
  public:
    Subject(TimeHM time, int room, char subjName, FullName teacher, int group): time_(time), room_(room), teacher_(teacher), group_(group){
      strncpy(subject_name_, subjName, sizeof(subject_name_));
    }
};

class Schedule{
  private: 
    std::vector<Subject*> schedule_;
    std::map<FullName, std::vector<int>> teacherInd;
    std::map<int, std::vector<int>> groupInd;
    std::map<int, std::vector<int>> roomInd;
    std::map<TimeHM, std::vector<int>> timeInd;
    std::map<char[128], std::vector<int>> subjectInd;
    
    void buildInd();
    std::vector<int> getCritInd(const std::string& crit);
    std::vector<int> intersectInd(const std::vector<int>& ind1, const std::vector<int>& ind2);
  public:
    Schedule();
    Schedule(FILE* fin);
    ~Schedule();
    void addEntry(Subject* entry);
    void deleteEntry(const TimeHM& time, int room);
    void updateEntry(const TimeHM& time, int room, Subject* newEntry);
    std::vector<Subject*> select(const std::vector<Cond>& crit);
    std::vector<Subject*> reselect(const std::vector<Subject*>& selected, const std::vector<Cond>& crit);
    void print(const std::vector<Subject*>& entries/*, const std::vector<Field>& fields*/);
    void saveToFile(FILE* fout);
    
}

class DataBase{
  private:
    Schedule *schedule_;
    bool startQuery(Query query);
  public:
    DataBase(FILE* fin);
    ~DataBase();
};

class Exception {
  private:
    int code_;
    std::string mess_;
  public:
    Exception(int c, std::string m){
      code_ = c;
      mess_ = m;
    }
};
