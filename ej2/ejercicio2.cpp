#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>  // Para manejar excepciones

// Enumeración para los niveles de severidad
enum SeverityLevel {
    DEBUG, INFO, WARNING, ERROR, CRITICAL, SECURITY, CUSTOM
};

// Función para obtener la etiqueta del nivel de severidad
std::string getSeverityLabel(SeverityLevel level) {
    switch (level) {
        case DEBUG: return "[DEBUG]";
        case INFO: return "[INFO]";
        case WARNING: return "[WARNING]";
        case ERROR: return "[ERROR]";
        case CRITICAL: return "[CRITICAL]";
        case SECURITY: return "[SECURITY]";
        case CUSTOM: return "[HOLA]";
        default: return "[UNKNOWN]";
    }
}

// Función para escribir en el archivo de log
void logMessage(const std::string& message, SeverityLevel level) {
    std::ofstream logFile("log.txt", std::ios::app);
    if (!logFile) {
        std::cerr << "Error al abrir el archivo de log." << std::endl;
        return;
    }
    logFile << getSeverityLabel(level) << " " << message << std::endl;
    logFile.close();
}

// Función para loggear errores con archivo y línea
void logError(const std::string& message, const std::string& file, int line) {
    logMessage(message + " (Archivo: " + file + ", Línea: " + std::to_string(line) + ")", ERROR);
}

// Función para loggear accesos de usuario
void logSecurity(const std::string& message, const std::string& username) {
    logMessage("Usuario: " + username + " - " + message, SECURITY);
}

// Función que simula un error en runtime
void simulateRuntimeError() {
    throw std::runtime_error("¡Error crítico detectado en runtime!");
}

int main() {
    int opcion;
    std::string mensaje, usuario, archivo;
    int linea;

    while (true) {
        std::cout << "\nMenú de logging:\n";
        std::cout << "1. Log DEBUG\n";
        std::cout << "2. Log INFO\n";
        std::cout << "3. Log WARNING\n";
        std::cout << "4. Log ERROR\n";
        std::cout << "5. Log CRITICAL\n";
        std::cout << "6. Log SECURITY (Acceso de Usuario)\n";
        std::cout << "7. Log ERROR con archivo y línea\n";
        std::cout << "8. Log CUSTOM [HOLA]\n";
        std::cout << "9. Simular error en runtime\n";
        std::cout << "0. Salir\n";
        std::cout << "Elija una opción: ";
        std::cin >> opcion;
        std::cin.ignore(); // Para evitar problemas con getline

        if (opcion == 0) break;

        switch (opcion) {
            case 1: case 2: case 3: case 4: case 5: case 8:
                std::cout << "Ingrese el mensaje: ";
                std::getline(std::cin, mensaje);
                logMessage(mensaje, static_cast<SeverityLevel>(opcion - 1));
                break;
            case 6:
                std::cout << "Ingrese el nombre de usuario: ";
                std::getline(std::cin, usuario);
                std::cout << "Ingrese el mensaje (Access Granted / Access Denied): ";
                std::getline(std::cin, mensaje);
                logSecurity(mensaje, usuario);
                break;
            case 7:
                std::cout << "Ingrese el mensaje de error: ";
                std::getline(std::cin, mensaje);
                std::cout << "Ingrese el nombre del archivo: ";
                std::getline(std::cin, archivo);
                std::cout << "Ingrese el número de línea: ";
                std::cin >> linea;
                logError(mensaje, archivo, linea);
                break;
            case 9:
                try {
                    simulateRuntimeError();
                } catch (const std::exception& e) {
                    logMessage(e.what(), CRITICAL);
                    std::cerr << "Se capturó un error en runtime: " << e.what() << std::endl;
                    return 1;
                }
                break;
            default:
                std::cout << "Opción no válida." << std::endl;
        }
    }

    return 0;
}
