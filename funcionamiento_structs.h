#include "criterios_busqueda.h"
const int columnas = 4;
string* atributos = new string [columnas]; // atributos de cada bloque
BlockChain<string>* cadena_bloques = new BlockChain<string>(atributos,columnas); // blockchain

//arboles
AVLTree2<int,int>* avl1 = new AVLTree2<int,int>(); // id monto
AVLTree2<int,long>* avl2 = new AVLTree2<int,long>(); //id fechas

//table_hash
ChainHash<string,int>* string1 = new ChainHash<string,int>(); //primer string
ChainHash<string,int>* string2 = new ChainHash<string,int>(); //segundo string
ChainHash<int,int>* numero = new ChainHash<int,int>(); //para monto id/monto
ChainHash<long,int>* fecha = new ChainHash<long,int>(); //para fecha/id>

void begin(){
    string archivo = "test1.csv";
    readCSV(archivo,atributos,avl1,avl2, string1, string2, numero, fecha); // creando estructuras
    cadena_bloques->insert_string("a","af","a","Afvg");

    for (int i=0; i<4;i++) cout<<atributos[i]<<" ";
    
        /*
    cout<<search(numero, 100)<<endl;
    string f = "Mallory";
    cout<<search(string1, f);
     cout<<min_value(avl1); // minimo
    */
    long a=convertToUnixTimestamp("2002-01-01");
    long  b=convertToUnixTimestamp("2003-01-01");
    cout<<avl2->size()<<endl;
    vector <int> res = range_search(avl2, a,b);
    for (auto x:res) cout<<x<<" ";
    // la consola debe llamar a las funciones y retornar info sobre el bloque(con get_block)
}

long long pedir_fecha(){
    int dia, mes, anho;
    cout<<"Ingrese fecha-> "; cout<<"Dia: "; cin>>dia;
    return convertToUnixTimestamp((anho)+"-"+to_string(mes)+"-"+to_string(dia));
}

string pedir_string(string atributo){
    cout<<"Ingrese "<<atributo<<": ";
    string atr; cin>>atr;
    return atr;
}

int pedir_entero(string atributo){
    cout<<"Ingrese "<<atributo<<": "; int num; cin>>num; return num;
}

void console(){
    /*funciones : 
        1. agregar registro, 
        2. buscar por atributo[0] // cout<<"Buscar por "<<atributo[0];
        3. buscar por atributo[1]
        4. buscar por atributo[2]
        5. buscar por atributo[3]
        6. buscar por rango en atributo[2] // monto 
        7. buscar por rango en atributo[3] // fecha
        8. buscar minimo por atributo[2] // monto 
        9. buscar minimo por atributo[3]// fecha
        10. buscar maximo por atributo[2]// monto 
        11. buscar maximo por atributo[3]// fecha
        12. mostrar todos los bloques (blockchain->print(huellas))
        13. recalculo en cascada
    */
}

