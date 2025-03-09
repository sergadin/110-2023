#include "Schedule.h"

/*void result::addEntry(const Entry& ent) {
    entry.push_back(ent);
}

void result::addMessage(const std::string& mes) {
    message = mes;
}

void result::addStatistic(const std::string& key, const Value& value) {
    statistics[key] = value;
}

void result::addError(const Exception& err) {
    error = err;
    
}*/

Cond::Cond(Field fld, BinOp optn, Value val) : field_(fld), operation_(optn), value_(val) {}

Query::Query(const std::string &query) : query_(query) {
    size_t pos = 0;
    std::string token;
    while ((pos = query_.find(' ')) != std::string::npos) {
        token = query_.substr(0, pos);
        if (token == "select") {
            command_ = SELECT;
        } else if (token == "reselect") {
            command_ = RESELECT;
        } else if (token == "insert") {
            command_ = INSERT;
        } else if (token == "update") {
            command_ = UPDATE;
        } else if (token == "delete") {
            command_ = DELETE;
        } else if (token == "print") {
            command_ = PRINT;
        }
        query_.erase(0, pos + 1);
    }
    if (!query_.empty()) {
        token = query_;
        if (token == "select") {
            command_ = SELECT;
        } else if (token == "reselect") {
            command_ = RESELECT;
        } else if (token == "insert") {
            command_ = INSERT;
        } else if (token == "update") {
            command_ = UPDATE;
        } else if (token == "delete") {
            command_ = DELETE;
        } else if (token == "print") {
            command_ = PRINT;
        }
    }
}

SelectingQuery::SelectingQuery(const std::string &query) : Query(query) {}

void SelectingQuery::parse() {
    parseCond();
}

void SelectingQuery::parseCond() {
    size_t pos = 0;
    std::string token;
    while ((pos = query_.find(' ')) != std::string::npos) {
        token = query_.substr(0, pos);
        if (token == "select") {
            command_ = SELECT;
        } else if (token == "end") {
            break;
        } else {
            parseCondTriple(token);
        }
        query_.erase(0, pos + 1);
    }
    if (!query_.empty()) {
        token = query_;
        if (token == "end") {
            return;
        } else {
            parseCondTriple(token);
        }
    }
}

void SelectingQuery::parseTriple(const std::string &frag) {
    parseCondTriple(frag);
}

void SelectingQuery::parseCondTriple(const std::string &frag) {
    size_t pos = frag.find('=');
    if (pos != std::string::npos) {
        std::string field = frag.substr(0, pos);
        std::string value = frag.substr(pos + 1);
        if (field == "teacher") {
            condition_.emplace_back(TEACHER, EQ, value);
        } else if (field == "group") {
            size_t rangePos = value.find('-');
            size_t comma = value.find(',');
            if (rangePos != std::string::npos) {
                int start = std::stoi(value.substr(0, rangePos));
                int end = std::stoi(value.substr(rangePos + 1));
                for (int i = start; i <= end; ++i) {
                    condition_.emplace_back(GROUP, EQ, i);
                }
            } else if (comma != std::string::npos) {
                size_t start = 0;
                while ((comma = value.find(',', start)) != std::string::npos) {
                    condition_.emplace_back(GROUP, EQ, std::stoi(value.substr(start, comma - start)));
                    start = comma + 1;
                }
                condition_.emplace_back(GROUP, EQ, std::stoi(value.substr(start)));
            } else {
                condition_.emplace_back(GROUP, EQ, std::stoi(value));
            }
        } else if (field == "room") {
            size_t rangePos = value.find('-');
            size_t comma = value.find(',');
            if (rangePos != std::string::npos) {
                int start = std::stoi(value.substr(0, rangePos));
                int end = std::stoi(value.substr(rangePos + 1));
                for (int i = start; i <= end; ++i) {
                    condition_.emplace_back(ROOM, EQ, i);
                }
            } else if (comma != std::string::npos) {
                size_t start = 0;
                while ((comma = value.find(',', start)) != std::string::npos) {
                    condition_.emplace_back(ROOM, EQ, std::stoi(value.substr(start, comma - start)));
                    start = comma + 1;
                }
                condition_.emplace_back(ROOM, EQ, std::stoi(value.substr(start)));
            } else {
                condition_.emplace_back(ROOM, EQ, std::stoi(value));
            }
        } else if (field == "time") {
            size_t rangePos = value.find('-');
            size_t comma = value.find(',');
            if (rangePos != std::string::npos) {
                TimeHM time;
                sscanf(value.c_str(), "%d:%d-%d:%d", &time.startHour, &time.startMinute, &time.endHour, &time.endMinute);
                condition_.emplace_back(TIME, EQ, time);
            } else if (comma != std::string::npos) {
                size_t start = 0;
                while ((comma = value.find(',', start)) != std::string::npos) {
                    TimeHM time;
                    sscanf(value.substr(start, comma - start).c_str(), "%d:%d-%d:%d", &time.startHour, &time.startMinute, &time.endHour, &time.endMinute);
                    condition_.emplace_back(TIME, EQ, time);
                    start = comma + 1;
                }
                TimeHM time;
                sscanf(value.substr(start).c_str(), "%d:%d-%d:%d", &time.startHour, &time.startMinute, &time.endHour, &time.endMinute);
                condition_.emplace_back(TIME, EQ, time);
            } else {
                TimeHM time;
                sscanf(value.c_str(), "%d:%d-%d:%d", &time.startHour, &time.startMinute, &time.endHour, &time.endMinute);
                condition_.emplace_back(TIME, EQ, time);
            }
        } else if (field == "subject") {
            size_t comma = value.find(',');
            if (comma != std::string::npos) {
                size_t start = 0;
                while ((comma = value.find(',', start)) != std::string::npos) {
                    condition_.emplace_back(SUBJNAME, EQ, value.substr(start, comma - start));
                    start = comma + 1;
                }
                condition_.emplace_back(SUBJNAME, EQ, value.substr(start));
            } else {
                condition_.emplace_back(SUBJNAME, EQ, value);
            }
        } else {
            throw Exception(3, "Unknown field: " + field);
        }
    } else {
        throw Exception(3, "Invalid condition format: " + frag);
    }
}

