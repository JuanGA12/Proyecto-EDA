#ifndef PROYECTO_EDA_RTREE_H
#define PROYECTO_EDA_RTREE_H
#include <math.h>
#include <algorithm>
#include "Node/Node.h"

class Rtree {
private:
    Node* root;
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
                newMBR.getMBR(toInsert,root->Mbr);
                auto parent = new Node();
                parent->Mbr = newMBR;

                parent->hijos[0] = root;
                parent->hijos[1] = newNode;

                parent->hijos[0]->padre = parent;
                parent->hijos[1]->padre = parent;

                root = parent;
                return true;
            }else{//iterar hasta el padre de las hojas y hacer comparaciones
                auto temp = root;
                vector<Node*> Padres;

                while(!temp->hijos[0]->esHoja){

                    for(auto it : temp->hijos){
                        if(it){
                            if(it->Mbr.contains(toInsert)){
                                Padres.push_back(it);
                            }
                        }
                    }
                    //Caso 1
                    if(Padres.size() > 1) {
                        //Preguntas si puedo meterlo en el padre
                        vector<pair<double, int>> distancias;
                        for (int i = 0; i < Padres.size(); i++) {
                            double distancia = 0;

                            for (int j = 0; j < Padres[i]->Mbr.CantidadDimensiones; j++) {

                                distancia += pow((Padres[i]->Mbr.puntoMedio[i] - toInsert.puntoMedio[i]), 2);

                            }

                            distancia = sqrt(distancia);
                            distancias.push_back(make_pair(distancia, i));
                        }

                        sort(distancias.begin(), distancias.end());

                        temp = Padres[distancias[0].second];
                    //Caso 2
                    if(Padres.size() == 1) {
                        //Preguntas si lo puedo meter en el padre
                        temp = Padres[0];
                    }

                    //Caso 3
                    if(Padres.empty()){
                        //Preguntas si lo puedo meter en el padre




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