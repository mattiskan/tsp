#ifndef ALGORITHMS
#define ALGORITHMS

#include <vector>
#include "common.h"
#include "point.h"

void optimize(std::vector<Point*>&, NearMatrix&);
void initialSolution(std::vector<Point*> & points, NearMatrix & dists, int);

#endif
