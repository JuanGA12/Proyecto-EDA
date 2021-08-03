#ifndef PROYECTO_EDA_NODE_H
#define PROYECTO_EDA_NODE_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
const int capacidad_nodo = 8;


struct MBR {

    vector<pair<double,double>> LimitesCoordenadas;
    int CantidadDimensiones;
    vector<double> puntoMedio;
    bool contains(MBR &child){
        bool con = true;
        for(int i = 0; i < CantidadDimensiones; i++){
            if(LimitesCoordenadas[i].first > child.LimitesCoordenadas[i].first){
                con = false;
            }
            if(LimitesCoordenadas[i].second < child.LimitesCoordenadas[i].second){
                con = false;
            }
        }
        return con;
    }

    //Iniciamos con la cantidad de dimensiones que vamos a utilizar
    MBR() = default;
    MBR(int Cantidad_Dimensiones){
        this->CantidadDimensiones = Cantidad_Dimensiones;
    };

    void Generar_MBR( vector<pair<double,double>> Coordenaditas){

        vector<pair<double,double>> MBR_final;

        for(int i = 0; i < CantidadDimensiones;i++){

            MBR_final.push_back(make_pair(1e7,-(1e7)));
        }
        for(auto i : Coordenaditas){

            if(i.first < MBR_final[0].first) MBR_final[0].first = i.first;
            if(i.first > MBR_final[0].second) MBR_final[0].second = i.first;
            if(i.second < MBR_final[1].first) MBR_final[1].first = i.second;
            if(i.second > MBR_final[1].second) MBR_final[1].second = i.second;
        }

        LimitesCoordenadas = MBR_final;

        for (int i = 0; i < CantidadDimensiones; i++){
            double puntoMedio_ = (LimitesCoordenadas[i].first + LimitesCoordenadas[i].second)/2;
            puntoMedio.push_back(puntoMedio_);
        }

    }



    void MBRresultante(MBR mbr1, MBR mbr2 ){
        vector<pair<double,double>> newMBR;
        for(int i = 0; i < CantidadDimensiones; i++){
            double mbr_min = min(mbr1.LimitesCoordenadas[i].first, mbr2.LimitesCoordenadas[i].first);
            double mbr_max = max(mbr1.LimitesCoordenadas[i].second, mbr2.LimitesCoordenadas[i].second);
            newMBR.push_back({mbr_min,mbr_max});
        }
        LimitesCoordenadas = newMBR;
        for (int i = 0; i < CantidadDimensiones; i++){
            double puntoMedio_ = (LimitesCoordenadas[i].first + LimitesCoordenadas[i].second)/2;
            puntoMedio.push_back(puntoMedio_);
        }
    }
};

class Node
{
public:
    MBR Mbr;
    int referencia_barrio;
    Node* padre;
    Node* hijos [capacidad_nodo];
    int cantidad_hijos;
    bool esHoja;

    Node()
    {
        this->Mbr = MBR(2);
        referencia_barrio = -1;
        padre = nullptr;
        cantidad_hijos = 0;
        for(int i = 0; i < capacidad_nodo; i++)
        {
            hijos[i] = nullptr;
        }
        esHoja = 0;
    }

};
#endif //PROYECTO_EDA_NODE_H
