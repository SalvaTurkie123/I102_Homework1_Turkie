#include <iostream>
#include <string>
#include <chrono>

// 1. Comparación con std::string (recursiva)
bool compareStrings(const std::string& str1, const std::string& str2, size_t index = 0) {
    if (index == str1.size() && index == str2.size()) return true;
    if (index >= str1.size() || index >= str2.size() || str1[index] != str2[index]) return false;
    return compareStrings(str1, str2, index + 1);
}

// 2. Comparación con const char* (recursiva)
bool compareStrings(const char* str1, const char* str2) {
    if (*str1 == '\0' && *str2 == '\0') return true;
    if (*str1 != *str2) return false;
    return compareStrings(str1 + 1, str2 + 1);
}

// 3. Comparación en tiempo de compilación con constexpr
constexpr bool compareStringsConstexpr(const char* str1, const char* str2) {
    return (*str1 == '\0' && *str2 == '\0') ? true :
           (*str1 != *str2) ? false :
           compareStringsConstexpr(str1 + 1, str2 + 1);
}

int main() {
    const std::string texto1 = "Hola, este es un texto de aprox 64 caracteres para compararlo ahora";
    const std::string texto2 = "Hola, este es un texto de aprox 64 caracteres para compararlo ahora";
    const char* texto1_char = "Hola, este es un texto de aprox 64 caracteres para compararlo ahora";
    const char* texto2_char = "Hola, este es un texto de aprox 64 caracteres para compararlo ahora";

    // Medición del tiempo de ejecución con std::string
    auto start1 = std::chrono::high_resolution_clock::now();
    bool result1 = compareStrings(texto1, texto2);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1);

    std::cout << "Comparación usando std::string: " << (result1 ? "Iguales" : "Diferentes")
              << " - Tiempo: " << time1.count() << " ns" << std::endl;

    // Medición del tiempo de ejecución con const char*
    auto start2 = std::chrono::high_resolution_clock::now();
    bool result2 = compareStrings(texto1_char, texto2_char);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2);

    std::cout << "Comparación usando const char*: " << (result2 ? "Iguales" : "Diferentes")
              << " - Tiempo: " << time2.count() << " ns" << std::endl;

    // Comparación en tiempo de compilación (no requiere medición de tiempo)
    constexpr bool result3 = compareStringsConstexpr(
        "Hola, este es un texto de aprox 64 caracteres para compararlo ahora",
        "Hola, este es un texto de aprox 64 caracteres para compararlo ahora"
    );    
    std::cout << "Comparación en tiempo de compilación (constexpr): " << (result3 ? "Iguales" : "Diferentes")
              << " - Tiempo: 0 ns (evaluado en compilación)" << std::endl;

    return 0;
}
