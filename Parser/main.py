import json
import pandas as pd

def leer_json():
    Datos = []

    with open("NYCNeighborhoods.json") as file: 
        data = json.load(file)
        NumeroCor=""
        for i in data['features']:
            DatosB = []
            prop = i['properties']
            DatosB.append(prop['neighborhood'])
            DatosB.append(prop['borough'])
            geo = i['geometry']
            for j in geo['coordinates'][0]:
                cor1 = str(round(j[0],5))
                cor2 = str(round(j[1],5))
                NumeroCor = NumeroCor + cor1 + ',' + cor2 + '/'
                
            #NumeroCor = NumeroCor[:-1]
            DatosB.append(NumeroCor)
            NumeroCor=""
            Datos.append(DatosB)
    excel = pd.DataFrame(Datos,
                            columns=['neighborhood','borough','coordinates'])

    excel.to_csv('Barrios.csv',index=False,sep=';')

leer_json()