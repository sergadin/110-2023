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
                    ss << "Date: " << entry->getDate().day << "." << entry->getDate().month
                        << ", Lesson: " << entry->getLesson()
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
                Date date = { 0, 0 };
                int lesson = 0;
                int room = 0;
                char subject_name[128] = { 0 };
                FullName teacher = { "", "", "" };
                int group = 0;

                const std::vector<std::pair<Field, Value>>& values = iq->getValues();
                for (const auto& pair : values) {
                    Field field = pair.first;
                    Value value = pair.second;

                    switch (field) {
                    case DAY: {
                        std::vector<std::pair<Date, Date>> dateRanges = parseDateRange(std::get<std::string>(value));
                        date = dateRanges[0].first;
                        break;
                    }
                    case LESSON_NUM: {
                        std::vector<std::pair<int, int>> lessonRanges = parseLessonRange(std::get<std::string>(value));
                        lesson = lessonRanges[0].first; 
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
                    case TEACHERNAME: {
                        strncpy(teacher.name, std::get<std::string>(value).c_str(), sizeof(teacher.name) - 1);
                        break;
                    }
                    case TEACHERLASTNAME: {
                        strncpy(teacher.surname, std::get<std::string>(value).c_str(), sizeof(teacher.surname) - 1);
                        break;
                    }
                    case TEACHERPATR: {
                        strncpy(teacher.patronymic, std::get<std::string>(value).c_str(), sizeof(teacher.patronymic) - 1);
                        break;
                    }
                    case GROUP:
                        group = std::get<int>(value);
                        break;
                    default:
                        break;
                    }
                }

                Entry* newEntry = new Entry(date, lesson, room, subject_name, teacher, group);
                schedule_->addEntry(newEntry);
                res.addMessage("Entry inserted successfully.");
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
                        case DAY: {
                            std::vector<std::pair<Date, Date>> dateRanges = parseDateRange(std::get<std::string>(value));
                            entry->setDate(dateRanges[0].first);
                            break;
                        }
                        case LESSON_NUM: {
                            std::vector<std::pair<int, int>> lessonRanges = parseLessonRange(std::get<std::string>(value));
                            entry->setLesson(lessonRanges[0].first);
                            break;
                        }
                        case ROOM:
                            entry->setRoom(std::get<int>(value));
                            break;
                        case SUBJNAME: {
                            std::string subjName = std::get<std::string>(value);
                            entry->setSubjectName(subjName.c_str());
                            break;
                        }
                        case TEACHERNAME: {
                            FullName teacher = entry->getTeacher();
                            strncpy(teacher.name, std::get<std::string>(value).c_str(), sizeof(teacher.name) - 1);
                            entry->setTeacher(teacher);
                            break;
                        }
                        case TEACHERLASTNAME: {
                            FullName teacher = entry->getTeacher();
                            strncpy(teacher.surname, std::get<std::string>(value).c_str(), sizeof(teacher.surname) - 1);
                            entry->setTeacher(teacher);
                            break;
                        }
                        case TEACHERPATR: {
                            FullName teacher = entry->getTeacher();
                            strncpy(teacher.patronymic, std::get<std::string>(value).c_str(), sizeof(teacher.patronymic) - 1);
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
            }
        } else if (command == DELETE) {
            DeleteQuery* dq = dynamic_cast<DeleteQuery*>(q.get());
            if (dq) {
                std::vector<Entry*> deletedEntries = schedule_->select(dq->getConditions());
                for (Entry* entry : deletedEntries) {
                    schedule_->deleteEntry(entry->getDate(), entry->getLesson(), entry->getRoom());
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
                        ss << "Date: " << entry->getDate().day << "." << entry->getDate().month
                            << ", Lesson: " << entry->getLesson()
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
        printf("Error a\n");
        res.addError(err);
    } catch (const std::bad_variant_access&) {
        printf("I found it!\n");
    } catch (...) {
        printf("Error b\n");
        res.addError(Exception(1, "Unknown exception occurred"));
    }

    return res;
}
