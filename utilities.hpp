//utilities.hpp

#pragma once

#include "airport.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

double haversine_distance(double lat1, double lon1, double lat2, double lon2) 
{
    const double earthRad = 6371.0; 
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    lat1 = lat1 * M_PI / 180.0;
    lat2 = lat2 * M_PI / 180.0;

    double a = sin(dLat / 2) * sin(dLat / 2) +
               sin(dLon / 2) * sin(dLon / 2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return earthRad * c;
}

double calculate_bearing(double lat1, double lon1, double lat2, double lon2) {
    double dLon = lon2 - lon1;
    double y = sin(dLon) * cos(lat2);
    double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dLon);
    return atan2(y, x) * 180 / M_PI;
}

double calculate_wind_effect(double bearing, double wind_direction, double wind_speed) {
    double wind_effect = wind_speed * cos((wind_direction - bearing) * M_PI / 180.0);
    return wind_effect;
}
