#include <bits/stdc++.h>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

// funcion para leer el archivo con el dataset
vector<int> leerDatos(const string& nombreArchivo, int cantidadMaxima) {
    vector<int> datos;
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return {};
    }
    int valor;
    int contador = 0;
    while (archivo >> valor && contador < cantidadMaxima) {
        datos.push_back(valor);
        contador++;
    } 
    archivo.close();
    return datos;
}

// Function for Selection sort
void selectionSort(vector<int>& arreglo) {
    int  n = arreglo.size();
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arreglo[j] < arreglo[min_index]) min_index = j;
        }
        if (min_index != i) {
            swap(arreglo[min_index], arreglo[i]);
        }
    }
}

// Function to print an array
void printArray(const vector<int>& arreglo) {
    for (int i = 0; i < arreglo.size(); i++)
        cout << arreglo[i] << " ";
    cout << endl;
}
// programa principal

int main() {
    string nombreArchivo = "inversamente_ordenado.txt";
    int cantidad_datos = 750000;
    vector<int> datos = leerDatos(nombreArchivo, cantidad_datos);
    auto inicio = high_resolution_clock::now();
    selectionSort(datos);
    auto fin = high_resolution_clock::now();
    duration<double, milli> duracion = fin - inicio;
    duration<double> duracion_seg = fin - inicio;
    printArray(datos);
    cout << "\n\nTiempo de ejecucion: " << duracion.count() << " ms"<< endl;
    cout << "\nTiempo de ejecucion: " << duracion_seg.count() << " s" << endl;
}

// This is code is contributed by rathbhupendra
