#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono> 
using namespace std;

// Función para leer datos desde un archivo y almacenarlos en un vector
vector<int> leerDatos(const string& nombreArchivo, int elementos) {
    vector<int> datos;
    ifstream archivo(nombreArchivo);
    int valor;
    int contador = 0;
    while (archivo >> valor && contador < elementos) {
        datos.push_back(valor);
        contador++;
    }
    archivo.close();
    return datos;
}

// Función para combinar dos subarreglos de arr[]
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear vectores temporales
    vector<int> L(n1), R(n2);

    // Copiar datos a los vectores temporales L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Combinar los vectores temporales en arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si los hay
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si los hay
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función de Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Función para imprimir un vector
void printVector(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Función principal
int main() {
    string nombreArchivoEntrada = "aleatorio.txt";
    int numero_elementos = 50000;
    // Leer nombre del archivo de entrada

    // Leer el dataset desde el archivo
    vector<int> arr = leerDatos(nombreArchivoEntrada, numero_elementos);

    if (arr.empty()) {
        cerr << "No se encontraron datos en el archivo o no se pudo abrir." << endl;
        return -1;
    }

    // Medir el tiempo de ejecución de Merge Sort
    auto start = chrono::high_resolution_clock::now(); // Iniciar cronómetro
    mergeSort(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();   // Finalizar cronómetro
    printVector(arr);
    // Calcular la duración en milisegundos
    chrono::duration<double, milli> duration = end - start;
    chrono::duration<double> duration2 = end - start;
    cout << "\n\nTiempo de ejecucion: " << duration.count() << " ms" << endl;
    cout << "\nTiempo de ejecucion: " << duration2.count() << " s" << endl;
    return 0;
}
