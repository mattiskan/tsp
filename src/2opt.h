#ifndef TWO_OPT
#define TWO_OPT

#include <vector>
#include "point.cpp"
#include <iostream>

void swap(Point*, Point*);
int findSwap(NearMatrix&, Point*);

std::vector<Point> optimize(std::vector<Point*> & points, NearMatrix& matrix){
  std::vector<Point> a;
  int delta;

  do{
    delta = 0;
    for(int i=0; i<matrix.size(); ++i){
      delta -= findSwap(matrix, points[i]);
    }
  }while(delta < 0);
  return a;
}

int findSwap(NearMatrix& matrix, Point *t1){
  const Point *t2 = t1->next;//index för staden efter t1 just nu
  for(int i=0; i<matrix[t2->i].size(); ++i){ //iterera över städer nära t2
    Point *t3 = matrix[t2->i][i].point;
    Point *t4 = t3->next;

    int preSwap = t1->distanceTo(*t2) + t3->distanceTo(*t4);
    int postSwap = t1->distanceTo(*t4) + t2->distanceTo(*t3);
    if( postSwap < preSwap ){
      swap(t1, t3);
      return postSwap - preSwap; // Improvement (as a positive value)
      }
  }
  return 0;
}

void swap(Point *t1, Point *t3){
  std::cout << "Swapping t" <<t1->i << ".next becomes t" << t3->next->i << std::endl;;
  std::cout << "and t" <<t3->i << ".next becomes t" << t1->next->i << std::endl;;

  Point* tmp = t1->next;
  t1->next = t3->next;
  t3->next = tmp;
}


#endif
