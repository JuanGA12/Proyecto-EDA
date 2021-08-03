#ifndef PROYECTO_EDA_RTREE_H
#define PROYECTO_EDA_RTREE_H
#include <math.h>
#include <stack>
#include <algorithm>
#include "../Reader/csvReader.h"

class Rtree {
private:
    Node* root;

    //https://www.eecs.umich.edu/courses/eecs380/HANDOUTS/PROJ2/InsidePoly.html
    bool PuntoEnPoligono(vector<pair<double,double>> poligono, pair<double,double> p){
        int i;
        double angle=0;
        pair<double,double> p1;
        pair<double,double> p2;
        for (i=0;i<poligono.size();i++) {
            p1.first = poligono[i].first - p.first; //X
            p1.second = poligono[i].second - p.second;//Y
            p2.first = poligono[(i+1)%poligono.size()].first - p.first;
            p2.second = poligono[(i+1)%poligono.size()].second - p.second;
            angle += Angle2D(p1.first,p1.second,p2.first,p2.second);
        }
        if (abs(angle) < (atan(1)*4))
            return false;
        else
            return true;
    }

    double Angle2D(double x1, double y1, double x2, double y2){
        double dtheta,theta1,theta2;
        theta1 = atan2(y1,x1);
        theta2 = atan2(y2,x2);
        dtheta = theta2 - theta1;
        while (dtheta > atan(1)*4)
            dtheta -= ((atan(1)*4)+(atan(1)*4));
        while (dtheta < -(atan(1)*4))
            dtheta += ((atan(1)*4)+(atan(1)*4));
        return(dtheta);
    }

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

    void split_and_balance(Node* toSplit, Node* toInsert)
    {
        vector <Node*> nodos_a_splitear;
        for(int i = 0; i < toSplit->cantidad_hijos; i++)
        {
            nodos_a_splitear.push_back(toSplit->hijos[i]);
        }
        nodos_a_splitear.push_back(toInsert);

        auto extremos = getExtremos(nodos_a_splitear);

        auto Node1 = new Node();
        Node1->hijos[Node1->cantidad_hijos] = nodos_a_splitear[extremos.first];
        Node1->cantidad_hijos++;
        Node1->Mbr = nodos_a_splitear[extremos.first]->Mbr;
        Node1->padre = toSplit->padre;

        auto Node2 = new Node();
        Node2->hijos[Node2->cantidad_hijos] = nodos_a_splitear[extremos.second];
        Node2->cantidad_hijos++;
        Node2->Mbr = nodos_a_splitear[extremos.second]->Mbr;
        Node2->padre = toSplit->padre;

        for(int i = 0; i < nodos_a_splitear.size(); i++)
        {
            if(i == extremos.first or i == extremos.second )
                continue;
            if(DistanciaEntreMBRs(nodos_a_splitear[i]->Mbr, nodos_a_splitear[extremos.first]->Mbr) <=  DistanciaEntreMBRs(nodos_a_splitear[i]->Mbr, nodos_a_splitear[extremos.second]->Mbr))
            {
                Node1->hijos[Node1->cantidad_hijos] = nodos_a_splitear[i];
                Node1->cantidad_hijos++;
                nodos_a_splitear[i]->padre = Node1;
                if(!Node1->Mbr.contains(nodos_a_splitear[i]->Mbr))
                {
                    auto newMBR = MBR(2);
                    newMBR.MBRresultante(Node1->Mbr, nodos_a_splitear[i]->Mbr);
                    Node1->Mbr = newMBR;
                }
            }
            else
            {
                Node2->hijos[Node2->cantidad_hijos] = nodos_a_splitear[i];
                Node2->cantidad_hijos++;
                nodos_a_splitear[i]->padre = Node2;
                if(!Node2->Mbr.contains(nodos_a_splitear[i]->Mbr))
                {
                    auto newMBR = MBR(2);
                    newMBR.MBRresultante(Node2->Mbr, nodos_a_splitear[i]->Mbr);
                    Node2->Mbr = newMBR;
                }
            }
        }

        if(!toSplit->padre)
        {
            auto newRoot = new Node;
            newRoot->hijos[newRoot->cantidad_hijos] = Node1;
            newRoot->cantidad_hijos++;
            newRoot->hijos[newRoot->cantidad_hijos] = Node2;
            newRoot->cantidad_hijos++;

            auto newMBR = MBR(2);
            newMBR.MBRresultante(Node1->Mbr, Node2->Mbr);
            newRoot->Mbr = newMBR;

            Node1->padre = newRoot;
            Node2->padre = newRoot;
            root = newRoot;
            return;
        }
        else
        {
            for(int i = 0; i < toSplit->padre->cantidad_hijos; i++)
            {
                if(toSplit->padre->hijos[i] == toSplit)
                {
                    toSplit->padre->hijos[i] = Node1;
                    break;
                }
            }
            if(toSplit->padre->cantidad_hijos < capacidad_nodo)
            {
                toSplit->padre->hijos[toSplit->padre->cantidad_hijos] = Node2;
                toSplit->padre->cantidad_hijos++;
                return;
            }
            else
            {
                split_and_balance(Node1->padre, Node2);
            }
        }
    }

