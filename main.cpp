#include "graph.hpp"

int main()
{
    Graph graph;
    string filename = "airports.csv";

    vector<Airport> airports;
    read_airport_file(airports, filename);

    for (const auto& airport : airports) {
        graph.add_airport(airport);
    }

    graph.create_adjacency_list();

    VariadicTable<std::string, double, double> vt({"Airport", "Latitude", "Longitude"}, 10);
    for (const auto& airport : graph.airports)
        airport.display(vt);
    vt.print(cout);

    cout << "\nAdjacency List:\n";
    graph.display_adjacency_list();

    return 0;
}
