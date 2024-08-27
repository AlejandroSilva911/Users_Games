// archivo.cpp implento las funciones declaradas en el archivo.h
#include "operations.h"
#include "sqlite3.h"
#include <iostream>

using namespace std;
extern sqlite3* db;// variable externa 

void ingresarDatos()
{
    // Pedir los datos al usuario
    string nombre, apellido, mail, games;

    cout << "Ingrese el nombre: ";
    cin.ignore(); // Para ignorar el '\n' que queda en el buffer
    getline(cin, nombre);
    cout << "Ingrese el apellido: ";
    getline(cin, apellido);
    cout << "Ingrese el email: ";
    getline(cin, mail);
    cout << "Ingrese el número de juegos: ";
    cin >> games;

    // Insertar los datos en la tabla
    const char* sqlInsert = "INSERT INTO Users (nombre, apellido, mail, games) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, nullptr);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, nombre.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, apellido.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, mail.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, games.c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);

        if (rc != SQLITE_DONE) {
            cout << "Error inserting data: " << sqlite3_errmsg(db) << endl;
        } else {
            cout << "Data inserted successfully" << endl;
        }
    } else {
        cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);  // Finalizar el statement
}
void mostrar()
{
    const char* sqlSelect = "SELECT * FROM Users;";
    sqlite3_stmt* stmt;

    // Preparar la consulta SQL
    int rc = sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, nullptr);

    if (rc == SQLITE_OK) {
        cout << "ID | Nombre | Apellido | Email | Juegos" << endl;
        cout << "---------------------------------------" << endl;

        // Ejecutar la consulta y recorrer los resultados
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* nombre = sqlite3_column_text(stmt, 1);
            const unsigned char* apellido = sqlite3_column_text(stmt, 2);
            const unsigned char* mail = sqlite3_column_text(stmt, 3);
            const unsigned char* games = sqlite3_column_text(stmt, 4);
            

            // Mostrar los resultados en la consola
            cout << id << " | " << nombre << " | " << apellido << " | " << mail << " | " << games << endl;
        }
    } else {
        cout << "Error executing SELECT statement: " << sqlite3_errmsg(db) << endl;
    }

    // Finalizar la consulta
    sqlite3_finalize(stmt);
}
void darDeBaja()

