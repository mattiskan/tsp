#ifndef INIT
#define INIT

#include <unordered_set>
#include <vector>
#include <limits.h>

typedef std::unordered_set<Point*, std::hash<Point*>> Points;

Point* pollNearest(Points &points, Point* ref);

std::vector<Point*> initialSolution(Points &points){
  Point * first = *points.begin();
  points.erase(points.begin());

  std::vector<Point*> result;

  result.push_back(first);
  Point* previous = first;
  while( !points.empty() ){
    Point* next = pollNearest(points, previous);
    previous->next = next;
    result.push_back(next);
    previous = next;
  }
  previous->nextDist = previous->distanceSquared(*first);

  return result;
}


Point* pollNearest(Points &points, Point* ref){
  Point * nearest;
  int nearestDist(INT_MAX);

  for(auto it=points.begin(); it!=points.end(); ++it){
    int dist = ref->distanceSquared(**it);
    if(dist < nearestDist){
      nearestDist = dist;
      nearest = *it;
    }
  }

  ref->nextDist = nearestDist;
  points.erase(nearest);
  return nearest;
}

/*void initialSolution(std::vector<Point*> & points, std::vector<std::vector<int>> & dists) {
  std::vector<bool> used(points.size());
  used[0] = true;
  int usedCount = 1;
  for (int i=0; i<dists.size(); i++) {
    for (int j=0; j<dists.size(); j++) {
      
      if (i==j || used[dist[i][j].second->i]) continue;
      used[j
    }
  }

  }*/

#endif
