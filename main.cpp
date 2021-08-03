#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Rtree/Node/Node.h"
#include "Reader/csvReader.h"
#include "Rtree/Rtree.h"






int main() {

    csvReader Lectura;

    auto contenedor = Lectura.leer_Barrios("Barrios_Prueba5.csv",2);

    Rtree arbolito;

    for(int i=0; i < contenedor.size(); i++){
        arbolito.insert(contenedor[i],i);

    }
    cout << "Bot";

    return 0;
}
