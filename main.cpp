//main.cpp

#include "graph.hpp"
#include <algorithm>
#include <cctype>

int main() 
{
    Graph graph;

    vector<Airport> airports;
    read_airport_file(airports, "csv_files/airport_list.csv");

    graph.create_adjacency_list(airports);

    VariadicTable<std::string, double, double, int, std::string, double, double> vt({"Airport", "Latitude", "Longitude", "Cluster", "IsMain", "WindSpeed", "WindDirection"}, 10);
    for (const auto& airport : airports)
        airport.display(vt);
    vt.print(cout);

    cout << "\nAdjacency List:\n";
    graph.display_adjacency_list(airports);

    graph.save_adjacency_list(airports, "adj_list.txt");

    graph.display_adjacency_list(airports);

    string source, destination;
    cout << "Enter source airport: ";
    cin >> source;
    cout << "Enter destination airport: ";
    cin >> destination;

    std::transform(source.begin(), source.end(), source.begin(), ::toupper);
    std::transform(destination.begin(), destination.end(), destination.begin(), ::toupper);

    double distance = graph.dijkstra(airports, source, destination);
    if (distance != -1) 
        cout << "Effective (wind corrected) distance from " << source << " to " << destination << " is " << distance << " km.\n";

    return 0;
}