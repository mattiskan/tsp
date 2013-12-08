#ifndef POINT
#define POINT

#include <math.h>
#include <cstdio>
#include <functional>
#include <vector>

struct Point {
  const float x,y;
  const int i;
  bool changeDir;
  Point *next, *prev;

  Point(float tx, float ty, int index) : x(tx), y(ty), i(index), changeDir(false) {
    next = nullptr;
    prev = nullptr;
  }

  int distanceTo(const Point &p) const{
    return round(sqrt(distanceSquared(p)));
  }


  float distanceSquared(const Point &p) const{
    return (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y);
  }

  void reverse(){
    Point* tmp = next;
    next = prev;
    prev = tmp;
  }
};

struct PointDist {
  int dist;
  Point * point;
  bool operator< (const PointDist & o) const {
    return dist < o.dist;
  }
  PointDist(int d, Point * p) : dist(d), point(p) { }
  PointDist() { }
};

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