{
    string nombre;
    cout << "Ingrese el nombre del usuario a buscar: ";
    cin.ignore(); // Limpiar el buffer
    getline(cin, nombre);

    const char* sqlSearch = "SELECT id, nombre, apellido, mail, games FROM Users WHERE nombre = ?;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sqlSearch, -1, &stmt, nullptr);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, nombre.c_str(), -1, SQLITE_STATIC);

        bool found = false;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            found = true;

            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* apellido = sqlite3_column_text(stmt, 2);
            const unsigned char* mail = sqlite3_column_text(stmt, 3);
            const unsigned char* games = sqlite3_column_text(stmt, 4);

            cout << "Usuario encontrado:\n";
            cout << "ID: " << id << "\nNombre: " << nombre << "\nApellido: " << apellido << "\nEmail: " << mail << "\nJuegos: " << games << endl;

            char confirm;
            cout << "¿Desea eliminar este usuario? (s/n): ";
            cin >> confirm;

            if (confirm == 's' || confirm == 'S') {
                const char* sqlDelete = "DELETE FROM Users WHERE id = ?;";
                sqlite3_stmt* deleteStmt;
                rc = sqlite3_prepare_v2(db, sqlDelete, -1, &deleteStmt, nullptr);

                if (rc == SQLITE_OK) {
                    sqlite3_bind_int(deleteStmt, 1, id);
                    rc = sqlite3_step(deleteStmt);

                    if (rc != SQLITE_DONE) {
                        cout << "Error al eliminar el registro: " << sqlite3_errmsg(db) << endl;
                    } else {
                        cout << "Usuario eliminado exitosamente." << endl;
                    }
                } else {
                    cout << "Error preparando la declaración de eliminación: " << sqlite3_errmsg(db) << endl;
                }

                sqlite3_finalize(deleteStmt);  // Finalizar el statement
            } else {
                cout << "Eliminación cancelada." << endl;
            }
        }

        if (!found) {
            cout << "No se encontró ningún usuario con el nombre: " << nombre << endl;
        }
    } else {
        cout << "Error preparando la declaración de búsqueda: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);  // Finalizar el statement
}
void modificarDatos()
{
    string nombre;
    cout << "Ingrese el nombre del usuario a modificar: ";
    cin.ignore(); // Limpiar el buffer
    getline(cin, nombre);

    const char* sqlSearch = "SELECT id FROM Users WHERE nombre = ?;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sqlSearch, -1, &stmt, nullptr);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, nombre.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);

            // Pedir nuevos datos al usuario
            string nuevoNombre, nuevoApellido, nuevoMail, nuevosGames;

            cout << "Ingrese el nuevo nombre: ";
            getline(cin, nuevoNombre);
            cout << "Ingrese el nuevo apellido: ";
            getline(cin, nuevoApellido);
            cout << "Ingrese el nuevo email: ";
            getline(cin, nuevoMail);
            cout << "Ingrese el nuevo número de juegos: ";
            getline(cin, nuevosGames);

            // Preparar la consulta de actualización
            const char* sqlUpdate = "UPDATE Users SET nombre = ?, apellido = ?, mail = ?, games = ? WHERE id = ?;";
            sqlite3_stmt* updateStmt;
            rc = sqlite3_prepare_v2(db, sqlUpdate, -1, &updateStmt, nullptr);

            if (rc == SQLITE_OK) {
                sqlite3_bind_text(updateStmt, 1, nuevoNombre.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(updateStmt, 2, nuevoApellido.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(updateStmt, 3, nuevoMail.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(updateStmt, 4, nuevosGames.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(updateStmt, 5, id);

                rc = sqlite3_step(updateStmt);

                if (rc != SQLITE_DONE) {
                    cout << "Error al actualizar el registro: " << sqlite3_errmsg(db) << endl;
                } else {
                    cout << "Usuario actualizado exitosamente." << endl;
                }
            } else {
                cout << "Error preparando la declaración de actualización: " << sqlite3_errmsg(db) << endl;
            }

            sqlite3_finalize(updateStmt);  // Finalizar el statement
        } else {
            cout << "No se encontró ningún usuario con el nombre: " << nombre << endl;
        }
    } else {
        cout << "Error preparando la declaración de búsqueda: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);  // Finalizar el statement
}
void buscarDatos()
{
    string apellido;
    cout << "Ingrese el apellido del usuario a buscar: ";
    cin.ignore(); // Limpiar el buffer
    getline(cin, apellido);

    const char* sqlSearch = "SELECT id, nombre, apellido, mail, games FROM Users WHERE apellido = ?;";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sqlSearch, -1, &stmt, nullptr);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, apellido.c_str(), -1, SQLITE_STATIC);

        bool found = false;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            found = true;
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* nombre = sqlite3_column_text(stmt, 1);
            const unsigned char* mail = sqlite3_column_text(stmt, 3);
            const unsigned char* games = sqlite3_column_text(stmt, 4);

            cout << "Usuario encontrado:\n";
            cout << "ID: " << id << "\nNombre: " << nombre << "\nApellido: " << apellido << "\nEmail: " << mail << "\nJuegos: " << games << endl;
            cout << "---------------------------------------" << endl;
        }

        if (!found) {
            cout << "No se encontró ningún usuario con el apellido: " << apellido << endl;
        }
    } else {
        cout << "Error preparando la declaración de búsqueda: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);  // Finalizar el statement
}
void menu()
{
    int option;
    do {
        cout << "1. Ingresar Datos\n";
        cout << "2. Dar de Baja\n";
        cout << "3. Modificar Datos\n";
        cout << "4. Buscar Datos\n";
        cout << "5. Mostrar Datos\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> option;

        switch (option) {
            case 1:
                ingresarDatos();
                break;
            case 2:
                darDeBaja();
                break;
            case 3:
                modificarDatos();
                break;
            case 4:
                buscarDatos();
                break;
            case 5:
                mostrar();
                break;

            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente de nuevo." << endl;
        }
    } while (option != 6);
}