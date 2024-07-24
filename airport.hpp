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
    int cluster;
    bool is_main;

    void add_airport(string name, float latitude, float longitude, int cluster = -1, bool is_main = false)
    {
        this->name = name;
        this->latitude = latitude;
        this->longitude = longitude;
        this->cluster = cluster;
        this->is_main = is_main;
    }

    void display(VariadicTable<std::string, double, double, int, std::string>& vt) const
    {
        vt.addRow(name, latitude, longitude, cluster, is_main?"Yes":"No");
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
            int group = row["Cluster"].get<int>();
            bool m = row["IsMain"].get<bool>();

            airport.add_airport(n, lat, lon, group, m);
            airports.push_back(airport);
        }
    } catch (const exception& e) {
        cerr << "Error reading CSV file: " << e.what() << endl;
    }
}

int find_airport_index(const vector<Airport>& airports, const string& name) 
{
    for (size_t i = 0; i < airports.size(); ++i) 
    {
        if (airports[i].name == name)
            return i;
    }
    return -1;
}


#endif 
