//airports.hpp

#ifndef AIRPORT_HPP
#define AIRPORT_HPP

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include "csv-parser/single_include/csv.hpp"
#include "variadic_table/include/VariadicTable.h"
#include "utilities.hpp"

using namespace std;
using namespace csv;

class Airport
{
public:
    string name;
    float latitude;
    float longitude;
    int group;

    void add_airport(string name, float latitude, float longitude, int group = -1)
    {
        this->name = name;
        this->latitude = latitude;
        this->longitude = longitude;
        this->group = group;
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
            string n = row["Name"].get<string>();
            float lat = row["Latitude"].get<float>();
            float lon = row["Longitude"].get<float>();
            int group = row["Group"].get<int>();

            airport.add_airport(n, lat, lon, group);
            airports.push_back(airport);
        }
    } catch (const exception& e) {
        cerr << "Error reading CSV file: " << e.what() << endl;
    }
}


#endif 