    pair <int, int> getExtremos(vector<Node*> nodos)
    {
        pair<double, pair<int, int>> max_dist = make_pair(-1,make_pair(-1,-1));
        for(int i = 0; i < nodos.size(); i++)
        {
            for(int j = 0; j < nodos.size(); j++)
            {
                if(i == j)
                    continue;
                double distancia = DistanciaEntreMBRs(nodos[i]->Mbr, nodos[j]->Mbr);
                if(distancia > max_dist.first)
                {
                    max_dist = make_pair(distancia, make_pair(i,j));
                }
            }
        }
        return max_dist.second;
    }

public:
    Rtree() : root(nullptr){};

    void insert(MBR &toInsert, int index){
        auto newNode = new Node();
        newNode->Mbr = toInsert;
        newNode->referencia_barrio = index;
        newNode->esHoja = true;
        if(!root){
            root = newNode;
            return;
        }else{
            if(root->esHoja){//Cuando el root es hoja y se inserta otro elemento
                auto newMBR = MBR(2);
                newMBR.MBRresultante(toInsert,root->Mbr);
                auto parent = new Node();
                parent->Mbr = newMBR;

                parent->hijos[parent->cantidad_hijos] = root;
                parent->cantidad_hijos++;
                parent->hijos[parent->cantidad_hijos] = newNode;
                parent->cantidad_hijos++;

                root->padre = parent;
                newNode->padre = parent;

                root = parent;
                return;
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
                            return;
                        }
                        else
                        {
                            split_and_balance(root,newNode);
                            return;
                        }
                    }
                    else
                    {
                        auto newMBR = MBR(2);
                        newMBR.MBRresultante(root->Mbr,toInsert);
                        root->Mbr = newMBR;
                        if(root->cantidad_hijos < capacidad_nodo)
                        {
                            newNode->padre = root;
                            root->hijos[root->cantidad_hijos] = newNode;
                            root->cantidad_hijos++;
                            return;
                        }
                        else
                        {
                            split_and_balance(root,newNode);
                            //SPLIT CON CHOCOLATE DOBLE
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
                        return;
                    }
                    else
                    {
                        split_and_balance(temp,newNode);
                    }
                }
                else
                {
                    if(temp->cantidad_hijos < capacidad_nodo)
                    {
                        newNode->padre = temp;
                        temp->hijos[temp->cantidad_hijos] = newNode;
                        temp->cantidad_hijos++;

                        while(temp && !(temp->Mbr.contains(toInsert)) )
                        {
                            auto newMBR = MBR(2);
                            newMBR.MBRresultante(temp->Mbr,toInsert);
                            temp->Mbr = newMBR;
                            temp = temp->padre;
                        }
                    }
                    else
                    {
                        auto aux = temp;
                        while(aux && !(aux->Mbr.contains(toInsert)) )
                        {
                            auto newMBR = MBR(2);
                            newMBR.MBRresultante(aux->Mbr,toInsert);
                            aux->Mbr = newMBR;
                            aux = aux->padre;
                        }
                        split_and_balance(temp,newNode);
                        //SPLIT CON CHOCOLATE DOBLE
                    }
                }
            }
        }
    }

    Barrio search(pair<double,double> point){

        auto mbr = MBR(2);
        mbr.Generar_MBR({{point.first,point.second}});

        auto fail = Barrio();
        stack<Node*> posibles;
        posibles.push(root);
        if(root->Mbr.contains(mbr)){
            for(;!posibles.empty();){
                auto temp = posibles.top();
                posibles.pop();
                if(!temp->esHoja){
                    for(int i = 0 ; i < temp->cantidad_hijos; i++){
                        if(temp->hijos[i]->Mbr.contains(mbr)) {
                            posibles.push(temp->hijos[i]);
                        }
                    }
                }else{
                    auto barrio = Barrios[temp->referencia_barrio];
                    if(PuntoEnPoligono(barrio.vertices,point)){
                        return barrio;
                    }
                }
            }
        }
        return fail;
    }


};
#endif //PROYECTO_EDA_RTREE_H