#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include "csv-parser/single_include/csv.hpp"
#include "variadic_table/include/VariadicTable.h"

using namespace std;
using namespace csv;

class Airport   
{
public:
    string name;
    float latitude;
    float longitude;

    void add_airport()
    {
        cout << "Enter Airport Name: ";
        cin >> name;
        cout << "Enter Latitude: ";
        cin >> latitude;
        cout << "Enter Longitude: ";
        cin >> longitude;
    }

    void display(VariadicTable<std::string, double, double>& vt) const 
    {
        vt.addRow(name, latitude, longitude);
    }
};

void read_airport_file(vector<Airport>& airports, const string& filename)
{
    try {
        CSVReader reader(filename);
        for (CSVRow& row : reader)  
        {
            Airport airport;
            airport.name = row["Name"].get<string>();
            airport.latitude = row["Latitude"].get<float>();
            airport.longitude = row["Longitude"].get<float>();
            airports.push_back(airport);
        }
    } catch (const exception& e) {
        cerr << "Error reading CSV file: " << e.what() << endl;
    }
}

double haversine_distance(double lat1, double lon1, double lat2, double lon2) {
    const double earthRad = 6371.0; 
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    lat1 = lat1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;

    double a = sin(dLat / 2) * sin(dLat / 2) +
               sin(dLon / 2) * sin(dLon / 2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return earthRad * c;
}
