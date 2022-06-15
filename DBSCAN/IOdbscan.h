#include <iostream>
#include <fstream>
#include "dbscan.h"

void readBenchmarkData(vector<DISTANCE>& points)
{
    // load point cloud
    FILE *stream;
    stream = fopen ("test.dat","ra");

    unsigned int minpts, num_points, cluster, i = 0;
    double epsilon;
    fscanf(stream, "%u\n", &num_points);

    DISTANCE *p = (DISTANCE *)calloc(num_points, sizeof(DISTANCE));

    while (i < num_points)
    {
          fscanf(stream, "%d,%f,%f,%d,%d\n", &(p[i].id),&(p[i].x), &(p[i].y), &(p[i].treatment_type), &cluster);
          p[i].id = i;
          p[i].z = 0;
          p[i].clusterID = UNCLASSIFIED;
          points.push_back(p[i]);
          ++i;
    }

    free(p);
    fclose(stream);
}

void printResults(vector<DISTANCE>& points, int num_points)
{
    int i = 0;
    /*
    printf("Number of points: %u\n"
        " ID      x     y     TreatmentType     cluster_id\n"
        "---------------------------------------------------------\n"
    */
    ofstream myout("myout.txt");
    while (i < num_points)
    {
        myout<<points[i].id<<","<<points[i].x<<","<<points[i].y<<","<<points[i].treatment_type<<","<<points[i].clusterID<<endl;
        ++i;
    }
    myout.close();
}