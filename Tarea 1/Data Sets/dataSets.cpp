#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
#include <ctime>

// Función para generar números aleatorios
std::vector<int> generarAleatorio(int tamanio, int min = 0, int max = 1000000) {
    std::vector<int> datos(tamanio);
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_int_distribution<> dis(min, max);
    for(auto &num : datos) {
        num = dis(gen);
    }
    return datos;
}

// Función para generar datos ordenados
std::vector<int> generarOrdenado(int tamanio) {
    std::vector<int> datos(tamanio);
    for(int i = 0; i < tamanio; ++i) {
        datos[i] = i;
    }
    return datos;
}

// Función para generar datos inversamente ordenados
std::vector<int> generarInversamenteOrdenado(int tamanio) {
    std::vector<int> datos(tamanio);
    for(int i = 0; i < tamanio; ++i) {
        datos[i] = tamanio - i;
    }
    return datos;
}

// Función para generar datos parcialmente ordenados
std::vector<int> generarParcialmenteOrdenado(int tamanio, double porcentajeOrdenado = 0.5) {
    std::vector<int> datos = generarOrdenado(tamanio);
    int desordenar = tamanio * (1 - porcentajeOrdenado);
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_int_distribution<> dis(0, tamanio - 1);
    for(int i = 0; i < desordenar; ++i) {
        int idx1 = dis(gen);
        int idx2 = dis(gen);
        std::swap(datos[idx1], datos[idx2]);
    }
    return datos;
}

// Función para generar una matriz aleatoria
std::vector<std::vector<int>> generarMatriz(int filas, int columnas, std::mt19937 &gen, int min = 0, int max = 10) {
    std::vector<std::vector<int>> matriz(filas, std::vector<int>(columnas));
    std::uniform_int_distribution<> dis(min, max);

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = dis(gen);
        }
    }
    return matriz;
}

// Función para guardar datos en un archivo de texto
void guardarDatos(const std::vector<int> &datos, const std::string &nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if(archivo.is_open()) {
        for(const auto &num : datos) {
            archivo << num << " ";
        }
        archivo.close();
        std::cout << "Datos guardados en " << nombreArchivo << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
}

// Función para guardar una matriz en un archivo de texto
void guardarMatriz(const std::vector<std::vector<int>> &matriz, const std::string &nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (const auto &fila : matriz) {
            for (const auto &num : fila) {
                archivo << num << " ";
            }
            archivo << std::endl;
        }
        archivo.close();
        std::cout << "Matriz guardada en " << nombreArchivo << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
}

int main() {
    int tamanio = 1000000; // tamanio de datasets ordenamiento de datos.
    int cuadrada = 5000; // tamanio de las matrices
    
    // Inicializar generador de números aleatorios 
     std::mt19937 gen(static_cast<unsigned int>(time(0)));

    // Generar y guardar datasets
    // ordenamiento de datos
    std::vector<int> aleatorio = generarAleatorio(tamanio);
    guardarDatos(aleatorio, "aleatorio.txt");

    std::vector<int> ordenado = generarOrdenado(tamanio);
    guardarDatos(ordenado, "ordenado.txt");

    std::vector<int> inversamenteOrdenado = generarInversamenteOrdenado(tamanio);
    guardarDatos(inversamenteOrdenado, "inversamente_ordenado.txt");

    std::vector<int> parcialmenteOrdenado = generarParcialmenteOrdenado(tamanio, 0.5);
    guardarDatos(parcialmenteOrdenado, "parcialmente_ordenado.txt");

    // multiplicación de matrices
    std::vector<std::vector<int>> matriz1 = generarMatriz(cuadrada, cuadrada, gen);
    guardarMatriz(matriz1, "m1.txt");

    std::vector<std::vector<int>> matriz2 = generarMatriz(cuadrada, cuadrada, gen);
    guardarMatriz(matriz2, "m2.txt");

    return 0;
}
