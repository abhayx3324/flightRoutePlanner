Sure, here is a README file for your project:

---

# Flight Route Planner

This project is a flight route planner implemented in C++. It uses Dijkstra's algorithm to find the shortest path between airports, considering the effect of wind on travel distance. The planner represents airports using a graph, where the nodes are airports, and the edges are the distances between them.

## Features

- Calculate the shortest path between airports using Dijkstra's algorithm.
- Consider the effect of wind speed and direction on travel distance.
- Support for grouping airports, where airports within a group have direct paths to each other, and only one airport within each group connects to another group.
- Display and save the adjacency list of the graph.

## File Structure

- **airports.hpp**: Defines the `Airport` class and functions for reading airport data from a CSV file.
- **graph.hpp**: Defines the `Graph` class and functions for creating the adjacency list, displaying it, and finding the shortest path using Dijkstra's algorithm.
- **utilities.hpp**: Contains utility functions for calculating haversine distance, bearing, and wind effect.
- **main.cpp**: The main driver of the program, which reads airport data, creates the adjacency list, displays it, and allows the user to find the shortest path between two airports.

## Dependencies

- [csv-parser](https://github.com/vincentlaucsb/csv-parser): A fast CSV parser for C++.
- [VariadicTable](https://github.com/friedmud/variadic_table): A simple header-only library for pretty-printing tables in C++.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/flight-route-planner.git
   cd flight-route-planner
   ```

2. Install the dependencies:
   Follow the instructions on the [csv-parser](https://github.com/vincentlaucsb/csv-parser) and [VariadicTable](https://github.com/friedmud/variadic_table) repositories to install these libraries.

3. Compile the project:
   ```bash
   g++ -o flight_route_planner main.cpp -I/path/to/csv-parser -I/path/to/variadic_table
   ```

## Usage

1. Prepare a CSV file containing the airport data. The CSV file should have the following columns:
   - `Name`: The name of the airport.
   - `Latitude`: The latitude of the airport.
   - `Longitude`: The longitude of the airport.
   - `Cluster`: The cluster/group number of the airport.
   - `IsMain`: A boolean indicating whether the airport is the main airport in its cluster.
   - `WindSpeed`: The wind speed at the airport.
   - `WindDirection`: The wind direction at the airport.

2. Run the program:
   ```bash
   ./flight_route_planner
   ```

3. The program will display the list of airports and the adjacency list. You can then enter the source and destination airports to find the shortest path between them, considering wind effects.

## Example

Here's an example of the CSV file format:

```csv
Name,Latitude,Longitude,Cluster,IsMain,WindSpeed,WindDirection
JFK,40.6413,-73.7781,1,true,5,180
LAX,33.9416,-118.4085,2,true,3,270
ORD,41.9742,-87.9073,3,true,4,90
ATL,33.6407,-84.4277,1,false,2,360
DFW,32.8998,-97.0403,2,false,6,135
```

When prompted, enter the source and destination airport names (e.g., `JFK` and `LAX`) to calculate the shortest path and the effective wind-corrected distance.