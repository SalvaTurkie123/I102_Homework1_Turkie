# I102_Homework1_Turkie
 Para compilar un ejercicio, debes entrar a la carpeta del ejercicio con el comando 'cd ej1' por ejemplo, luego ejecutar el comando 'make' y se compilará y ejecutará el ejercicio.

4)
La diferencia se debe a que el tiempo de ejecución de la comparación de strings con std::string es mayor que el tiempo de ejecución de la comparación de strings con const char*.
Esto se debe a que std::string es un objeto que contiene un puntero a un array de caracteres y un tamaño, mientras que const char* es simplemente un puntero a un array de caracteres.
