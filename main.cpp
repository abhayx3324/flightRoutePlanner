#include "airport.hpp"

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