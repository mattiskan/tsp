#include <stdio.h>
#include <functional>
#include <vector>
#include <algorithm>
#include "algorithms.h"
#include "common.h"
#include "point.h"

void read();
void printPoints();
int totalDist(std::vector<Point*> & points);
void printSolution(std::vector<Point*> & solution);
std::vector<int> getNearestPoints(std::vector<Point*> points, int index);


NearMatrix neighbourMatrix(std::vector<Point*> & points);
NearMatrix distances;

std::vector<Point*> points;

int main(){
  read();
  
  NearMatrix nearMatr = neighbourMatrix(points);
  /*printf("%d %d", distances.size(), distances[0].size());
  for (int i=0; i<distances.size(); i++) {
    for (int j=0; j<distances[i].size(); j++) {
      printf("(%d %d) ", distances[i][j].dist, distances[i][j].point->i);
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
  scanf("%*d");
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
  for (int i=0; i<(int)solution.size(); ++i) {
    printf("%d\n", curr->i);
    curr = curr->next;
  }
}

int Point::distanceTo(const Point &p) const{
  return distances[this->i][p.i].dist;
}


NearMatrix neighbourMatrix(std::vector<Point*> & points) {
  //printf("lalalastart %d\n", points.size());
  NearMatrix m = NearMatrix(points.size(), std::vector<PointDist>(points.size()));
  /*for (int i=0; i<(int)points.size(); ++i) {
    m[i].reserve(points.size()-1);
    }*/
  
  //printf("lalalamiddle %d\n", m.size());
  for (int i=0; i<(int)points.size(); ++i) {
    Point * from = points[i];
    m[i][i] = PointDist(0, from);
    for (int j=1+i; j<(int)points.size(); ++j) {
      Point * to = points[j];
      int dist = (int)std::round(from->calcDistanceTo(*to));
      m[i][j] = PointDist(dist, to);
      m[j][i] = PointDist(dist, from);
    }
  }
  distances = m;
  for (int i=0; i<(int)points.size(); ++i) {
    std::sort(m[i].begin(), m[i].end());
  }
  //printf("lalalaend %d %d\n", m.size(), m[0].size());
  return m;
}


int totalDist(std::vector<Point*> & points) {
   Point * curr = points[0];
   int total = 0;
   for (int i=0; i<(int)points.size(); ++i) {
     total += curr->distanceTo(*curr->next);
     curr = curr->next;
   } 
   return total;
}
