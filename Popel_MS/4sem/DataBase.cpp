#include "Schedule.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <list>

static Query* parseSelectingQuery(const std::string& query);
static Query* parseAssigningQuery(const std::string& query);
static Query* parseUpdateQuery(const std::string& query);
static Query* parseInsertQuery(const std::string& query);
static Query* parsePrintQuery(const std::string& query);
static Query* parseDeleteQuery(const std::string& query);
void registerParsers();

static Query* parseSelectingQuery(const std::string& query) {
    SelectingQuery* q = new SelectingQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parseAssigningQuery(const std::string& query) {
    AssigningQuery* q = new AssigningQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parseUpdateQuery(const std::string& query) {
    UpdateQuery* q = new UpdateQuery(query);
    try {
        q->UpdateQuery::parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parseInsertQuery(const std::string& query) {
    InsertQuery* q = new InsertQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parsePrintQuery(const std::string& query) {
    PrintQuery* q = new PrintQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parseDeleteQuery(const std::string& query) {
    DeleteQuery* q = new DeleteQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}


void registerParsers() {
    Query::register_parser(parseSelectingQuery);
    Query::register_parser(parseUpdateQuery);
    Query::register_parser(parseInsertQuery);
    Query::register_parser(parsePrintQuery);
    Query::register_parser(parseDeleteQuery);
    Query::register_parser(parseAssigningQuery);
}

DataBase::DataBase(FILE* fin) : schedule_(new Schedule()), clientSessions() {}

DataBase::~DataBase() {
    delete schedule_;
    for (auto& client : clientSessions) {
        for (Entry* entry : client.second.previousSelection) {
            delete entry;
        }
        client.second.previousSelection.clear();
    }
    clientSessions.clear();
}

result DataBase::startQuery(int clientSocket, std::string& query) {
    result res;
        registerParsers();
    try {
        std::unique_ptr<Query> q(Query::do_parse(query));
        if (!q) {
            res.addError(Exception(1, "Invalid query"));
            return res;
        }
        ComType command = q->getCommand();
        if (command == SELECT || command == RESELECT)
        {
            SelectingQuery *sq = dynamic_cast<SelectingQuery *>(q.get());
            if (sq)
            {
                std::vector<Entry *> selectedEntries;
                if (command == SELECT)
                { 
                    for (Entry *entry : clientSessions[clientSocket].previousSelection)
                    {
                        delete entry;
                    }
                    clientSessions[clientSocket].previousSelection.clear();

                    selectedEntries = schedule_->select(sq->getConditions());
                }
                else
                {
                    if (clientSessions[clientSocket].previousSelection.empty())
                    {
                        res.addError(Exception(20, "No previous selection to reselect from."));
                        return res;
                    }
                    selectedEntries = schedule_->reselect(clientSessions[clientSocket].previousSelection, sq->getConditions());
                }

                for (Entry *entry : selectedEntries)
                {
                    Entry *newEntry = new Entry(entry->getDay(), entry->getMonth(), entry->getLesson(), entry->getRoom(), entry->getSubjectName(), entry->getTeacher(), entry->getGroup());
                    clientSessions[clientSocket].previousSelection.push_back(newEntry);
                }

                std::stringstream ss;
                if (clientSessions[clientSocket].previousSelection.empty()) {
                    ss << "Нет подходящих записей" << std::endl;
                } else {
                    for (Entry *entry : clientSessions[clientSocket].previousSelection)
                    {
                       ss << "Date: " << entry->getDay() << "." << entry->getMonth()
                           << ", Lesson: " << entry->getLesson()
                           << ", Room: " << entry->getRoom()
                           << ", Subject: " << entry->getSubjectName()
                           << ", Teacher: " << entry->getTeacher()
                           << ", Group: " << entry->getGroup() << std::endl;
                    }
                }
                res.addMessage(ss.str());
                std::cout << "Server response to client " << clientSocket << ":\n"
                          << ss.str() << std::endl;
                          
                          schedule_->saveToFile("scheduleout.txt");
            }
        }
        else if (command == PRINT) {
            PrintQuery* pq = dynamic_cast<PrintQuery*>(q.get());
            if (pq) {
                if (clientSessions[clientSocket].previousSelection.empty()) {
                    res.addError(Exception(21, "No previous selection to print."));
                    return res;
                }

                std::vector<Entry*> entriesToPrint = clientSessions[clientSocket].previousSelection;

                // Sort entries if sort fields are specified
                if (!pq->getSortFields().empty()) {
                    for (const auto& sortField : pq->getSortFields()) {
                        std::sort(entriesToPrint.begin(), entriesToPrint.end(), [&](Entry* a, Entry* b) {
                            switch (sortField.first) {
                                case DAY:
                                    return sortField.second == ASC ? a->getDay() < b->getDay() : a->getDay() > b->getDay();
                                case MONTH:
                                    return sortField.second == ASC ? a->getMonth() < b->getMonth() : a->getMonth() > b->getMonth();
                                case LESSON_NUM:
                                    return sortField.second == ASC ? a->getLesson() < b->getLesson() : a->getLesson() > b->getLesson();
                                case ROOM:
                                    return sortField.second == ASC ? a->getRoom() < b->getRoom() : a->getRoom() > b->getRoom();
                                case SUBJNAME:
                                    return sortField.second == ASC ? strcmp(a->getSubjectName(), b->getSubjectName()) < 0 : strcmp(a->getSubjectName(), b->getSubjectName()) > 0;
                                case TEACHERNAME:
                                    return sortField.second == ASC ? a->getTeacher() < b->getTeacher() : a->getTeacher() > b->getTeacher();
                                case GROUP:
                                    return sortField.second == ASC ? a->getGroup() < b->getGroup() : a->getGroup() > b->getGroup();
                                default:
                                    return false;
                            }
                        });
                    }
                }

                std::stringstream ss;
                for (Entry* entry : entriesToPrint) {
                    Entry filteredEntry = *entry;
                    
                    if (!pq->getFields().empty()) {
                for (Field field : pq->getFields()) {
                    switch (field) {
                        case DAY:
                            ss << "Day: " << filteredEntry.getDay() << " ";
                            break;
                        case MONTH:
                            ss << "Month: " << filteredEntry.getMonth() << " ";
                            break;
                        case LESSON_NUM:
                            ss << "Lesson: " << filteredEntry.getLesson() << " ";
                            break;
                        case ROOM:
                            ss << "Room: " << filteredEntry.getRoom() << " ";
                            break;
                        case SUBJNAME:
                            ss << "Subject: " << filteredEntry.getSubjectName() << " ";
                            break;
                        case TEACHERNAME:
                            ss << "Teacher: " << filteredEntry.getTeacher() << " ";
                            break;
                        case GROUP:
                            ss << "Group: " << filteredEntry.getGroup() << " ";
                            break;
                        default:
                            break;
                    }
                }
            } else {
                // Если поля не указаны, выводим все поля
                ss << "Date: " << filteredEntry.getDay() << "." << filteredEntry.getMonth()
                   << ", Lesson: " << filteredEntry.getLesson()
                   << ", Room: " << filteredEntry.getRoom()
                   << ", Subject: " << filteredEntry.getSubjectName()
                   << ", Teacher: " << filteredEntry.getTeacher()
                   << ", Group: " << filteredEntry.getGroup() << std::endl;
            }
            ss << std::endl;
                }
                res.addMessage(ss.str());
                std::cout << "Server response to client " << clientSocket << ":\n"
                          << ss.str() << std::endl;
                          
                          schedule_->saveToFile("scheduleout.txt");
            }
        }else if (command == INSERT) {
            AssigningQuery* iq = dynamic_cast<AssigningQuery*>(q.get());
            if (iq) {
                int day = 0, month = 0, lesson = 0, room = 0, group = 0;
                char subject_name[128] = { 0 };
                std::string teacher = "";

                const std::vector<std::pair<Field, Value>>& values = iq->getValues();
                for (const auto& pair : values) {
                    Field field = pair.first;
                    Value value = pair.second;

                    switch (field) {
                        case DAY:
                            day = std::get<int>(value);
                            break;
                        case MONTH:
                            month = std::get<int>(value);
                            break;
                        case LESSON_NUM:
                            lesson = std::get<int>(value);
                            break;
                        case ROOM:
                            room = std::get<int>(value);
                            break;
                        case SUBJNAME: {
                            std::string subjName = std::get<std::string>(value);
                            size_t len = subjName.length();
                            len = std::min(len, sizeof(subject_name) - 1);
                            std::strncpy(subject_name, subjName.c_str(), len);
                            subject_name[len] = '\0';
                            break;
                        }
                        case TEACHERNAME: {
                            teacher = std::get<std::string>(value);
                            break;
                        }
                        case GROUP:
                            group = std::get<int>(value);
                            break;
                        default:
                            break;
                    }
                }

                Entry* newEntry = new Entry(day, month, lesson, room, subject_name, teacher, group);
                schedule_->addEntry(newEntry);
                res.addMessage("Entry inserted successfully.");
                
                schedule_->saveToFile("scheduleout.txt");
            }
        } else if (command == UPDATE) {
            UpdateQuery* uq = dynamic_cast<UpdateQuery*>(q.get());
            if (uq) {
                const std::vector<Cond>& conditions = uq->getConditions();
                const std::vector<std::pair<Field, Value>>& values = uq->getValues();
                std::vector<Entry*> entriesToUpdate = schedule_->select(conditions);
                for (Entry* entry : entriesToUpdate) {
                    for (const auto& pair : values) {
                        Field field = pair.first;
                        Value value = pair.second;

                        switch (field) {
                            case DAY:
                                entry->setDay(std::get<int>(value));
                                break;
                            case MONTH:
                                entry->setMonth(std::get<int>(value));
                                break;
                            case LESSON_NUM:
                                entry->setLesson(std::get<int>(value));
                                break;
                            case ROOM:
                                entry->setRoom(std::get<int>(value));
                                break;
                            case SUBJNAME: {
                                std::string subjName = std::get<std::string>(value);
                                entry->setSubjectName(subjName.c_str());
                                break;
                            }
                            case TEACHERNAME: {
                                std::string teacher = entry->getTeacher();
                                teacher = std::get<std::string>(value);
                                entry->setTeacher(teacher);
                                break;
                            }
                            case GROUP:
                                entry->setGroup(std::get<int>(value));
                                break;
                            default:
                                break;
                        }
                    }
                }

                res.addMessage("Entries updated successfully.");
                
                schedule_->saveToFile("scheduleout.txt");
            }
        } else if (command == DELETE) {
            DeleteQuery* dq = dynamic_cast<DeleteQuery*>(q.get());
            if (dq) {
                const std::vector<Cond>& conditions = dq->getConditions();
                if(conditions.empty()){
                }
                std::vector<Entry*> entriesToDelete = schedule_->select(conditions);

                if (entriesToDelete.empty()) {
                    res.addMessage("Nothing was deleted.");
                } else {

                    for (Entry* entry : entriesToDelete) {
                        schedule_->deleteEntry(entry);
                    }
                    std::stringstream ss;
                    ss << entriesToDelete.size() << " entries deleted successfully.";
                    res.addMessage(ss.str());
                }
                clientSessions[clientSocket].previousSelection.clear();
                schedule_->saveToFile("scheduleout.txt");
            }
        }
    } catch (const Exception& err) {
        res.addError(err);
    } catch (const std::bad_variant_access&) {
        res.addError(Exception(1, "Unknown exception occurred bad_var"));
    } catch (...) {
        res.addError(Exception(1, "Unknown exception occurred"));
    }


    return res;
}
