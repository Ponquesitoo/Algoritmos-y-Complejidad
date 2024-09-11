#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <cstdlib> 
#include <ctime>   

using namespace std;

// Función para hacer la partición de Quicksort con pivote aleatorio
int partition(vector<int>& vec, int low, int high) {
    // Elegir un pivote aleatorio y moverlo al final
    int randomPivotIndex = low + rand() % (high - low + 1);
    swap(vec[randomPivotIndex], vec[high]); // Colocamos el pivote aleatorio en la posición final

    int pivot = vec[high]; // El último elemento ahora es el pivote
    int i = (low - 1);     // Índice más pequeño

    for (int j = low; j <= high - 1; j++) {
        // Si el elemento actual es menor o igual al pivote
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]); // Intercambiamos los elementos
        }
    }
    swap(vec[i + 1], vec[high]); // Ponemos el pivote en su lugar
    return (i + 1);
}

// Implementación de Quicksort
void quickSort(vector<int>& vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high); // Índice de partición
        quickSort(vec, low, pi - 1);        // Ordenar los elementos antes de la partición
        quickSort(vec, pi + 1, high);       // Ordenar los elementos después de la partición
    }
}

// Función para leer los datos desde un archivo
vector<int> leerDatos(const string& nombreArchivo, int cantidad) {
    vector<int> datos;
    ifstream archivo(nombreArchivo);
    int valor;
    int contador = 0;

    while (archivo >> valor && contador < cantidad) {
        datos.push_back(valor);
        contador++;
    }
    archivo.close();

    return datos;
}

int main() {
    // Inicializar para usar números aleatorios
    srand(time(0)); 

    // Archivo de entrada y número de elementos
    string nombreArchivo = "aleatorio.txt"; 
    int cantidadElementos = 750000;        

    // Leer datos del archivo
    vector<int> vec = leerDatos(nombreArchivo, cantidadElementos);

    // Verificar si el archivo se leyó correctamente
    if (vec.empty()) {
        cout << "No se pudieron leer datos del archivo." << endl;
        return 1;
    }

    // Medir el tiempo de ejecución de quicksort
    auto start = chrono::high_resolution_clock::now();
    quickSort(vec, 0, vec.size() - 1);
    auto end = chrono::high_resolution_clock::now();

    // Mostrar el vector ordenado
    // for (int num : vec) {
    //     cout << num << " ";
    // }
    // cout << endl;

    // Calcular y mostrar el tiempo de ejecución
    chrono::duration<double, milli> duration = end - start;
    chrono::duration<double> duration2 = end - start;
    cout << "\n\nTiempo de ejecucion: " << duration.count() << " ms" << endl;
    cout << "\nTiempo de ejecucion: " << duration2.count() << " seg" << endl;

    return 0;
}
