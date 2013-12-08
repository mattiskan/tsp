#include <vector>
#include <limits.h>
#include <math.h>
#include "common.h"

void initialSolution(std::vector<Point*> & points, NearMatrix & dists, int firstIndex) {
  std::vector<bool> used(points.size(), false);
  used[firstIndex] = true;
  Point & first = *points[firstIndex];
  Point * curr = &first;
  for (int i=1; i<(int)dists.size(); i++) {
    for (int j=1; j<(int)dists.size()-1; j++) {
      PointDist & pd = dists[curr->i][j];
      if (used[pd.point->i]) continue;
      used[pd.point->i] = true;
      pd.point->prev = curr;
      curr->next = pd.point;
      curr = pd.point;
      break;
    }
  }
  curr->next = &first;
  first.prev = curr;

}
