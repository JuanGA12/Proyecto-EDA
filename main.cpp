#include <iostream>
#include "Rtree/Rtree.h"


int main() {

    csvReader Lectura;

    auto contenedor = Lectura.leer_Barrios("Barrios.csv",2);

    Rtree Arbol;

    for(int i=0; i < contenedor.size(); i++) Arbol.insert(contenedor[i],i);

    auto searchResult = Arbol.search({-73.86,40.865});

    for(int i = 0; i < Barrios.size();i++){
        cout << i << " " << Barrios[i].Nombre_Barrio << endl;
    }


    if(!searchResult.Nombre_Barrio.empty()){
        cout<<"El punto se encuentra en "<<searchResult.Nombre_Barrio;
    }else cout<<"No se encontró barrio";


    return 0;
}