AssigningQuery::AssigningQuery(const std::string &query): Query(query) {}

void AssigningQuery::parse();

void AssigningQuery::parseKeyVal();

void AssigningQuery::parseTriple(const std::string &frag);

void AssigningQuery::parseKeyValTriple(const std::string &frag);

UpdateQuery::UpdateQuery(const std::string &query) : SelectingQuery(query), AssigningQuery(query) {}

void UpdateQuery::parseCond();

void UpdateQuery::parseKeyVal();

void UpdateQuery::parseCondTriple(const std::string &frag);

void UpdateQuery::parseKeyValTriple(const std::string &frag);

PrintQuery::PrintQuery(const std::string &query) : Query(query) {}

void PrintQuery::parse();

void PrintQuery::parseTriple(const std::string &frag);

Schedule::Schedule() {}

Schedule::Schedule(FILE* fin) {
    if (fin) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), fin)) {
            TimeHM time;
            int room;
            char subject_name[128];
            FullName teacher;
            int group;

            sscanf(buffer, "%d:%d-%d:%d %d %s %s %s %s %d",
                   &time.startHour, &time.startMinute, &time.endHour, &time.endMinute, &room, subject_name,
                   teacher.surname, teacher.name, teacher.patronymic, &group);

            Entry* entry = new Entry(time, room, subject_name, teacher, group);
            addEntry(entry);
        }
    }else {
        throw Exception(5, "Unable to open file");
    }
}

Schedule::~Schedule() {
    for (auto entry : schedule_) {
        delete entry;
    }
}

void Schedule::addEntry(Entry* entry) {
    for (const auto& exstEntry : schedule_) {
        /*if (exstEntry->room == entry->room && checkTimeMatch(exstEntry->time, entry->time)) {
            throw Exception(2, "Time match in the same room");//Мб еще что-то аналогичное для схожих пересечений
        }*/
    }
    schedule_.push_back(entry);
}

void Schedule::deleteEntry(const TimeHM& time, int room) {
    ...
}

void Schedule::updateEntry(const TimeHM& time, int room, Entry* newEntry) {
    for (auto& entry : schedule_) {
        if (entry->time.startHour == time.startHour && entry->time.startMinute == time.startMinute &&
            entry->time.endHour == time.endHour && entry->time.endMinute == time.endMinute && entry->room == room) {
            *entry = *newEntry;
            break;
        }
    }
}

