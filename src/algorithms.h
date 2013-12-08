#ifndef ALGORITHMS
#define ALGORITHMS

#include <vector>
#include "common.h"
#include "point.h"

int optimize(std::vector<Point*>&, NearMatrix&);
void initialSolution(std::vector<Point*> & points, NearMatrix & dists, int);

#endif
