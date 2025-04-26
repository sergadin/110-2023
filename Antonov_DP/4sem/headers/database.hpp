#include "student.hpp"
#include "Tree.hpp"
#include "List.hpp"
#include <iostream>

typedef enum {OK, N_OK} confirm;
typedef enum {SELECT, RESELECT, PRINT, INSERT, REMOVE, UPDATE} oper;
typedef enum {NAME, GROUP, RATING, INFO} field;
typedef enum {EQ, N_EQ, GR, LE, GR_EQ, LE_EQ} binop;
