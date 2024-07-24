//graph.hpp

#pragma once

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

        for (size_t i = 0; i < n; ++i) 
        {
            for (size_t j = i + 1; j < n; ++j) 
            {
                if (airports[i].cluster == airports[j].cluster) 
                {
                    double distance1 = haversine_distance(
                        airports[i].latitude, airports[i].longitude,
                        airports[j].latitude, airports[j].longitude
                    );
                    double distance2 = haversine_distance(
                        airports[j].latitude, airports[j].longitude,
                        airports[i].latitude, airports[i].longitude
                    );
                    distance1 = calculate_effective_distance(airports[i], airports[j], distance1);
                    distance2 = calculate_effective_distance(airports[j], airports[i], distance2);
                    adjacency_list[i].emplace_back(j, distance1);
                    adjacency_list[j].emplace_back(i, distance2);
                }
                else if (airports[i].is_main && airports[j].is_main) 
                {
                    double distance1 = haversine_distance(
                        airports[i].latitude, airports[i].longitude,
                        airports[j].latitude, airports[j].longitude
                    );
                    double distance2 = haversine_distance(
                        airports[j].latitude, airports[j].longitude,
                        airports[i].latitude, airports[i].longitude
                    );
                    distance1 = calculate_effective_distance(airports[i], airports[j], distance1);
                    distance2 = calculate_effective_distance(airports[j], airports[i], distance2);
                    adjacency_list[i].emplace_back(j, distance1);
                    adjacency_list[j].emplace_back(i, distance2);
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
            file << airports[i].name << " > ";
            for (const auto& [index, distance] : adjacency_list[i]) {
                file << "(" << airports[index].name << ", " << distance << "), ";
            }
            file << endl;
        }

        file.close();
    }


    void display_adjacency_list(const vector<Airport>& airports) const 
    {
        for (size_t i = 0; i < airports.size(); ++i) 
        {
            cout << airports[i].name << " > ";
            for (const auto& [index, distance] : adjacency_list[i]) 
                cout << "(" << airports[index].name << ", " << distance << "), ";
            cout << endl;
        }
    }

    double dijkstra(const vector<Airport>& airports, const string& source_name, const string& destination_name) 
    {
        int n = airports.size();
        vector<double> min_distance(n, numeric_limits<double>::infinity());
        vector<bool> visited(n, false);
        vector<int> predecessor(n, -1); // To store the path

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
                    predecessor[v] = u; // Update predecessor
                    pq.emplace(v, min_distance[v]);
                }
            }
        }

        if (min_distance[destination_index] == numeric_limits<double>::infinity())
        {
            cout << "No path found from " << source_name << " to " << destination_name << endl;
            return -1;
        }

        cout << "Shortest path from " << source_name << " to " << destination_name << " with distance: " << min_distance[destination_index] << endl;
        cout << "Path: ";
        print_path(predecessor, destination_index, airports);
        cout << endl;

        return min_distance[destination_index];
    }

    void print_path(const vector<int>& predecessor, int destination_index, const vector<Airport>& airports) const
    {
        if (predecessor[destination_index] == -1) 
        {
            cout << "No path";
            return;
        }

        vector<int> path;
        for (int at = destination_index; at != -1; at = predecessor[at]) 
        {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        for (size_t i = 0; i < path.size(); ++i) 
        {
            if (i > 0) cout << " -> ";
            cout << airports[path[i]].name;
        }
    }
};