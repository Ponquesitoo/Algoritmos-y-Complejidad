#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

// Función para leer una matriz desde un archivo
vector<vector<int>> leerMatriz(const string& nombreArchivo, int filas, int columnas) {
    ifstream archivo(nombreArchivo);
    vector<vector<int>> matriz(filas, vector<int>(columnas));

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            archivo >> matriz[i][j];
        }
    }

    archivo.close();
    return matriz;
}

// Función para transponer una matriz
vector<vector<int>> transponerMatriz(const vector<vector<int>>& matriz, int filas, int columnas) {
    vector<vector<int>> transpuesta(columnas, vector<int>(filas));
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            transpuesta[j][i] = matriz[i][j]; // Intercambia filas por columnas
        }
    }
    
    return transpuesta;
}

// Función para multiplicar dos matrices
vector<vector<int>> multiplicarMatrices(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2T, int F1, int C1, int F2, int C2) {
    if (C1 != F2) {
        cerr << "Error: El número de columnas de la primera matriz debe ser igual al número de filas de la segunda matriz." << endl;
        exit(EXIT_FAILURE);
    }

    vector<vector<int>> resultado(F1, vector<int>(C2, 0));

    // Optimización: mat2T es la segunda matriz transpuesta
    for (int i = 0; i < F1; ++i) {
        for (int j = 0; j < C2; ++j) {
            for (int k = 0; k < C1; ++k) {
                resultado[i][j] += mat1[i][k] * mat2T[j][k];
            }
        }
    }

    return resultado;
}

// Función para imprimir una matriz
void imprimirMatriz(const vector<vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (const auto& elemento : fila) {
            cout << elemento << "\t";
        }
        cout << endl;
    }
}

int main() {
    // Definir las dimensiones de las matrices
    int F1 = 3500, C1 = 3500;
    int F2 = 3500, C2 = 3500;

    // Leer las matrices desde archivos
    string archivoMat1 = "matriz_7d_1.txt", archivoMat2 = "matriz_7d_2.txt";

    vector<vector<int>> mat1 = leerMatriz(archivoMat1, F1, C1);
    vector<vector<int>> mat2 = leerMatriz(archivoMat2, F2, C2);

    // Transponer la segunda matriz para mejorar la localidad de datos
    vector<vector<int>> mat2T = transponerMatriz(mat2, F2, C2);

    auto start = chrono::high_resolution_clock::now(); // Iniciar cronómetro

    // Multiplicar matrices
    vector<vector<int>> resultado = multiplicarMatrices(mat1, mat2T, F1, C1, F2, C2);

    auto end = chrono::high_resolution_clock::now();   // Finalizar cronómetro

    // Imprimir resultado
    //cout << "\nResultado de la multiplicación de matrices:\n";
    //imprimirMatriz(resultado);

    // Calcular la duración del programa
    chrono::duration<double, milli> duration = end - start;
    chrono::duration<double> duration2 = end - start;
    cout << "\n\nTiempo de ejecucion: " << duration.count() << " ms" << endl;
    cout << "\nTiempo de ejecucion: " << duration2.count() << " s" << endl;

    return 0;
}
