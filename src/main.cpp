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
int totalDist(std::vector<Point*> & points);
void printSolution(std::vector<Point*> & solution);
std::vector<int> getNearestPoints(std::vector<Point*> points, int index);
NearMatrix neighbourMatrix(std::vector<Point*> & points);
int main(){
  read();
  
  NearMatrix nearMatr = neighbourMatrix(points);
  /*printf("%d %d", nearMatr.size(), nearMatr[0].size());
  for (int i=0; i<nearMatr.size(); i++) {
    for (int j=0; j<nearMatr[i].size(); j++) {
      printf("(%d %d) ", nearMatr[i][j].dist, nearMatr[i][j].point->i);
    }
    printf("\n");
  }//*/

  //printPoints();

  initialSolution(points, nearMatr); 
  //  printf("Greedy dist: %d\n", &points);

  

  optimize(points, nearMatr);
  //printf("2opt dist: %d\n", &points);

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
    printf("%d\n", curr->i);
    curr = curr->next;
  }
}

NearMatrix neighbourMatrix(std::vector<Point*> & points) {
  //printf("lalalastart %d\n", points.size());
  NearMatrix m = NearMatrix(points.size(), std::vector<PointDist>());
  for (int i=0; i<points.size(); ++i) {
    m[i].reserve(points.size()-1);
  }
  
  //printf("lalalamiddle %d\n", m.size());
  for (int i=0; i<points.size(); ++i) {
    Point * from = points[i];
    for (int j=1+i; j<points.size(); ++j) {
      Point * to = points[j];
      int dist = (int)std::round(from->distanceTo(*to));
      m[i].emplace_back(dist, to);
      m[j].emplace_back(dist, from);
    }
    std::sort(m[i].begin(), m[i].end());
  }
  //printf("lalalaend %d %d\n", m.size(), m[0].size());
  return m;
}


int totalDist(std::vector<Point*> & points) {
   Point * curr = points[0];
   int total = 0;
   for (int i=0; i<points.size(); ++i) {
     total += round(curr->distanceTo(*curr->next));
     curr = curr->next;
   } 
}
