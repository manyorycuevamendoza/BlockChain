#ifndef BOYER_MOREE_H
#define BOYER_MOREE_H
#include <iostream>
#include <algorithm>
#include "../circular_array/circular_array.h"
using namespace std;


void CoincidenciaSufijoCompleto(int Cambio_array[], int arrayBorde[], string patron)
{
    int tamPatron = patron.size();
    int i = tamPatron;
    int j = tamPatron + 1;
    arrayBorde[i] = j;

    while (i > 0)
    {
        while (j <= tamPatron && patron[i - 1] != patron[j - 1])
        {
            if (Cambio_array[j] == 0)
                Cambio_array[j] = j - i;
            j = arrayBorde[j];
        }
        i--;
        j--;
        arrayBorde[i] = j;
    }
}

void CoincidenciaSufijoParcial(int Cambio_array[], int arrayBorde[], string patron)
{
    int tamPatron = patron.size();
    int j;
    j = arrayBorde[0];

    for (int i = 0; i < tamPatron; i++)
    {
        if (Cambio_array[i] == 0)
            Cambio_array[i] = j;
        if (i == j)
            j = arrayBorde[j];
    }
}

void BuscarPatron(string cadenaPrincipal, string patron, CircularArray<int> &array, int *index)
{
    int tamPatron = patron.size();
    int tamCadena = cadenaPrincipal.size();
    int arrayBorde[tamPatron + 1];
    int Cambio_array[tamPatron + 1];

    for (int i = 0; i <= tamPatron; i++)
    {
        Cambio_array[i] = 0;
    }

    CoincidenciaSufijoCompleto(Cambio_array, arrayBorde, patron);
    CoincidenciaSufijoParcial(Cambio_array, arrayBorde, patron);

    int Cambio = 0;
    int  punto =0;
    int contador=-1;
//el array debe evaluar el punto donde pasa y tomarlo como un indice
    while (Cambio <= (tamCadena - tamPatron)){
        int j = tamPatron - 1;
        
        for (int i = 0; i < tamPatron; i++){
            if (cadenaPrincipal[Cambio + i] == '.'){
                contador++;
            }
        }
        //verificar si el patron y la cadena principal son iguales
        while (j >= 0 && patron[j] == cadenaPrincipal[Cambio + j]){j--;punto=contador;}
        if (j < 0){
            (*index)++;
            if(array.find(punto/2)==false){
                array.push_back(punto/2);
                //para aproximar el punto al momento de dividirlo usamos la funcion floor
            }
            Cambio += Cambio_array[0];
        }
        else{
            Cambio += Cambio_array[j + 1];
        }
    }
}

std::string eliminarContenidoDespuesDelPunto(std::string cadena, int puntoInicio) {
    int contadorPuntos = 0;
    size_t indice = 0;

    // Buscar el punto de inicio
    while (contadorPuntos <= puntoInicio && indice < cadena.size()) {
        if (cadena[indice] == '.') {
            contadorPuntos++;
        }
        indice++;
    }

    // Buscar el siguiente punto
    size_t siguientePunto = cadena.find('.', indice);
    if (siguientePunto == std::string::npos) {
        siguientePunto = cadena.size();
    }

    // Eliminar el contenido entre los puntos
    cadena.erase(indice, siguientePunto - indice +1);

    return cadena;
}
std::string AgregarDespuesDelPunto(const std::string& cadena, int puntoInicio, std::string contenidoAgregar) {
    int contadorPuntos = 0;
    size_t indice = 0;
    std::string resultado;
    for(auto &item:contenidoAgregar){
        item=tolower(item);
    }
    // Buscar el punto de inicio
    while (contadorPuntos <= puntoInicio && indice < cadena.size()) {
        resultado += cadena[indice];
        if (cadena[indice] == '.') {
            contadorPuntos++;
        }
        indice++;
    }

    // Agregar el contenido después del punto de inicio
    resultado += contenidoAgregar;

    // Copiar el resto de la cadena desde el índice actual
    resultado += cadena.substr(indice);

    return resultado;
}

#endif

int main(){
    
}
