#include <iostream>
#include <fstream>
#include <string>
#include <exception>

using namespace std;

// Función base para escribir en el log
void logMessage(const string& message, const string& level) {
    ofstream logFile("log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << "[" << level << "] " << "<" << message << ">" << endl;
        logFile.close();
    } else {
        cerr << "Error: No se pudo abrir el archivo de log." << endl;
    }
}

// Función para registrar errores con más detalles
void logError(const string& message, const string& file, int line) {
    logMessage(message + " - Archivo: " + file + " - Línea: " + to_string(line), "ERROR");
}

// Función para registrar accesos de usuario
void logSecurity(const string& message, const string& user) {
    logMessage(message + " - Usuario: " + user, "SECURITY");
}

// Función que simula un error en runtime
void simulateRuntimeError() {
    try {
        throw runtime_error("Simulación de error en runtime.");
    } catch (const exception& e) {
        logError(e.what(), __FILE__, __LINE__);
        cerr << "Se capturó un error en runtime: " << e.what() << endl;
        // Se detiene el programa con código de error
        exit(1);  
    }
}

// Función de prueba
void testLoggingSystem() {
    logMessage("El sistema inició correctamente", "INFO");
    logError("Error de conexión a la base de datos", "database.cpp", 45);
    logSecurity("Access Denied", "usuario123");

    // Simulación de un error crítico
    simulateRuntimeError();

}

int main() {
    testLoggingSystem();
    return 0;
}
