#include <stdio.h>
#include <unordered_set>
#include <functional>
#include "point.cpp"
#include <vector>
#include "initial_solution.h"
#include <algorithm>

struct PointDist {
  int dist;
  Point * point;
  bool operator< (const PointDist & o) const {
    return dist < o.dist;
  }
};
Points points;

void read();
void printPoints();
void printSolution(std::vector<Point*> & solution);
std::vector<int> getNearestPoints(std::vector<Point*> points, int index);

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

std::vector<std::vector<PointDist>> neighbourMatrix(std::vector<Point*> & points) {
  std::vector<std::vector<PointDist>> m;
  for (auto from=points.begin(); from<points.end(); ++from) {
    std::vector<PointDist> row;
    for (auto to=points.begin(); to<points.end(); ++to) {
      if (*from == *to) {
      } else {
	PointDist *pd = new PointDist({std::round((*from)->distanceTo(**to)), *to});
	row.push_back(*pd);
      }
    }
    std::sort(row.begin(), row.end());
    m.push_back(row);
  }
  return m;
}

std::vector<int> getNearestPoints(std::vector<Point*> points, int index) {
  int useCount = std::min((int)points.size()-1, 20);
  std::vector<int> allDistances;
  Point * from = points[index];
  for (int i=0; i<points.size(); i++) {
    if (i==index) continue;
    allDistances.push_back(std::round(from->distanceTo(*points[i])));
  }
  std::vector<int>  shortestDists = std::vector<int>(useCount);
  std::partial_sort_copy (allDistances.begin(), allDistances.end(), shortestDists.begin(), shortestDists.end());
  for (int i=0; i<shortestDists.size();i++) {

  }
  return shortestDists;
}
