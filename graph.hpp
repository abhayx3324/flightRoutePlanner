//graph.hpp

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "airport.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include <utility>

using namespace std;

class Graph {
public:
    vector<vector<pair<int, double>>> adjacency_list;
    vector<int> group_map;

    void create_adjacency_list(const vector<Airport>& airports)
    {
        size_t n = airports.size();
        adjacency_list.resize(n);
        group_map.resize(n, -1);

        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = i + 1; j < n; ++j)
            {
                if (airports[i].group == airports[j].group)
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

        // Ensure only one connection between groups
        for (size_t i = 0; i < n; ++i)
        {
            if (group_map[airports[i].group] == -1)
            {
                group_map[airports[i].group] = i;
            }
            else
            {
                // Connect this airport to the representative of its group
                double distance = haversine_distance(
                    airports[i].latitude, airports[i].longitude,
                    airports[group_map[airports[i].group]].latitude,
                    airports[group_map[airports[i].group]].longitude
                );
                adjacency_list[i].emplace_back(group_map[airports[i].group], distance);
                adjacency_list[group_map[airports[i].group]].emplace_back(i, distance);
            }
        }
    }

    void save_adjacency_list(const vector<Airport>& airports, const string& filename) const 
    {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        for (size_t i = 0; i < airports.size(); ++i) {
            file << airports[i].name << " -> ";
            for (const auto& [index, distance] : adjacency_list[i]) {
                file << "(" << airports[index].name << ", " << distance << " km) ";
            }
            file << endl;
        }

        file.close();
    }

    void display_adjacency_list(const vector<Airport>& airports) const
    {
        for (size_t i = 0; i < airports.size(); ++i)
        {
            cout << airports[i].name << " -> ";
            for (const auto& [index, distance] : adjacency_list[i])
                cout << "(" << airports[index].name << ", " << distance << " km) ";
            cout << endl;
        }
    }
};


#endif 
