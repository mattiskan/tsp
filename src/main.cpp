#include <stdio.h>
#include <unordered_set>
#include <functional>
#include "point.cpp"
#include <vector>
#include "initial_solution.h"
#include <algorithm>


Points points;

void read();
void printPoints();
void printSolution(std::vector<Point*> & solution);
std::vector<int> getNearestPoints(std::vector<Point*> points, int index) {

int main(){
  read();

  //printPoints();

  std::vector<Point*> res = initialSolution(points);  

  printSolution(res);
}

void read(){
  float x,y;
  int i(-1);
  while( scanf("%f %f", &x, &y) == 2){
    points.insert( new Point(x,y, ++i) );
  }
}

void printPoints() {
  for(auto it = points.begin(); it!=points.end(); ++it)
    printf("%d: (%f, %f)\n", (*it)->i, (*it)->x, (*it)->y);
}

void printSolution(std::vector<Point*> & solution) {
  for (auto it=solution.begin(); it<solution.end(); ++it) {
    printf("%d\n", (*it)->i);
  }
}

std::vector<int> getNearestPoints(std::vector<Point*> points, int index) {
  int useCount = std::min((int)points.size()-1, 20);
  std::vector<float> allDistances;
  Point * from = points[index];
  for (int i=0; i<points.size(); i++) {
    if (i==index) continue;
    allDistances.push_back(from->distanceSquared(*points[i]));
  }
  std::vector<int> * shortestDists = new std::vector<int>(useCount);
  std::partial_sort_copy (allDistances.begin(), allDistances.end(), shortestDists->begin(), shortestDists->end());
  return *shortestDists;
}
