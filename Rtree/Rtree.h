#ifndef PROYECTO_EDA_RTREE_H
#define PROYECTO_EDA_RTREE_H

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
                while(!temp->hijos[0]->esHoja){
                    if(temp->Mbr.contains(toInsert)){

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