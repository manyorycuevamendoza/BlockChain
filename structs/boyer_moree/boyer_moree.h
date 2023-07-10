#ifndef BOYER_MOREE_H
#define BOYER_MOREE_H
#include <iostream>
#include <algorithm>
#include "../circular_array/circular_array.h"
using namespace std;

void BuscarPatron(string cadena, string patron, CircularArray <int>& array){

  // obtenemos su size
  int size_patron = patron.size();
  int size_cadena = cadena.size();  
  int ultimo_punto = -1; // para saber si ya se pasó un punto (y no contarlo dos veces)
  
  int i = size_patron-1; // empezamos evaluando desde ultima posicion
  
  for (int j=0;j<i;j++) if (cadena[j]=='.') ultimo_punto++; // se corrige nro de ultimo punto encontrado
  cout<<"Punto; "<<ultimo_punto<<endl;
  
  while (i!=size_cadena){ // mientras aun se pueda evaluar
    if (cadena[i]=='.') {ultimo_punto++;i++;}
    else if (cadena[i]==patron[size_patron-1]){ // si ambos coinciden
      int ind = 0; // para recorrer patron
      while (ind<size_patron){ // verificamos en orden inverso  
        if (cadena[i-ind]==patron[size_patron-1-ind]) ind++; // se compara igualdad
        else {
          ind=size_patron+1; // se le da un valor que no sea size_patron
        }
      }
      if (ind==size_patron){ // se encontró una coincidencia (se encontró patrón)
        if (!array.find(ultimo_punto)) {
          array.push_back(ultimo_punto);
          cout<<ultimo_punto<<endl;
          i+=(size_patron-1); // se avanza el valor de i
        }
        else i++;
      }
      else i++;
      
    }
    else i++; //sino coinciden, se avanza uno
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
