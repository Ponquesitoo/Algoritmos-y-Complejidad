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

    //deben modificarse los valores de las cadenas
    string S1 = "intention";
    string S2 = "execution";

    auto inicio = high_resolution_clock::now();
    int distancia_minima = distanciaEdicion_fb(S1, S2, 0, 0);
    auto fin = high_resolution_clock::now();
    
    auto duracion = duration_cast<seconds>(fin - inicio);
    auto duracion_ms = duration_cast<milliseconds>(fin - inicio);

    cout << "Tiempo de ejecucion: " << duracion.count() << " [s] , ";
    cout << duracion_ms.count() << " [ms]" << endl;

    return 0;
    
}