bool matchCond(const Entry& entry, const Cond& cond) {
    switch (cond.getField()) {
        case TIME: {
            TimeHM time = std::get<TimeHM>(cond.getVal());
            return entry.time.startHour == time.startHour && entry.time.startMinute == time.startMinute && entry.time.endHour == time.endHour && entry.time.endMinute == time.endMinute;
        }
        case ROOM: {
            int room = std::get<int>(cond.getVal());
            return entry.room == room;
        }
        case SUBJNAME: {
            std::string subject = std::get<std::string>(cond.getVal());
            return strcmp(entry.subject_name, subject.c_str()) == 0;
        }
        case TEACHER: {
            FullName teacher = std::get<FullName>(cond.getVal());
            return strcmp(entry.teacher.surname, teacher.surname) == 0 && strcmp(entry.teacher.name, teacher.name) == 0 && strcmp(entry.teacher.patronymic, teacher.patronymic) == 0;
        }
        case GROUP: {
            int group = std::get<int>(cond.getVal());
            return entry.group == group;
        }
        default:
            return false;
    }
}

std::vector<Entry*> Schedule::select(const std::vector<Cond>& crit) {
    std::vector<Entry*> selected;
    for (const auto& entry : schedule_) {
        bool match = true;
        for (const auto& cond : crit) {
            if (!matchCond(*entry, cond)) {
                match = false;
                break;
            }
        }
        if (match) {
            selected.push_back(entry);
        }
    }
    return selected;
}

std::vector<Entry*> Schedule::reselect(const std::vector<Entry*>& selected, const std::vector<Cond>& crit) {
    std::vector<Entry*> reselect;
    for (const auto& entry : selected) {
        bool match = true;
        for (const auto& cond : crit) {
            if (!matchCond(*entry, cond)) {
                match = false;
                break;
            }
        }
        if (match) {
            reselect.push_back(entry);
        }
    }
    return reselect;
}

void Schedule::print(const std::vector<Entry*>& entries/*, const std::vector<Field>& fields*/) {
    for (const auto& entry : entries) {
        std::cout << "Time: " << entry->time.startHour << ":" << entry->time.startMinute << "-" << entry->time.endHour << ":" << entry->time.endMinute
                  << ", Room: " << entry->room << ", Subject: " << entry->subject_name << ", Teacher: " << entry->teacher.surname << " "
                  << entry->teacher.name << " " << entry->teacher.patronymic << ", Group: " << entry->group << std::endl;
    }
}

void Schedule::saveToFile(FILE* fout) {
    for (const auto& entry : schedule_) {
        fprintf(fout, "%d:%d-%d:%d %d %s %s %s %s %d\n", entry->time.startHour, entry->time.startMinute, entry->time.endHour, entry->time.endMinute, entry->room,
                entry->subject_name, entry->teacher.surname, entry->teacher.name, entry->teacher.patronymic, entry->group);
    }
}


/*bool Schedule::checkTimeMatch(const TimeHM& time1, const TimeHM& time2) {
    return !(time1.endHour < time2.startHour || time1.endHour == time2.startHour && time1.endMinute <= time2.startMinute ||
             time2.endHour < time1.startHour || time2.endHour == time1.startHour && time2.endMinute <= time1.startMinute);
}*/

DataBase::DataBase(FILE* fin) {
    schedule_ = new Schedule(fin);
}

DataBase::~DataBase() {
    delete schedule_;
}

result DataBase::startQuery(std::string& query) {
    result res;
    Query* q = nullptr;

    try {
        if (query.find("select") != std::string::npos) {
            q = new SelectingQuery(query);
        } else if (query.find("insert") != std::string::npos) {
            q = new AssigningQuery(query);
        } else if (query.find("update") != std::string::npos) {
            q = new UpdateQuery(query);
        } else if (query.find("delete") != std::string::npos) {
            q = new SelectingQuery(query);
        } else if (query.find("print") != std::string::npos) {
            q = new PrintQuery(query);
        }

        if (q) {
            q->parse();
            switch (q->getCommand()) {
                case SELECT: {
                    SelectingQuery* sq = static_cast<SelectingQuery*>(q);
                    std::vector<Entry*> selected = schedule_->select(sq->getConditions());
                    for (const auto& entry : selected) {
                        res.addEntry(*entry);
                    }
                    //res.addStatistic("record_count", selected.size());
                    break;
                }
                case INSERT: {
                    ...
                }
                case UPDATE: {
                    ...
                }
                case DELETE: {
                    ...
                }
                case PRINT: {
                    ...
                }
                default:
                    res.addError(Exception(1, "Unknown command"));
                    break;
            }
            delete q;
        } else {
            res.addError(Exception(1, "Unknown command"));
        }
    } catch (const Exception& e) {
        res.addError(e);
    }

    return res;
}


