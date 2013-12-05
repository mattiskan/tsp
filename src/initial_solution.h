#ifndef INIT
#define INIT

#include <unordered_set>
#include <vector>
#include <limits.h>

typedef std::unordered_set<Point*, std::hash<Point*>> Points;

Point* pollNearest(Points points, Point* ref);

std::vector<Point*> initialSolution(Points points){
  Point * first = *points.begin();
  points.erase(points.begin());

  std::vector<Point*> result;
  result.push_back(first);

  while( !points.empty() ){
    Point* next = pollNearest(points, first);
    
    result.push_back(next);
  }
  result.push_back(first);

  return result;
}


Point* pollNearest(Points points, Point* ref){
  Point * nearest;
  int nearestDist(INT_MAX);

  for(auto it=points.begin(); it!=points.end(); ++it){
    int dist = ref->distanceSquared(**it);
    if(dist < nearestDist){
      nearestDist = dist;
      nearest = *it;
    }
  }

  points.erase(nearest);
  return nearest;
}

#endif
