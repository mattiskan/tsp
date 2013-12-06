#ifndef INIT
#define INIT

#include <unordered_set>
#include <vector>
#include <limits.h>
#include <math.h>

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

void initialSolution(std::vector<Point*> & points, NearMatrix & dists) {
  std::vector<bool> used(points.size(), false);
  used[0] = true;
  int usedCount = 1;
  Point & first = *points[0];
  Point * curr = &first;
  for (int i=1; i<dists.size(); i++) {
    for (int j=0; j<dists.size()-1; j++) {
      PointDist & pd = dists[curr->i][j];
      if (used[pd.point->i]) continue;
      used[pd.point->i] = true;
      pd.point->prev = curr;
      curr->next = pd.point;
      curr->nextDist = pd.dist;
      pd.point->prevDist = curr->nextDist;
      curr = pd.point;
      break;
    }
  }
  curr->next = &first;
  first.prev = curr;
  curr->nextDist = round(curr->distanceTo(first));
  first.prevDist = curr->nextDist;
}

#endif
