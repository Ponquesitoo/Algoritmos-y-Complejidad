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
            // Costo de sustitución o no hacer nada si son iguales
            int costoSustitucion = pd[i - 1][j - 1] + costo_sub(S1[i - 1], S2[j - 1]);

            // Costo de inserción
            int costoInsercion = pd[i][j - 1] + costo_ins(S2[j - 1]);

            // Costo de eliminación
            int costoEliminacion = pd[i - 1][j] + costo_del(S1[i - 1]);

            // Inicializamos el costo de transposición como un valor muy alto
            int costoTransposicion = INT_MAX;
            // Costo de transposición (si es aplicable)
            if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1]) {
                costoTransposicion = pd[i - 2][j - 2] + costo_trans(S1[i - 2], S1[i - 1]);
            }

            // Selecciona el mínimo entre las cuatro operaciones
            pd[i][j] = min({costoSustitucion, costoInsercion, costoEliminacion, costoTransposicion});
        }
    }
    return pd[m][n];
}

int main() {

    // deben modificarse los valores las cadenas.
    string S1 = "intention"; 
    string S2 = "execution";

        auto inicio = high_resolution_clock::now();
        int distancia_minima = distanciaEdicion_pd(S1, S2);
        auto fin = high_resolution_clock::now();

        auto duracion_s = duration_cast<seconds>(fin - inicio);
        auto duracion_ms = duration_cast<milliseconds>(fin - inicio);


        cout << "Tiempo de ejecucion: " << duracion_s.count() << " [s], "; 
        cout << duracion_ms.count() << " [ms]" << endl;

    return 0;
}