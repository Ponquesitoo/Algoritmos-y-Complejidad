#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>

using namespace std;

// Función para leer los datos desde un archivo
vector<int> leerDatos(const string& nombreArchivo, int cantidad) {
    vector<int> datos;
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return datos;
    }

    int valor;
    int contador = 0;

    while (archivo >> valor && contador < cantidad) {
        datos.push_back(valor);
        contador++;
    }
    archivo.close();

    if (datos.size() != cantidad) {
        cerr << "Advertencia: Se esperaban " << cantidad << " elementos, pero se leyeron " << datos.size() << "." << endl;
    }

    return datos;
}

// Función para imprimir un vector
void printVector(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // Solicitar al usuario el archivo de entrada y número de elementos
    string nombreArchivo = "aleatorio.txt";
    int cantidadElementos = 750000;

    // Leer datos del archivo
    vector<int> vec = leerDatos(nombreArchivo, cantidadElementos);

    // Verificar si el archivo se leyó correctamente
    if (vec.empty()) {
        cerr << "No se pudieron leer datos del archivo o está vacío." << endl;
        return 1;
    }

    // Medir el tiempo de ejecución
    auto start = chrono::high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto end = chrono::high_resolution_clock::now();

    // Mostrar los datos ordenados
    printVector(vec);

    // Calcular y mostrar el tiempo de ejecución
    chrono::duration<double, milli> duration_ms = end - start;
    chrono::duration<double> duration_sec = end - start;
    cout << "\nTiempo de ejecución: " << duration_ms.count() << " ms" << endl;
    cout << "Tiempo de ejecución: " << duration_sec.count() << " seg" << endl;

    return 0;
}
