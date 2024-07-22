//main.cpp

#include "graph.hpp"

int main() {
    Graph graph;

    vector<Airport> airports;
    read_airport_file(airports, "airport_list.csv");

    graph.create_adjacency_list(airports);

    VariadicTable<std::string, double, double> vt({"Airport", "Latitude", "Longitude"}, 10);
    for (const auto& airport : airports) {
        airport.display(vt);
    }
    vt.print(cout);

    cout << "\nAdjacency List:\n";
    graph.display_adjacency_list(airports);

    graph.save_adjacency_list(airports, "adj_list.txt");

    return 0;
}
