#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits.h>
#include <chrono>

#include "funciones_costo.cpp"

using namespace std;
using namespace std::chrono;

int distanciaEdicion_pd(const string& S1, const string& S2) {
    int m = S1.size();
    int n = S2.size();

    vector<vector<int>> pd(m+1, vector<int>(n+1, 0));

    for(int i = 1; i <= m; ++i) {
        pd[i][0] = pd[i-1][0] + costo_del(S1[i-1]);
    }
    for(int j = 1; j <= n; ++j) {
        pd[0][j] = pd[0][j-1] + costo_ins(S2[j-1]);
    }
    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= n; ++j) {
            // Costo de sustitucion
            int costoSustitucion = pd[i - 1][j - 1] + costo_sub(S1[i - 1], S2[j - 1]);

            // Costo de insercion
            int costoInsercion = pd[i][j - 1] + costo_ins(S2[j - 1]);

            // Costo de eliminacion
            int costoEliminacion = pd[i - 1][j] + costo_del(S1[i - 1]);

            int costoTransposicion = INT_MAX;
            // Costo de transposición (si es aplicable)
            if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1]) {
                costoTransposicion = pd[i - 2][j - 2] + costo_trans(S1[i - 2], S1[i - 1]);
            }
            // el minimo entre las cuatro operaciones
            pd[i][j] = min({costoSustitucion, costoInsercion, costoEliminacion, costoTransposicion});
        }
    }
    return pd[m][n];
}

int main() {

    vector <string> S1, S2;
    vector<float> tiempos, tamanios;
    float seg_totales = 0;
    int cant_lineas = 0;
    
    size_t limite = 100; // se debe modificar por el numero de pares de cadenas deseado
    string nombreArchivo = "transposiciones.txt"; // se debe modificar por el nombre del dataset
    
    cadenas(nombreArchivo, S1, S2, limite, cant_lineas);
    if (S1.size() != S2.size()) {
        cerr <<"S1 y S2 no coinciden en tamanio." << endl;
        return 1;
    }
    for(int i = 0; i < S1.size(); ++i) {
        auto inicio = high_resolution_clock::now();
        int distancia_minima = distanciaEdicion_pd(S1[i], S2[i]);
        auto fin = high_resolution_clock::now();

        auto duracion_s = duration_cast<seconds>(fin - inicio);
        auto duracion_ms = duration_cast<milliseconds>(fin - inicio);

        seg_totales += duracion_s.count();

        cout << i+1 << ". "<< "Tiempo de ejecucion: " << duracion_s.count() << " [s], "; 
        cout << duracion_ms.count() << " [ms]" << endl;
    }
    tiempos.push_back(seg_totales);
    escribirArchivo(tiempos, "tiempos_transposiciones_PD.txt");

    tamanios.push_back(cant_lineas);
    escribirArchivo(tamanios, "tamanio_transposiciones_PD.txt");

    cout << "Duracion total: " << seg_totales << "[s]" << endl;

    return 0;
}
