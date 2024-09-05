// main.cpp
#include <iostream>
#include "sqlite3.h"
#include "database.h"
#include "operations.h"

using namespace std;
sqlite3* db;

int main(int argc, char* argv[]) {
    int rc = sqlite3_open("Test.db", &db);
    
    if (rc) {
        cout << "Database file could not be opened: " << sqlite3_errmsg(db) << endl;
        return rc;
    } else {
        cout << "Database opened successfully" << endl;

        // Llamar a la creación de la tabla Users
        rc = createTable(db);
        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            return rc;
        }

        // Llamar a la creación de la tabla Games
        rc = createGamesTable(db);
        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            return rc;
        }

        // Llamar al menú principal
        menu();
    }
    
    sqlite3_close(db);  // Cerrar la base de datos para liberar recursos
    return 0;
}
