from rtree import index
import json
import pandas as pd

idx = index.Index()


def leer_json(Nombre_Archivo):
    df = pd.read_csv(Nombre_Archivo, sep=';')
    #print(df['coordinates'])
    lista = []
    contador = 0
    
    for key in df['coordinates']:
        lista = key.split("/")
        lista.remove("") 
        #print(lista)
        #print(key)
        LimiteMaximoX = -10000000;
        LimiteMinimoX = 1000000;
        LimiteMaximoY = -10000000;
        LimiteMinimoY = 1000000;
        lista2=[]
        for key2 in lista:
            lista2 = key2.split(",")
            Corx = float(lista2[0]) 
            Cory = float(lista2[1])
            if LimiteMaximoX < Corx:
                LimiteMaximoX = Corx
            if LimiteMinimoX > Corx:
                LimiteMinimoX = Corx
            if LimiteMaximoY < Cory:
                LimiteMaximoY = Cory
            if LimiteMinimoY > Cory:
                LimiteMinimoY = Cory

        #print("Indice: ")
        #print(contador)
        #print("-----------------------")
        #print("LimiteMaximoX:")
        #print(LimiteMaximoX)
        #print("-----------------------")
        #print("LimiteMinimoX:")
        #print(LimiteMinimoX)
        #print("-----------------------")
        #print("LimiteMaximoY:")
        #print(LimiteMaximoY)
        #print("-----------------------")
        #print("LimiteMinimoY:")
        #print(LimiteMinimoY)
        #print("-----------------------")

        idx.insert(contador, (LimiteMinimoX, LimiteMinimoY, LimiteMaximoX,LimiteMaximoY ))
        contador= contador + 1

            #print(key2.split(","))
            #print('HOLA')
    
    print(idx)        
    print(list(idx.nearest((-73.98690753704442, 40.68609554690169,-73.98690753704442, 40.68609554690169))))

leer_json("Barrios.csv")

