#include <vector>
#include <iostream>
#include "point.h"
#include "common.h"

void swap(Point&, Point&);
int findSwap(NearMatrix&, Point*);
void reverseInterval(Point*, Point*);

int optimize(std::vector<Point*> & points, NearMatrix& matrix){
  int end(0);
  int totalDiff(0);
  bool improving;
  do{
    improving = false;
    for(int i=0; i<(int)matrix.size(); ++i){
      int thisDiff = findSwap(matrix, points[i]);
      if(thisDiff != 0)
	improving = true;
      totalDiff += thisDiff;
    }
  }while(improving && ++end < 5);
  return totalDiff;;
}

int findSwap(NearMatrix& nearMat, Point *t1){
  Point *t2 = t1->next;//index för staden efter t1 just nu

  for(int i=1; i<(int)nearMat[t2->i].size(); ++i){ //iterera över städer nära t2
    Point *t3 = nearMat[t2->i][i].point;
    Point *t4 = t3->next;

    if(t1==t3)
      continue;

    int preSwap = t1->distanceTo(*t2) + t3->distanceTo(*t4);
    int postSwap = t1->distanceTo(*t3) + t2->distanceTo(*t4);
    if( postSwap < preSwap ){
      swap(*t1, *t3);
      reverseInterval(t3, t2);
      return preSwap - postSwap;
    }
  }
  return false;
}

void swap(Point &t1, Point &t3){
  //std::cout << "swapping " << t1.i << "->" << t1.next->i << " with " << t3.i<<"->"<<t3.next->i << std::endl;
  Point *t2 = t1.next;
  t2->prev = t3.next;//t2.next=t4
  t3.next->prev = t2; //t4=t2

  t1.next = &t3;
  t3.next = &t1;
}


void reverseInterval(Point *from, Point *to){
  //std::cout << "reversing from "<< from->i << " to " << to->i << std::endl;
  while(from != to){
    from->reverse();
    from = from->next;
  }
  to->reverse();
}
