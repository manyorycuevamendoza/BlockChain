#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <unistd.h>

using namespace std;

const string alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789   ";

string generarTexto(size_t N){
    string resultado = "";
    for (size_t i = 0; i < N; i++)
        resultado += alfabeto[rand() %  alfabeto.size()];
    return resultado;
}

vector<int> testInocente(string Texto, string Patron){
    auto start = std::chrono::steady_clock::now();
    vector<int> result;
    for (int j = 0; j < Texto.size() - Patron.size(); j++)
    {
        //digamos que el patron es "AABA" y mi texto es "AABAACAABAABA"

        int i = 0;
        while (Patron[i] == Texto[j + i] && i < Patron.size())
            i++;
        if (i == Patron.size())
            result.push_back(j);
            
            /*
            ----para j =0--------
            j
            AABAACAABAABA
            AABA
            i

                para (j=0; 0<12-4;j++){// cumple la condicion}
                    i=0;
                    mientras (AABA[0]A==A texto[0+0] && 0<4) //cumple la condicion
                        j
                        T
                        AABAACAABAABA
                        AABA
                        i
                        i++; //i=1
                        AABA
                         i
                    mientras (AABA[1]A==A texto[0+1] && 1<4) //cumple la condicion
                        j
                         T
                        AABAACAABAABA
                        AABA
                         i
                        i++; //i=2
                        AABA
                          i
                    mientras (AABA[2]B==B texto[0+2] && 2<4) //cumple la condicion
                        j
                          T
                        AABAACAABAABA
                        AABA
                          i
                    mientras (AABA[3]A==A texto[0+3] && 3<4) //cumple la condicion
                        j
                           T
                        AABAACAABAABA
                        AABA
                           i
                        i++; //i=4
                        AABA
                            i
                    si (4==4) // cumple la condicion
                        result.push_back(0);
                }

/*######################################################

En conclución el algoritmo inocente es de orden O(n*m) donde n es el tamaño del texto y m es el tamaño del patron
Se comprende que el primer for es para recorrer el texto-patron 
y el While es para comparar el patron con el texto
                        j
                           T
                        AABAACAABAABA
                        AABA
                           i
                        i++; //i=4
                        AABA
                            i
El T es como si fuera i ya que va comparando uno a uno el patron con el texto
y el if es para ver ya se termino de recorrer el patron y si es asi se agrega el indice al vector result


#######################################################*/
    }

    auto end = std::chrono::steady_clock::now();
    //show the elapsed time
    cout << "Inocente time in nanoseconds: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << " ns" << endl;
    return result;
}




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
            cout<<"i: "<<i<<endl; //i=4
            cout<<"j: "<<j<<endl; //j=2
            i = i + (j - positions[Texto[i + j]]); 
            cout << "i: " << i << endl;//esta linea es la que hace que el algoritmo sea mas eficiente
        }
        else
        {
            result.push_back(i);
            i = i + size_patron;
            cout<<"a"<<"i: "<<i<<endl;
        }
    }

    /*

    Patron= "AABA"
    Texto = "AABAACAABAABA"
    tamaño del texto = 12
    tamaño del patron = 4
    //creamos un array de 256 posiciones para guaradar las posiciones de los caracteres del patron
    array posiciones con tamaño 256;


###########llena el array de todas las posiciones con -1 ################
    para i=0; 0<256; i++{
        el i estara recorriendo desde el 1 hasta el 256 
        y todas esas pocisiones
        las inicializamos en -1
        }
###########Recorre el patron y guarda las posiciones de los caracteres en el array ################
    para i=0; i<4; i++{
        Patron[0]=A
        en el array de pocisiones [en la pocision del caracter del patron [0] ] = 0 ;
        en el array de pocisiones [A] = 0 ; //la pocision del caracter A es 0
        }
########## 
    ----para i=0-----
    para i=0; 0< 12-4{
        j=4-1=3 //para ir al ultimo caracter del patron
        //mientras no se termine de recorrer de recoorrer el arreglo y los caracteres del patron sea igual al texto
        mientras (3>=0 && AABA[3]A==A texto[0+3] ) //cumple la condicion
               T
            AABAACAABAABA
            AABA
               j
            j--; //j=2
            AABA
              j
        mientras (2>=0 && AABA[2]B==B texto[0+2] ) //cumple la condicion
            
              T
            AABAACAABAABA
            AABA
              j
            j--; //j=1
            AABA
             j
        mientras (1>=0 && AABA[1]A==A texto[0+1] ) //cumple la condicion
            j
             T
            AABAACAABAABA
            AABA
             j
            j--; //j=0
            AABA
            j
        mientras (0>=0 && AABA[0]A==A texto[0+0] ) //cumple la condicion
            j
            T
            AABAACAABAABA
            AABA
            j
            j--; //j=-1
            AABA
           j
        ahora j=-1 y ya no cumple la condicion
        si (j>0) // no cumple la condicion
        sino
            result.push_back(i); // result.push_back(0);
            i = i + size_patron; // i = 0 + 4 = 4
        }
        -----------------para i=4-----------------
        para i=4; 4< 12-4{
        j=4-1=3
        mientras (3>=0 && AABA[3]A==A texto[4+3] ) //cumple la condicion
            j
                  T
            AABAACAABAABA
                AABA
                   j
            j--; //j=2
            AABA
              j
        mientras (2>=0 && AABA[2]B==C texto[4+2] ) //no cumple la condicion
            j
                 T
            AABAACAABAABA
                AABA
                  j
            j--;  //j no disminuye porque no cumple la condicion
        si (j>0) // cumple la condicion j=2
            i = i + (j - positions[Texto[i + j]]); // i = 4 + (2- posiciones[A]) = 4 + (2- 0) = 6
        #######
        hace que el algoritmo sea mas eficiente, avanza a la siguiente pocision del texto de donde me quede
        recuerda que yo compare el B=C y no son iguales entonces avanzo a la siguiente pocision del texto 
        que es A y como mi patron es de tamaño 4 entonces avanzo 3 pocisiones mas por ello el j=4-1=3
        -----------------para i=7-----------------
        para i=7; 7< 12-4{
        j=4-1=3
        mientras (3>=0 && AABA[3]A==A texto[7+3] ) //cumple la condicion
            j
                        T
            AABAACAABAABA
                AABA
                   j
            j--; //j=2
            AABA
              j
        mientras (2>=0 && AABA[2]B==B texto[7+2] ) //cumple la condicion
            j
                       T
            AABAACAABAABA
                AABA
                  j
            j--; //j=1
            AABA
             j
        mientras (1>=0 && AABA[1]A==A texto[7+1] ) //cumple la condicion
            j
                      T
            AABAACAABAABA
                AABA
                 j
            j--; //j=0
            AABA
            j
        mientras (0>=0 && AABA[0]A==A texto[7+0] ) //cumple la condicion
            j
                     T
            AABAACAABAABA
                AABA
                j
            j--; //j=-1
            AABA
           j
        ahora j=-1 y ya no cumple la condicion
        si (j>0) // no cumple la condicion
        sino
            result.push_back(i); // result.push_back(7);
            i = i + size_patron; // i = 7 + 4 = 11
        }
        

    }

    
    
    
    
    */

    auto end = std::chrono::steady_clock::now();
    //show the elapsed time
    cout << "BoyerMoore time in nanoseconds: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << " ns" << endl;
    return result;
}

void verificarResultado(vector<int> result1, vector<int> result2)
{
    if(result1.size() != result2.size())
        cerr <<"Error!! el resultado no es el mismo\n";
    for(int i=0;i<(int)result1.size();i++){
        if(result1[i] != result2[i]) {
            cerr <<"Error!! el resultado no es el mismo\n";
            break;
        }
    }
}

int main(){
    srand(time(NULL));
    size_t N = 100;//100,1000,10000,100000,1000000
    int m = 10;
    //string Texto = generarTexto(N);
    //string Patron = generarTexto(m);
    string Texto = "AABAACAABAABA";//GCGATGCCTA
    string Patron = "AABA";//TATATG


    vector<int> result1 = testInocente(Texto, Patron);
    vector<int> result2 = testBoyerMoore(Texto, Patron);

    verificarResultado(result1, result2);

    //imprimiendo los resultados
    cout << "Inocente: ";
    for (auto x : result1)
        cout << x << " ";
    cout << endl;
    cout << "BoyerMoore: ";
    for (auto x : result2)
        cout << x << " ";
    cout << endl;

    return 0;
}

//comparamos el tiempo de ejecución de los dos algoritmos con graficos

