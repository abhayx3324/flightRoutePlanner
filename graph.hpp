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
};

#endif 
