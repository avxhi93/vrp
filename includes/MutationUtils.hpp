#ifndef MUTATIONUTILS_H
#define MUTATIONUTILS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "Map.hpp"
#include "Utils.hpp"

using namespace std;
bool checkInSameTour(vector<int>, int,int,int);
pair<vector<int>,bool> basicFitnessEvaluation(vector<int>,vector<int>,Map&);
void printVector(vector<int>,Map&);
bool validateTour(vector<int>,int,int);
pair<vector<int>,bool> setInitialResult(vector<int>);
vector<int> doubleSwap(vector<int>,int currentValue,int iterationValue,
int newValueU, int newValueX,int newValueV,int newValueY);


#endif