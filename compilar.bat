@echo off
REM Establece el directorio de trabajo al del script
cd /d "%~dp0"

REM Compila el programa C++
g++ main.cpp database.cpp operations.cpp -o sqlite3Demo.exe -I.\lib -L.\lib -lsqlite3

REM Verifica si la compilación fue exitosa
if %errorlevel% neq 0 (
    echo Error en la compilación.
    pause
    exit /b %errorlevel%
)

echo Compilación exitosa.

REM Ejecuta el programa compilado
sqlite3Demo.exe

REM Pausa para ver el resultado
pause
