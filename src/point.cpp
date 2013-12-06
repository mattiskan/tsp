#ifndef POINT
#define POINT

#include <math.h>
#include <cstdio>
#include <functional>
#include <vector>

struct Point {
  const float x,y;
  const int i;
  Point* next;
  float nextDist;

  Point(float tx, float ty, int index) : x(tx), y(ty), i(index) 
  {}

  int distanceTo(const Point &p) const{
    return round(sqrt(distanceSquared(p)));
  }

  int distanceToNext(){
    return distanceTo(*next);
  }
	

  float distanceSquared(const Point &p) const{
    return (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y);
  }
};

struct PointDist {
  int dist;
  Point * point;
  bool operator< (const PointDist & o) const {
    return dist < o.dist;
  }
};

typedef std::vector<std::vector<PointDist>> NearMatrix;

//Hash:
namespace std {
  template<>
  struct hash<Point*> {
  public:
    std::size_t operator() (Point const *p) const {
      return (size_t) p;
    }
  };
}

#endif
