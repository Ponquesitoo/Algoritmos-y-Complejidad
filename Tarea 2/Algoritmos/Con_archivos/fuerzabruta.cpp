#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>
#include <limits.h>
#include <chrono>

#include "funciones_costo.cpp"

using namespace std;
using namespace std::chrono;

int distanciaEdicion_fb(const string& S1, const string& S2, int i, int j) {

    if(i == S1.size()) {
        int total_cost = 0;
        for(int x = j; x < S2.size(); ++x) {
            total_cost += costo_ins(S2[x]);
        }
        return total_cost;
    }
    
    if (j == S2.size()) {
        int total_cost = 0;
        for(int y = i; y < S1.size(); ++y) {
            total_cost += costo_del(S1[y]);
        }
        return total_cost;
    }

    int costoSustitucion = costo_sub(S1[i], S2[j]) + distanciaEdicion_fb(S1, S2, i+1, j+1);
    int costoInsercion = costo_ins(S2[j]) + distanciaEdicion_fb(S1, S2, i, j+1);
    int costoEliminacion = costo_del(S1[i]) + distanciaEdicion_fb(S1, S2, i+1, j);
    int costoTransposicion = INT_MAX;
    if (i + 1 < S1.size() && j + 1 < S2.size() && S1[i] == S2[j + 1] && S1[i + 1] == S2[j]) {
        costoTransposicion = costo_trans(S1[i], S1[i + 1]) + distanciaEdicion_fb(S1, S2, i + 2, j + 2);
    }
    return min({costoEliminacion, costoInsercion, costoSustitucion, costoTransposicion});

}

int main() {

    float seg_totales = 0;
    int cant_lineas = 0;
    vector<float> tiempos;
    vector<float> tamanios;
    vector<string> S1, S2;
    
    size_t limite = 15; // Se debe modificar por el numero de pares de cadenas que se desea leer del dataset, dado que cada linea es un par S1 y S2
    string nombreArchivo = "vacioS1.txt"; // Se debe modificar por el nombre del dataset
    
    cadenas(nombreArchivo, S1, S2, limite, cant_lineas);
    
    if (S1.size() != S2.size()) {
        cerr << "S1 y S2 no coinciden en tamanio." << endl;
        return 1;
    }

    for(int i = 0; i < S1.size(); ++i){
        auto inicio = high_resolution_clock::now();
        int distancia_minima = distanciaEdicion_fb(S1[i], S2[i], 0, 0);
        auto fin = high_resolution_clock::now();
        
        auto duracion = duration_cast<seconds>(fin - inicio);
        auto duracion_ms = duration_cast<milliseconds>(fin - inicio);

        seg_totales += duracion.count();
        cout << i+1 << ". "<< "Tiempo de ejecucion: " << duracion.count() << " [s] , ";
        cout << duracion_ms.count() << " [ms]" << endl;
    }
    //guardamos los tiempos en un archivo
    tiempos.push_back(seg_totales);
    escribirArchivo(tiempos, "tiempos_largo.txt");

    //guardamos la cantidad de lineas en un archivo
    tamanios.push_back(cant_lineas);
    escribirArchivo(tamanios, "tamanio_largo.txt");

    cout << endl;
    cout << "Duracion total: " << seg_totales << endl;
    

    return 0;
    
}
