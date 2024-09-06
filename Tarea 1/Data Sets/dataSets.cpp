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

int main() {
    int tamanio = 1000000; // Puedes variar el tamanio según necesites

    // Generar y guardar datasets
    std::vector<int> aleatorio = generarAleatorio(tamanio);
    guardarDatos(aleatorio, "aleatorio.txt");

    std::vector<int> ordenado = generarOrdenado(tamanio);
    guardarDatos(ordenado, "ordenado.txt");

    std::vector<int> inversamenteOrdenado = generarInversamenteOrdenado(tamanio);
    guardarDatos(inversamenteOrdenado, "inversamente_ordenado.txt");

    std::vector<int> parcialmenteOrdenado = generarParcialmenteOrdenado(tamanio, 0.5);
    guardarDatos(parcialmenteOrdenado, "parcialmente_ordenado.txt");

    return 0;
}
