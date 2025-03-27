#include "Schedule.h"
#include <iostream>
#include <sstream>
#include <regex>

DataBase::DataBase(FILE* fin) : schedule_(new Schedule()), previousSelection() {}

DataBase::~DataBase() {
    delete schedule_;
    for (Entry* entry : previousSelection) {
        delete entry;
    }
    previousSelection.clear();
}

result DataBase::startQuery(std::string& query) {
    result res;
    try {
        std::unique_ptr<Query> q(Query::do_parse(query));
        if (!q) {
            res.addError(Exception(1, "Invalid query"));
            return res;
        }

        ComType command = q->getCommand();

        if (command == SELECT || command == RESELECT) {
            SelectingQuery* sq = dynamic_cast<SelectingQuery*>(q.get());
            if (sq) {
                std::vector<Entry*> selectedEntries;
                if (command == SELECT) {
                    for (Entry* entry : previousSelection) {
                        delete entry;
                    }
                    previousSelection.clear();
                    selectedEntries = schedule_->select(sq->getConditions()); 

                } else {
                    selectedEntries = schedule_->reselect(previousSelection, sq->getConditions());
                }
                previousSelection.clear();
                for (Entry* entry : selectedEntries) {
                    previousSelection.push_back(entry);
                }

                std::stringstream ss;
                for (Entry* entry : selectedEntries) {
                   ss << "Time: " << entry->getTime().startHour << ":" << entry->getTime().startMinute << "-" << entry->getTime().endHour << ":" << entry->getTime().endMinute
                        << ", Room: " << entry->getRoom()
                        << ", Subject: " << entry->getSubjectName()
                        << ", Teacher: " << entry->getTeacher().surname << " " << entry->getTeacher().name << " " << entry->getTeacher().patronymic
                        << ", Group: " << entry->getGroup() << std::endl;

                }
                res.addMessage(ss.str());
            }
        } else if (command == INSERT) {
            AssigningQuery* iq = dynamic_cast<AssigningQuery*>(q.get());
            if (iq) {
                TimeHM time = { 0, 0, 0, 0 };
                int room = 0;
                char subject_name[128] = { 0 };
                FullName teacher = { "", "", "" };
                int group = 0;

                const std::vector<std::pair<Field, Value>>& values = iq->getValues();
                for (const auto& pair : values) {
                    Field field = pair.first;
                    Value value = pair.second;

                    switch (field) {
                    case TIME: {
                       std::pair<TimeHM, TimeHM> timeRange = parseTimeRange(std::get<std::string>(value));
                        time = timeRange.first;
                      break;
                     }

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
                    case TEACHERNAME:{
                         strncpy(teacher.name, std::get<std::string>(value).c_str(), sizeof(teacher.name)-1);
                         break;
}
                     case TEACHERLASTNAME:{
                         strncpy(teacher.surname, std::get<std::string>(value).c_str(), sizeof(teacher.surname)-1);
break;
                    }
                     case TEACHERPATR:{
                         strncpy(teacher.patronymic, std::get<std::string>(value).c_str(), sizeof(teacher.patronymic)-1);
break;
                    }
                    case GROUP:
                        group = std::get<int>(value);
                        break;
                    default:
                        break;
                    }
                }

                Entry* newEntry = new Entry(time, room, subject_name, teacher, group);
                schedule_->addEntry(newEntry);
                res.addMessage("Entry inserted successfully.");
            }
        } else if (command == UPDATE) {
            UpdateQuery* uq = dynamic_cast<UpdateQuery*>(q.get());
            if (uq) {
               res.addError(Exception(1, "UPDATE not implemented"));
            }
        } else if (command == DELETE) {
            DeleteQuery* dq = dynamic_cast<DeleteQuery*>(q.get());
            if (dq) {
              std::vector<Entry*> deletedEntries = schedule_->select(dq->getConditions());
              for (Entry* entry : deletedEntries){
                schedule_->deleteEntry(entry->getTime(), entry->getRoom());
              }
              std::stringstream ss;
              ss << deletedEntries.size() << " entries deleted successfully.";
              res.addMessage(ss.str());
              previousSelection.clear();
            }
        } else if (command == PRINT) {
            PrintQuery* pq = dynamic_cast<PrintQuery*>(q.get());
            if (pq) {
                 std::stringstream ss;
                if (1) {
                    for (Entry* entry : previousSelection) {
                      ss << "Time: " << entry->getTime().startHour << ":" << entry->getTime().startMinute << "-" << entry->getTime().endHour << ":" << entry->getTime().endMinute
                        << ", Room: " << entry->getRoom()
                        << ", Subject: " << entry->getSubjectName()
                        << ", Teacher: " << entry->getTeacher().surname << " " << entry->getTeacher().name << " " << entry->getTeacher().patronymic
                        << ", Group: " << entry->getGroup() << std::endl;

                    }
                }
                 res.addMessage(ss.str());
             }
        }
    } catch (const Exception& err) {
        res.addError(e);
    } catch (...) {
        res.addError(Exception(1, "Unknown exception occurred"));
    }

    return res;
}
