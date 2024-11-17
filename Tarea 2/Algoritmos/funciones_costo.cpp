#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;

const vector <char> abecedario = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

//funcion para leer la matriz
vector<vector<int>> leer_matriz(const string& nombreArchivo) {
    vector<vector<int>> matriz;
    fstream archivo;
    archivo.open(nombreArchivo, ios::in);
    if(!archivo.is_open()) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return matriz;
    }
    
    string linea;
    while (getline(archivo, linea)) {
        istringstream stream(linea);
        vector<int> fila;
        int valor;
        while (stream >> valor) {
            fila.push_back(valor);
        }
        matriz.push_back(fila);
    }
    archivo.close();
    return matriz;
}


// encontrar posicion en el abecedario de las cuestiones
int pos_abc(char a) {
    int posicion = -1; //si la posicion es -1, el simbolo no se encuentra en el abecedario
    for(int i = 0; i < abecedario.size(); i++) {
        if(abecedario[i] == a) {
            posicion = i;
        }
    }
    return posicion;
}

//funcion para leer el archivo, retorna dos vectores de cadenas, S1 y S2
void cadenas(string nombreArchivo, vector<string>& S1, vector<string>& S2, size_t limite, int& cant_lineas) {
    fstream archivo;
    archivo.open(nombreArchivo, ios::in);
    if(!archivo.is_open()) {
        cerr << "el archivo " << nombreArchivo << ", no se abrió." << endl;
        return;
    }
    string linea;
    size_t contador = 0;
    while(getline(archivo, linea) && contador < limite) {
        size_t pos = linea.find(',');
        if(pos != string::npos) {
            S1.push_back(linea.substr(0,pos));
            S2.push_back(linea.substr(pos+1));
            contador++;
            cant_lineas++;
        } else{
            cerr << "linea invalida" << endl;
        }
    }
    archivo.close();
}

//funcion para escribir el tiempo en un archivo.
void escribirArchivo( vector<float>& tiempos, const string& nombreArchivo) {
    fstream archivo;
    archivo.open(nombreArchivo, ios::app);
    if(!archivo.is_open()) {
        cerr << "El archivo " << nombreArchivo << " no se ha abierto." << endl;
        return;
    } else {
        for( const int& tiempo : tiempos) {
            archivo << tiempo << endl;
        }
    }
    archivo.close();
}

int costo_sub(char a, char b) {
    int costo = 0, pos_a, pos_b;
    vector<vector<int>> matriz = leer_matriz("cost_replace.txt");
    pos_a = pos_abc(a);
    pos_b = pos_abc(b);
    costo = matriz[pos_a][pos_b];
    return costo;
}

int costo_ins(char b) {
    int costo = 0, pos_b;
    vector<vector<int>> matriz = leer_matriz("cost_insert.txt");
    pos_b = pos_abc(b);
    costo = matriz[0][pos_b];
    return costo;
}

int costo_del(char a) {
    int costo = 0, pos_a;
    vector<vector<int>> matriz = leer_matriz("cost_delete.txt");
    pos_a = pos_abc(a);
    costo = matriz[0][pos_a];
    return costo;

}

int costo_trans(char a, char b) {
    int costo = 0, pos_a, pos_b;
    vector<vector<int>> matriz = leer_matriz("cost_transpose.txt");
    pos_a = pos_abc(a);
    pos_b = pos_abc(b);
    costo = matriz[pos_a][pos_b];
    return costo;
}

// costo sustitucion -- LISTA

// int costo_sub(char a, char b, vector<char> abecedario) {
//     int costo = 0, pos_a, pos_b;
//     for (int i = 0; i < abecedario.size(); i++) {
//         if(abecedario[i] == b) {
//             pos_b = i;
//         } 
//         if(abecedario[i] == a) {
//             pos_a = i;
//         }
//     }
//     int d = abs(pos_a - pos_b);
//     // asignacion de costos dependiendo de la distancia "d" entre las letras, dentro del abecedario
    
//     // caso 1: a = b
//     if (d == 0) {
//         costo = 0;
//     }
//     // caso 2: 1 <= I <= 8
//     if (d >= 1 && d <= 8) {
//         costo = 1;
//     }
//     // caso 3: 8 < II <= 17
//     if (d > 8 && d <= 17) {
//         costo = 2;
//     }
//     // caso 4: 17 < III <= 25
//     if (d > 17 && d <= 25) {
//         costo = 3;
//     }
//     return costo;

// }

// // costo insercion 
// int costo_in(char a) {
//     int costo;

//     return costo;
// }

// // costo eliminacion / delete
// int costo_del(char b) {
//     int costo;

//     return costo;
// }

// // costo transposicion 
// int costo_trans(char a, char b) {
//     int costo;

//     return costo;
// }