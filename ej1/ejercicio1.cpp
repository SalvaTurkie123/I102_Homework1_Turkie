#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Genero la matriz
vector<vector<int>> generarMatriz(int n) {
    vector<vector<int>> matriz(n, vector<int>(n));
    int valor = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matriz[i][j] = valor++;
        }
    }
    return matriz;
}

// Función para imprimir la matriz en orden descendente
void imprimirMatrizDescendente(const vector<vector<int>>& matriz) {
    int n = matriz.size();
    vector<pair<int, pair<int, int>>> elementos;

    // Guardar valores con sus índices
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            elementos.push_back({matriz[i][j], {i, j}});
        }
    }

    // Ordenar en orden descendente
    sort(elementos.rbegin(), elementos.rend());

    // Imprimir los valores
    for (const auto& elem : elementos) {
        cout << "M_" << n << "[" << elem.second.first << "][" << elem.second.second << "] = " << elem.first << endl;
    }
}

int main() {
    int n;
    cout << "Ingrese el tamaño de la matriz: ";
    cin >> n;

    if (n < 2) {
        cout << "El valor de n debe ser mayor a 1." << endl;
        return 1;
    }

    vector<vector<int>> matriz = generarMatriz(n);
    imprimirMatrizDescendente(matriz);

    return 0;
}
