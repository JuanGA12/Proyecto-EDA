#ifndef PROYECTO_EDA_NODE_H
#define PROYECTO_EDA_NODE_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

const int capacidad_nodo = 8;

struct MBR {

    vector<pair<double,double>> LimitesCordenadas;
    int CantidadDimensiones;

    //Iniciamos con la cantidad de dimensiones que vamos a utilizar
    MBR() = default;
    MBR(int Cantidad_Dimensiones){
        this->CantidadDimensiones = Cantidad_Dimensiones;
    };

    void Generar_MBR( vector<pair<double,double>> Coordenaditas){

        vector<pair<double,double>> MBR_final;

        for(int i = 0; i < CantidadDimensiones;i++)
        {
            MBR_final.push_back(make_pair(1e7,-(1e7)));
        }
        for(auto i : Coordenaditas)
        {
            if(i.first < MBR_final[0].first)
            {
                MBR_final[0].first = i.first;
            }
            if(i.first > MBR_final[0].second)
            {
                MBR_final[0].second = i.first;
            }

            if(i.second < MBR_final[1].first)
            {
                MBR_final[1].first = i.second;
            }

            if(i.second > MBR_final[1].second)
            {
                MBR_final[1].second = i.second;
            }

        }

        LimitesCordenadas = MBR_final;
    }
};

class Node
{
public:
    MBR Mbr;
    int referencia_barrio;
    Node* padre;
    Node* hijos [capacidad_nodo];
    bool esHoja;

    Node()
    {
        this->Mbr = MBR(2);
        referencia_barrio = -1;
        padre = nullptr;
        for(int i = 0; i < capacidad_nodo; i++)
        {
            hijos[i] = nullptr;
        }
        esHoja = 0;
    }
};

#endif //PROYECTO_EDA_NODE_H
