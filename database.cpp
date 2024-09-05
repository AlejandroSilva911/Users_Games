#include "database.h"  // Archivo de encabezado donde se declaran las funciones
#include <iostream>
#include "sqlite3.h"

int createTable(sqlite3* db) {
    const char* sqlCreateTable = R"(
    CREATE TABLE IF NOT EXISTS Users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        nombre TEXT NOT NULL,
        apellido TEXT NOT NULL,
        mail TEXT NOT NULL UNIQUE,
        games TEXT NOT NULL
    );
    )";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cout << "Error al crear la tabla Users: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return rc;
    } else {
        std::cout << "Tabla Users creada OK" << std::endl;
    }

    return SQLITE_OK;
}

int createGamesTable(sqlite3* db) {
    const char* sqlCreateGamesTable = R"(
    CREATE TABLE IF NOT EXISTS Games (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        nombre_juego TEXT NOT NULL
    );
    )";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sqlCreateGamesTable, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cout << "Error al crear la tabla Games: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return rc;
    } else {
        std::cout << "Tabla Games creada OK" << std::endl;
    }

    return SQLITE_OK;
}
