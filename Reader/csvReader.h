#ifndef PROYECTO_EDA_CSVREADER_H
#define PROYECTO_EDA_CSVREADER_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "../Rtree/Node/Node.h"

using namespace std;


class Barrio
{
public:
    string Nombre_Barrio;
    vector<pair<double,double>> vertices;
    Barrio() : Nombre_Barrio("") {}
};

vector <Barrio> Barrios;

class csvReader {

public:

    vector<MBR> leer_Barrios(string nombre_archivo, int NumeroDimensiones){

        ifstream archivo(nombre_archivo);
        string linea;
        char delimitador = ';';

        vector<MBR> ContenedorMBRs;

        // Leemos la primer línea para descartarla, pues es el encabezado
        getline(archivo, linea);

        // Leemos todas las líneas
        while (getline(archivo, linea))
        {
            Barrio barrio;
            stringstream stream(linea); // Convertir la cadena a un stream
            string neighborhood,borough,coordinates;

            // Extraer todos los valores de esa fila
            getline(stream, neighborhood, delimitador);
            getline(stream, borough, delimitador);
            getline(stream, coordinates, delimitador);

            barrio.Nombre_Barrio = neighborhood;

            stringstream stream1(coordinates);
            vector<pair<double, double>> Cordenaditas;
            MBR mbr(NumeroDimensiones);
            for (int i = 0; i < coordinates.size();) {

                string cor1, cor2;

                getline(stream1, cor1, ',');
                i += int(cor1.size()) + 1;
                getline(stream1, cor2, '/');
                i += int(cor2.size())+ 1;

                Cordenaditas.push_back({stod(cor1),stod(cor2)});
            }
            barrio.vertices = Cordenaditas;
            mbr.Generar_MBR(Cordenaditas);
            ContenedorMBRs.push_back(mbr);
            Barrios.push_back(barrio);
        }
        archivo.close();
        return ContenedorMBRs;
    };





    void leer_taxis(string nombre_archivo){


        ifstream archivo(nombre_archivo);
        string linea;
        char delimitador = ';';

        // Leemos la primer línea para descartarla, pues es el encabezado
        getline(archivo, linea);

        // Leemos todas las líneas
        while (getline(archivo, linea))
        {


            stringstream stream(linea); // Convertir la cadena a un stream
            string VendorID, lpep_pickup_datetime, Lpep_dropoff_datetime, Store_and_fwd_flag, RateCodeID, Pickup_longitude, Pickup_latitude,
                    Dropoff_longitude, Dropoff_latitude, Passenger_count, Trip_distance, Fare_amount, Extra, MTA_tax,
                    Tip_amount, Tolls_amount, Ehail_fee, improvement_surcharge, Total_amount, Payment_type, Trip_type,Column1,_1;

            // Extraer todos los valores de esa fila
            getline(stream, VendorID, delimitador);
            getline(stream, lpep_pickup_datetime, delimitador);
            getline(stream, Lpep_dropoff_datetime, delimitador);
            getline(stream, Store_and_fwd_flag, delimitador);
            getline(stream, RateCodeID, delimitador);
            getline(stream, Pickup_longitude, delimitador);
            getline(stream, Pickup_latitude, delimitador);

            getline(stream, Dropoff_longitude, delimitador);
            getline(stream, Dropoff_latitude, delimitador);
            getline(stream, Passenger_count, delimitador);
            getline(stream, Trip_distance, delimitador);
            getline(stream, Fare_amount, delimitador);
            getline(stream, Extra, delimitador);
            getline(stream, MTA_tax, delimitador);

            getline(stream, Tip_amount, delimitador);
            getline(stream, Tolls_amount, delimitador);
            getline(stream, Ehail_fee, delimitador);
            getline(stream, improvement_surcharge, delimitador);
            getline(stream, Total_amount, delimitador);
            getline(stream, Payment_type, delimitador);
            getline(stream, Trip_type, delimitador);
            getline(stream, Column1, delimitador);
            getline(stream, _1, delimitador);


            // Imprimir
            cout << "==================" << endl;
            cout << "VendorID: " << VendorID << endl;
            cout << "lpep_pickup_datetime: " << lpep_pickup_datetime << endl;
            cout << "Lpep_dropoff_datetime: " << Lpep_dropoff_datetime << endl;
            cout << "Store_and_fwd_flag: " << Store_and_fwd_flag << endl;
            cout << "RateCodeID: " << RateCodeID << endl;
            cout << "Pickup_longitude: " << Pickup_longitude << endl;
            cout << "Pickup_latitude: " << Pickup_latitude << endl;

            cout << "Dropoff_longitude: " << Dropoff_longitude << endl;
            cout << "Dropoff_latitude: " << Dropoff_latitude << endl;
            cout << "Passenger_count: " << Passenger_count << endl;
            cout << "Trip_distance: " << Trip_distance << endl;
            cout << "Fare_amount: " << Fare_amount << endl;
            cout << "Extra: " << Extra << endl;
            cout << "MTA_tax: " << MTA_tax << endl;

            cout << "Tip_amount: " << Tip_amount << endl;
            cout << "Tolls_amount: " << Tolls_amount << endl;
            cout << "Ehail_fee: " << Ehail_fee << endl;
            cout << "improvement_surcharge: " << improvement_surcharge << endl;
            cout << "Total_amount: " << Total_amount << endl;
            cout << "Payment_type: " << Payment_type << endl;
            cout << "Trip_type: " << Trip_type << endl;
            cout << "Column1: " << Column1 << endl;
            cout << "_1: " << _1 << endl;

        }

        archivo.close();

    };

};

#endif //PROYECTO_EDA_CSVREADER_H
