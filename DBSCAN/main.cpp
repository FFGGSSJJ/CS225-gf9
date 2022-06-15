#include <stdio.h>
#include "dbscan.cpp"
#include "IOdbscan.h"

#define MINIMUM_POINTS 1     // minimum number of cluster
#define EPSILON (30)  // distance for clustering, metre^2



int main()
{    
    vector<DISTANCE> points;

    // read point data
    readBenchmarkData(points);

    // constructor
    DBSCAN ds(MINIMUM_POINTS, EPSILON, points);

    // main loop
    ds.run();

    // result of DBSCAN algorithm
    printResults(ds.m_points, ds.getTotalPointSize());    

    return 0;
}
