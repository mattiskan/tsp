#ifndef INIT
#define INIT

#include <unordered_set>
#include <vector>

typedef std::unordered_set<Point*, std::hash<Point*>> Points;

std::vector<Point*> initialSolution(Points points){
  Point * first = *points.begin();
  points.erase(points.begin());
  

  
}

#endif
