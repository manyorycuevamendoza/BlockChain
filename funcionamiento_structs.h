
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

time_t pedir_fecha(){
    string dia, mes, anho;
    cout<<"Ingrese fecha-> "; cout<<"Dia: "; cin>>dia; 
    cout<<"Mes: "; cin>>mes; 
    cout<<"Anho: "; cin>>anho; 
    return convertToUnixTimestamp(anho+"-"+mes+"-"+dia);
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
        cout<<"[2]. buscar por "<<atributos[0]<<endl;
        cout<<"[3]. buscar por "<<atributos[1]<<endl;
        cout<<"[4]. buscar por "<<atributos[2]<<endl;
        cout<<"[5]. buscar por "<<atributos[3]<<endl;
        cout<<"[6]. buscar por rango en "<<atributos[2]<<endl;
        cout<<"[7]. buscar por rango en "<<atributos[3]<<endl;
        cout<<"[8]. buscar minimo por "<<atributos[2]<<endl;
        cout<<"[9]. buscar minimo por "<<atributos[3]<<endl;
        cout<<"[10]. buscar maximo por "<<atributos[2]<<endl;
        cout<<"[11]. buscar maximo por "<<atributos[3]<<endl;
        cout<<"[12]. mostrar todos los bloques"<<endl;
        cout<<"[13]. recalculo en cascada"<<endl;
        cin>>alternativa;


   }while (alternativa>0 && 13<alternativa);

    vector<int> res;
    int n1,n2;
    time_t c1, c2;

    switch (alternativa)
   {
   case 1:
        cout<<"hola";
        break;
   case 2:
        cadena_bloques->get_block(string1->search(pedir_string(atributos[0])));
        break;
    case 3:
        cadena_bloques->get_block(string2->search(pedir_string(atributos[1])));
        break;
    case 4:
        cadena_bloques->get_block(numero->search(pedir_entero(atributos[2])));
        break;
    case 5:
        cadena_bloques->get_block(fecha->search(pedir_fecha()));
        break;
        case 6:
            n1 = pedir_entero(atributos[2]+" 1");
           n2 = pedir_entero(atributos[2]+" 2");
        res = avl1->search_by_range(n1,n2);
        cout<<"\tBloques: \n";
        for (auto i:res) cadena_bloques->get_block(i); cout<<"\n"; // cout<<i<<" ";
        break;

    case 7:
        c1 = pedir_fecha();
        c2 = pedir_fecha();
        res=avl2->search_by_range(c1,c2);
        //imprimiendo el vector de tuplas
        cout<<"\tBloques: \n";
        for (auto i:res) cadena_bloques->get_block(i); cout<<"\n"; // cout<<i<<" ";
        break;

    case 8:
        cadena_bloques->get_block(avl1->minValue());
        break;

    case 9:
        cadena_bloques->get_block(avl2->minValue());
        break;

    case 10:
        cadena_bloques->get_block(avl1->maxValue());
        break;

    case 11:
        cadena_bloques->get_block(avl2->maxValue());
        break;

    case 12:
        cadena_bloques->display();
        break;

    case 13:
        cout<<"hola";
        break;

    
    
   }
}


