//graph.hpp

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "airport.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>

using namespace std;

class Graph 
{
    public:
    vector<vector<pair<int, double>>> adjacency_list;

    void create_adjacency_list(const vector<Airport>& airports) 
    {
        size_t n = airports.size();
        adjacency_list.resize(n);

        // Connect airports within the same group
        for (size_t i = 0; i < n; ++i) 
        {
            for (size_t j = i + 1; j < n; ++j) 
            {
                if (airports[i].cluster == airports[j].cluster) 
                {
                    double distance = haversine_distance(
                        airports[i].latitude, airports[i].longitude,
                        airports[j].latitude, airports[j].longitude
                    );
                    adjacency_list[i].emplace_back(j, distance);
                    adjacency_list[j].emplace_back(i, distance);
                }
                else if (airports[i].is_main && airports[j].is_main) 
                {
                    double distance = haversine_distance(
                        airports[i].latitude, airports[i].longitude,
                        airports[j].latitude, airports[j].longitude
                    );
                    adjacency_list[i].emplace_back(j, distance);
                    adjacency_list[j].emplace_back(i, distance);
                }
            }
        }
    }

    void save_adjacency_list(const vector<Airport>& airports, const string& filename) const 
    {
        ofstream file(filename);
        if (!file.is_open()) 
        {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        for (size_t i = 0; i < airports.size(); ++i) 
        {
            file << airports[i].name << " -> ";
            for (const auto& [index, distance] : adjacency_list[i]) {
                file << "(" << airports[index].name << ", " << distance << " ) ";
            }
            file << endl;
        }

        file.close();
    }

    void load_adjacency_list(const vector<Airport>& airports, const string& filename) const 
    {
        ifstream file(filename);
        if (!file.is_open()) 
        {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        file.close();
    }

    void display_adjacency_list(const vector<Airport>& airports) const 
    {
        for (size_t i = 0; i < airports.size(); ++i) 
        {
            cout << airports[i].name << " -> ";
            for (const auto& [index, distance] : adjacency_list[i]) 
                cout << "(" << airports[index].name << ", " << distance << " ) ";
            cout << endl;
        }
    }

    double dijkstra(const vector<Airport>& airports, const string& source_name, const string& destination_name) 
    {
        int n = airports.size();
        vector<double> min_distance(n, numeric_limits<double>::infinity());
        vector<bool> visited(n, false);

        auto compare = [](pair<int, double> a, pair<int, double> b) { return a.second > b.second; };
        priority_queue<pair<int, double>, vector<pair<int, double>>, decltype(compare)> pq(compare);

        int source_index = find_airport_index(airports, source_name);
        int destination_index = find_airport_index(airports, destination_name);

        if (source_index == -1 || destination_index == -1) 
        {
            cerr << "Invalid source or destination airport name." << endl;
            return -1;
        }

        pq.emplace(source_index, 0);
        min_distance[source_index] = 0;

        while (!pq.empty()) 
        {
            int u = pq.top().first;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (const auto& [v, weight] : adjacency_list[u]) 
            {
                if (!visited[v] && min_distance[u] + weight < min_distance[v]) 
                {
                    min_distance[v] = min_distance[u] + weight;
                    pq.emplace(v, min_distance[v]);
                }
            }
        }

        return min_distance[destination_index];
    }
};

#endif 