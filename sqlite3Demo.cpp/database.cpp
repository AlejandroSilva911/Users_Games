//definimos la funcion para crear la tabla
#include "database.h"//el archivo en donde la declaramos
#include <iostream>

int createTable(sqlite3* db)
{
    const char* sqlCreateTable= R"(
    CREATE TABLE IF NOT EXISTS Users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        nombre TEXT NOT NULL,
        apellido TEXT NOT NULL,
        mail TEXT NOT NULL UNIQUE,
        games TEXT  NOT NULL
        );
    
    )";
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cout<<"Error al crear la tabla: "<<errMsg << std::endl;
        sqlite3_free(errMsg);
        return rc;
    } else 
        {
            std::cout<<" Tabla creada OK "<<std::endl;
        }

return SQLITE_OK;

}