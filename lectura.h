#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void readCSV(string nombre){
  // Create an `ifstream` object to open the file.
  ifstream file(nombre);

  // Read each line of the file.
  string line;

//leyendo el primer elemento
  getline(file,line);cout<<line<<endl;
/*
  while (getline(file, line)) { // lee por linea: line
    // Split the line into a vector of strings using the comma as the delimiter.

        vector<string> values;
        stringstream ss(line);
        string value;
        while (getline(ss, value, ',')) { // accede a cada valor: value
        values.push_back(value);
        //llamarias a la funcion (values, id);
        getline(file,line);cout<<line<<endl;
        }
    
}
 */
/*
ifstream lectura;
lectura.open(nombre,ios::in);

for (std::string linea; std::getline(lectura, linea); )
{
    std::stringstream registro(linea);

    for (std::string dato; std::getline(registro, dato, ';'); )
    {
        std::cout << dato << '\t';
    }
    std::cout << '\n';
}
 */
  // Close the file.
  file.close();



}