#include <stdio.h>
#include <unordered_set>
#include <functional>
#include "point.cpp"
#include <vector>
#include "initial_solution.h"


Points points;

void read();
void printPoints();
void printSolution(std::vector<Point*> & solution);

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
