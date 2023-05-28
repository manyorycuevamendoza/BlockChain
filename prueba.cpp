#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<string>> leerCSV(string nombreArchivo, char delimitador) {
    vector<vector<string>> datos;

    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo CSV." << endl;
        return datos;
    }

    string linea;
    while (getline(archivo, linea)) {
        vector<string> fila;
        stringstream ss(linea);
        string campo;

        while (getline(ss, campo, delimitador)) {
            fila.push_back(campo);
        }

        datos.push_back(fila);
    }

    archivo.close();

    return datos;
}

int main() {
    string nombreArchivo = "test1.csv"; // Nombre del archivo CSV a leer
    char delimitador = ','; // Delimitador utilizado en el archivo CSV

    vector<vector<string>> datos = leerCSV(nombreArchivo, delimitador);

    // Imprimir los datos leídos
    for (const auto& fila : datos) {
        for (const auto& campo : fila) {
            cout << campo << " ";
        }
        cout << endl;
    }

    return 0;
}
