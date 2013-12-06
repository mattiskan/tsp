#ifndef TWO_OPT
#define TWO_OPT

#include <vector>
#include "point.cpp"


void swap(Point&, Point&);
int findSwap(NearMatrix&, Point&);

std::vector<Point> optimize(NearMatrix matrix){
  int delta;

  do{
    delta = 0;
    for(auto t=matrix.begin(); t!=matrix.end(); ++t){
      delta -= findSwap(matrix, *(*t)[0].point);
    }
  }while(delta < 0);

}

int findSwap(NearMatrix& matrix, Point& t1){
  Point *t2 = t1.next;//index för staden efter t1 just nu

  bool found(false);
  for(auto t3pd=matrix[t2->i].begin(); t3pd!=matrix[t2->i].end(); ++t3pd){ //iterera över städer nära t2
    Point *t3 = t3pd->point;
    int preSwap = t1.distanceTo(*t2)+t3->distanceToNext();
    int postSwap = t1.distanceTo(*t3->next)+t2->distanceTo(*t3);
    if( postSwap < preSwap ){
      swap(t1, *t3);
      return postSwap - preSwap; // Improvement (as a positive value)
    }
  }
  return 0;
}

void swap(Point &t1, Point &t3){
  Point* tmp( t1.next);
  t1.next = t3.next;
  t3.next = tmp;
}


#endif
