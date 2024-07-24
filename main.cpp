//main.cpp

#include "graph.hpp"

int main() 
{
    Graph graph;

    vector<Airport> airports;
    read_airport_file(airports, "alt_airport_list.csv");

    graph.create_adjacency_list(airports);

    VariadicTable<std::string, double, double, int, std::string> vt({"Airport", "Latitude", "Longitude", "Cluster", "IsMain"}, 10);
    for (const auto& airport : airports)
        airport.display(vt);
    vt.print(cout);

    cout << "\nAdjacency List:\n";
    graph.display_adjacency_list(airports);

    graph.save_adjacency_list(airports, "adj_list.txt");

    string source, destination;
    cout << "Enter source airport: ";
    cin >> source;
    cout << "Enter destination airport: ";
    cin >> destination;

    double distance = graph.dijkstra(airports, source, destination);
    if (distance != -1) 
        cout << "Distance from " << source << " to " << destination << " is " << distance << " km.\n";

    return 0;
}
