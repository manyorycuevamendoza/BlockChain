#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void readCSV(string nombre){
  // Create an `ifstream` object to open the file.
  ifstream file(nombre);

  // Read each line of the file.
  string line;

//leyendo el primer elemento
  getline(file,line);cout<<line<<endl;

  while (getline(file, line)) {
    // Split the line into a vector of strings using the comma as the delimiter.

        vector<string> values;
        stringstream ss(line);
        string value;
        while (getline(ss, value, ',')) {
        values.push_back(value);

        getline(file,line);cout<<line<<endl;
        }
    
}

  // Close the file.
  file.close();



}