#ifndef PROYECTO_EDA_RTREE_H
#define PROYECTO_EDA_RTREE_H
#include <math.h>
#include <algorithm>
#include "Node/Node.h"

class Rtree {
private:
    Node* root;

    double DistanciaEntreMBRs(MBR r1, MBR r2)
    {
        double distancia = 0;

        for (int j = 0; j < r1.CantidadDimensiones; j++)
        {
            distancia += pow((r1.puntoMedio[j] - r2.puntoMedio[j]), 2);
        }

        distancia = sqrt(distancia);
        return distancia;
    }
public:
    Rtree() : root(nullptr){};

    bool insert(MBR &toInsert, int index){
        auto newNode = new Node();
        newNode->Mbr = toInsert;
        newNode->referencia_barrio = index;
        newNode->esHoja = true;
        if(!root){
            root = newNode;
            return true;
        }else{
            if(root->esHoja){//Cuando el root es hoja y se inserta otro elemento
                auto newMBR = MBR(2);
                newMBR.MBRresultante(toInsert,root->Mbr);
                auto parent = new Node();
                parent->Mbr = newMBR;

                parent->hijos[0] = root;
                parent->hijos[1] = newNode;
                parent->cantidad_hijos = 2;

                parent->hijos[0]->padre = parent;
                parent->hijos[1]->padre = parent;

                root = parent;
                return true;
            }else{//iterar hasta el padre de las hojas y hacer comparaciones
                auto temp = root;
                bool Flag_contain = 1;

                while(!temp->hijos[0]->esHoja)
                {
                    vector<Node*> Padres;
                    if(Flag_contain)
                    {
                        for(int i = 0; i < temp->cantidad_hijos; i++){
                            if(temp->hijos[i]->Mbr.contains(toInsert)){
                                Padres.push_back(temp->hijos[i]);
                            }
                        }
                        //Caso 1
                        if(Padres.size() > 1) {
                            //Preguntas si puedo meterlo en el padre
                            vector<pair<double, int>> distancias;
                            for (int i = 0; i < Padres.size(); i++) {
                                distancias.push_back(make_pair(DistanciaEntreMBRs(Padres[i]->Mbr, toInsert), i));
                            }
                            sort(distancias.begin(), distancias.end());

                            temp = Padres[distancias[0].second];
                        }
                        //Caso 2
                        if(Padres.size() == 1) {
                            //Preguntas si lo puedo meter en el padre
                            temp = Padres[0];
                        }
                    }
                    //Caso 3
                    if(Padres.empty()){
                        Flag_contain = 0;
                        vector<pair<double, int>> distancias;
                        for(int i = 0; i < temp->cantidad_hijos; i++)
                        {
                            distancias.push_back(make_pair(DistanciaEntreMBRs(temp->hijos[i]->Mbr, toInsert), i));
                        }
                        sort(distancias.begin(), distancias.end());
                        temp = temp->hijos[distancias[0].second];
                    }

                }
                if(temp == root)
                {
                    if(root->Mbr.contains(toInsert))
                    {
                        if(root->cantidad_hijos < capacidad_nodo)
                        {
                            newNode->padre = root;
                            root->hijos[root->cantidad_hijos] = newNode;
                            root->cantidad_hijos++;
                            return true;
                        }
                        else
                        {
                            //CHOCO
                        }
                    }
                    else
                    {
                        if(root->cantidad_hijos < capacidad_nodo)
                        {
                            newNode->padre = root;
                            root->hijos[root->cantidad_hijos] = newNode;
                            root->cantidad_hijos++;
                            auto newMBR = MBR(2);
                            newMBR.MBRresultante(root->Mbr,toInsert);
                            root->Mbr = newMBR;
                            return true;
                        }
                        else
                        {
                            //CHOCO
                        }
                    }
                }
                if(Flag_contain)
                {
                    if(temp->cantidad_hijos < capacidad_nodo)
                    {
                        newNode->padre = temp;
                        temp->hijos[temp->cantidad_hijos] = newNode;
                        temp->cantidad_hijos++;
                        return true;
                    }
                    else
                    {
                        //SPLIT CON CHOCOLATE
                    }
                }
                else
                {
                    if(temp->cantidad_hijos < capacidad_nodo)
                    {
                        newNode->padre = temp;
                        temp->hijos[temp->cantidad_hijos] = newNode;
                        temp->cantidad_hijos++;

                        while(temp!=nullptr && !(temp->Mbr.contains(toInsert)) )
                        {
                            auto newMBR = MBR(2);
                            newMBR.MBRresultante(temp->Mbr,toInsert);
                            temp->Mbr = newMBR;
                        }
                        return true;
                    }
                    else
                    {
                        //SPLIT CON CHOCOLATE DOBLE
                    }
                }
            }
        }

        return true;
        //Insert nodo hoja
    }

    void split(Node* &toSplit){

    }

};

#endif //PROYECTO_EDA_RTREE_H