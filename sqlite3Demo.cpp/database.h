//en este archivo declaramos la funcion para crear la tabla
#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"

int createTable(sqlite3* db);
#endif