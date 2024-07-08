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

int main()
{
    vector<Airport> airports;
    string filename = "airports.csv";

    read_airport_file(airports, filename);

    VariadicTable<std::string, double, double> vt({"Airport", "Latitude", "Longitude"}, 10);
    
    for (const auto& airport : airports)
        airport.display(vt);

    vt.print(cout);

    return 0;
}
