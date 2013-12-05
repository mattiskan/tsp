#include <math.h>
#include <cstdio>
#include <functional>

struct Point {
  const float x,y;
  
  Point(float tx, float ty) : x(tx), y(ty) {}

  int distanceTo(const Point &p) const{
    return round(sqrt(distanceSquared(p)));
  }
	

  float distanceSquared(const Point &p) const{
    return (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y);
  }
};


namespace std {
  template<>
  struct hash<Point*> {
  public:
    std::size_t operator() (Point const *p) const {
      return (size_t) p;
    }
  };
}
