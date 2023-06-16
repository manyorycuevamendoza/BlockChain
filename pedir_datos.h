#include "criterios_busqueda.h"

//incluir time_t convertToUnixTimestamp(const std::string& date) - de structs/avl :
    // escribir la funcion aqui
time_t pedir_fecha(){
    string dia, mes, anho;
    cout<<"Ingrese fecha-> "; cout<<"Dia: "; cin>>dia; 
    cout<<"Mes: "; cin>>mes; 
    cout<<"Anho: "; cin>>anho; 
    return convertToUnixTimestamp(anho+"-"+mes+"-"+dia);
}

string fecha_string(){
    string dia, mes, anho;
    cout<<"Ingrese fecha-> "; cout<<"Dia: "; cin>>dia;
    if (dia.length()==1) dia = "0"+dia;

    cout<<"Mes: "; cin>>mes;
    if (mes.length()==1) mes = "0"+mes;

    cout<<"Anho: "; cin>>anho;
    return anho+"-"+mes+"-"+dia;
}

string pedir_string(string atributo){
    cout<<"Ingrese "<<atributo<<": ";
    string atr; cin>>atr;
    atr[0] = toupper(atr[0]);
    return atr;
}

int pedir_entero(string atributo){
    cout<<"Ingrese "<<atributo<<": "; int num; cin>>num; return num;
}