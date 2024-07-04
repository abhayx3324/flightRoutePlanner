#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "csv-parser/include/csv.hpp"

using namespace std;
using namespace csv;

class Airport   {
    string name;
    float latitude;
    float longitude;

    void add_airport()
    {
        printf("Enter Airport Name: ");
        scanf("%s", name);
        printf("Enter Latitude: ");
        scanf("%f", &latitude);
        printf("Enter Longitude: ");
        scanf("%f", &longitude);
    }
};

class Edge {
    string destination;
    float distance;
};

void read_airport_file()
{
    ifstream infile("airports.txt");
    if (!infile)    {
        printf("File failed to open\n");
        return;
    }
    
}

int main()
{
    vector<Airport> graph;
    
}