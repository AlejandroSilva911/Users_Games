//en este archivo declaramos la funcion para crear la tabla
#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"

//Declaro la funcion para crear la tabla de Usuarios

int createTable(sqlite3* db);

//Ahora agrego otra tabla Games

int createGamesTable(sqlite3* db);

#endif //database_h