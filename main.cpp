#include <iostream>
#include "Rtree/Rtree.h"


int main() {

    csvReader Lectura;

    auto contenedor = Lectura.leer_Barrios("Barrios_Prueba5.csv",2);

    Rtree arbolito;

    for(int i=0; i < contenedor.size(); i++){
        arbolito.insert(contenedor[i],i);

    }/*
    for(auto &i:Barrios){
        cout<<i.Nombre_Barrio<<" ";
    }*/

    auto search = arbolito.search({-73.858419999999995,40.865254999999998});
    cout<<search.Nombre_Barrio;
    cout<<arbolito.PuntoEnPoligono()

    return 0;
}
