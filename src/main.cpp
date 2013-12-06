#include <stdio.h>
#include <unordered_set>
#include <functional>
#include "point.cpp"
#include <vector>
#include "initial_solution.h"
#include <algorithm>
#include "2opt.h"

std::vector<Point*> points;


void read();
void printPoints();
void printSolution(std::vector<Point*> & solution);
std::vector<int> getNearestPoints(std::vector<Point*> points, int index);
NearMatrix neighbourMatrix(std::vector<Point*> & points);
int main(){
  read();
  
  NearMatrix nearMatr = neighbourMatrix(points);
  for (int i=0; i<nearMatr.size(); i++) {
    for (int j=0; j<nearMatr[i].size(); j++) {
      printf("(%d %d) ", nearMatr[i][j].dist, nearMatr[i][j].point->i);
    }
    printf("\n");
  }

  //printPoints();

  initialSolution(points, nearMatr);  

  //optimize(points, nearMatr);

  printSolution(points);
}

void read(){
  float x,y;
  int i(-1);
  while( scanf("%f %f", &x, &y) == 2){
    //printf("%f %f\n", x, y);
    points.push_back( new Point(x,y, ++i) );
  }
}

void printPoints() {
  for(auto it = points.begin(); it!=points.end(); ++it)
    printf("%d: (%f, %f)\n", (*it)->i, (*it)->x, (*it)->y);
}

void printSolution(std::vector<Point*> & solution) {
  /*for (auto it=solution.begin(); it<solution.end(); ++it) {
    printf("%d\n", (*it)->i);
    }*/
  Point * curr = solution[0];
  for (int i=0; i<solution.size(); ++i) {
    printf("sol: %d->%d\n", curr->i, curr->next->i);
    curr = curr->next;
  }
}

NearMatrix neighbourMatrix(std::vector<Point*> & points) {
  NearMatrix m;
  for (auto from=points.begin(); from<points.end(); ++from) {
    std::vector<PointDist> row;
    for (auto to=points.begin(); to<points.end(); ++to) {
      if (*from == *to) {
      } else {
	PointDist *pd = new PointDist({(int)std::round((*from)->distanceTo(**to)), *to});
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
  std::vector<int> shortestDists = std::vector<int>(useCount);
  std::partial_sort_copy (allDistances.begin(), allDistances.end(), shortestDists.begin(), shortestDists.end());
  for (int i=0; i<shortestDists.size();i++) {
    
  }
  return shortestDists;
}
