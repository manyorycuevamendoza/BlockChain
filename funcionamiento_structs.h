
#include "criterios_busqueda.h"
void console();

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
    string archivo = "test2.csv";
    readCSV(archivo,atributos,cadena_bloques,avl1,avl2, string1, string2, numero, fecha); // creando estructuras
    console();
}

long long pedir_fecha(){
    int dia, mes, anho;
    cout<<"Ingrese fecha-> "; cout<<"Dia: "; cin>>dia; 
    cout<<"Mes: "; cin>>mes; 
    cout<<"Anho: "; cin>>anho; 
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
   int alternativa;
   do{
        cout<<"[1]. agregar registro"<<endl; 
        cout<<"[2]. buscar por atributo al emisor "<<endl;
        cout<<"[3]. buscar por atributo al receptor "<<endl;
        cout<<"[4]. buscar por atributo al monto "<<endl;
        cout<<"[5]. buscar por atributo al fecha "<<endl;
        cout<<"[6]. buscar por rango en monto"<<endl;
        cout<<"[7]. buscar por rango en fecha"<<endl;
        cout<<"[8]. buscar minimo por atributo de monto"<<endl;
        cout<<"[9]. buscar minimo por atributo de fecha"<<endl;
        cout<<"[10]. buscar maximo por atributo de monto"<<endl;
        cout<<"[11]. buscar maximo por atributo de fecha"<<endl;
        cout<<"[12]. mostrar todos los bloques (blockchain->print(huellas))"<<endl;
        cout<<"[13]. recalculo en cascada"<<endl;
        cin>>alternativa;


   }while (alternativa>0 && 13<alternativa);

    vector<int> res;

    switch (alternativa)
   {
   case 1:
        cout<<"hola";
        break;
   case 2:
        cout<<string1->search(pedir_string(atributos[0]));
        break;
    case 3:
        cout<<string2->search(pedir_string(atributos[1]));
        break;
    case 4:
        cout<<numero->search(pedir_entero(atributos[2]));
        break;
    case 5:
        cout<<fecha->search(pedir_fecha());
        break;
    case 6:
        //vector<int> res;
        res = avl1->search_by_range(pedir_entero(atributos[2]),pedir_entero(atributos[2]));
        
        cout<<"Bloques: ";
        for (auto i:res) cout<<i<<" ";
        cout<<endl;

        break;

    case 7:
        //vector<int> result2;
        res=avl2->search_by_range(pedir_fecha(),pedir_fecha());
        //imprimiendo el vector de tuplas
        cout<<"Valores: ";
        for (long long i:res) cout<<i<<" ";
        cout<<endl;

        break;

    case 8:
        cout<<avl1->minValue();
        break;

    case 9:
        cout<<avl2->minValue();
        break;

    case 10:
        cout<<avl1->maxValue();
        break;

    case 11:
        cout<<avl2->maxValue();
        break;

    case 12:
        cadena_bloques->display();
        break;

    case 13:
        cout<<"hola";
        break;

    
    
   }
}


