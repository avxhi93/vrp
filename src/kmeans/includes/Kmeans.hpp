#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <vector>
#include "Tour.hpp"
using std::vector;
using std::pair;

//X and Y from centroid point
namespace CentroidCalc{
    pair<double,double> calcRouteCentroid(vector<int>&);
    vector<pair<double,double>> getAllCentroids(Tour&);
    bool compareCentroids(vector<pair<double,double>>,vector<pair<double,double>>);
    bool compareDoubles(double, double);
}
//Given a customer, returns the nearest centroid from it
namespace Classifier{
    int  findNearestCentroid(vector<pair<double,double>> centroids,int customer);
    Tour KmeansBasic(Tour&, vector<pair<double,double>>);
}

namespace KmeansMethods{
    Tour InfiniteIteratedKmeans(Tour&);
    Tour LimitedIteratedKmeans(Tour&,int iterations);
}
namespace Kmeans{
    Tour run(Tour&);
}
#endif