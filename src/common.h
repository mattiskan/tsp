#ifndef COMMON_H
#define COMMON_H
#include "point.h"

typedef std::vector<std::vector<PointDist>> NearMatrix;

extern std::vector<Point*> points;
extern NearMatrix distances;


#endif
