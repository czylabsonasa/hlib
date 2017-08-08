#ifndef __WEIGHTS_H__
#define __WEIGHTS_H__
#include "common.hpp"

struct tMut{
   int* p;
   int np;
   bool operator<(const tMut& masik)const{
      int i=0;
      while(i<np&&p[i]==masik.p[i]){i++;}
      if(i<np&&p[i]<masik.p[i]){return true;}
      return false;
   }
};

#endif
