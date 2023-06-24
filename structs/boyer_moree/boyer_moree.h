#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

const string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789  ";

//generando texto aleatorio
string generarTexto(size_t N){
    string resultado = "";
    for (size_t i = 0; i < N; i++)
        resultado += alfabeto[rand() %  alfabeto.size()];
    return resultado;
}

//test de boyer moore

vector<int> testBoyerMoore(string Texto, string Patron)
{
    auto start = std::chrono::steady_clock::now();
    vector<int> result;
    //para construir la tabla de saltos de manera mas eficiente (sin usar unordered_map) 
    int size_text = Texto.size();
    int size_patron = Patron.size();
    int positions[256];
    for (int i = 0; i < 256; i++)
        positions[i] = -1;

    for (int i = 0; i < size_patron; i++)
        positions[Patron[i]] = i;

    for (int i = 0; i < size_text - size_patron;)
    {
        int j = size_patron - 1;//para ir al ultimo caracter del patron
        while (j >= 0 && Patron[j] == Texto[i + j])
            j--;
        if (j > 0){

            i = i + (j - positions[Texto[i + j]]); 
           // cout << "i: " << i << endl;//esta linea es la que hace que el algoritmo sea mas eficiente
        }
        else
        {
            result.push_back(i);
            i = i + size_patron;
            //cout<<"a"<<"i: "<<i<<endl;
        }
    }

    auto end = std::chrono::steady_clock::now();
    //show the elapsed time
    cout << "BoyerMoore time in nanoseconds: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << " ns" << endl;
    return result;


}

/*
int main(){
    string texto = "holaholahol";
    string patron = "hola";
    vector<int> result = testBoyerMoore(texto,patron);
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    cout << endl;
    return 0;
}

*/