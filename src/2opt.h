#ifndef TWO_OPT
#define TWO_OPT

#include <vector>
#include "point.cpp"
#include <iostream>

void swap(Point&, Point&);
bool findSwap(NearMatrix&, Point*);
void reverseInterval(Point*, Point*);

void optimize(std::vector<Point*> & points, NearMatrix& matrix){
  bool improving;
  do{
    improving = false;
    for(int i=0; i<matrix.size(); ++i){
      if(findSwap(matrix, points[i]))
	improving = true;
      return;
    }
  }while(improving);

}

bool findSwap(NearMatrix& matrix, Point *t1){
  Point *t2 = t1->next;//index för staden efter t1 just nu

  for(int i=0; i<matrix[t2->i].size(); ++i){ //iterera över städer nära t2
    Point *t3 = matrix[t2->i][i].point;
    Point *t4 = t3->next;

    if(t1==t3)
      continue;

    int preSwap = t1->distanceTo(*t2) + t4->distanceTo(*t3);
    int postSwap = t1->distanceTo(*t3) + t2->distanceTo(*t4);
    if( postSwap < preSwap ){
      swap(*t1, *t3);
      reverseInterval(t3, t2);
      return true;
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
  std::cout << "pass2" << std::endl;
}


#endif
