#ifndef __MRAND_H__
#define __MRAND_H__

#include "inc.h"

namespace mrand{
   double const RMX=(1.0+double(RAND_MAX));
   void init(int s){
      if(s<0){
         unsigned int t;
         FILE* fp=fopen("/dev/urandom","r");
         fread(&t,4,1,fp);
         fclose(fp);
         srand(t);
         return;
      }
      if(0==s){
         srand(time(NULL));
         return ;
      }
      srand(s);
   }
//
   inline int IRND( int const a , int const b ){//b IS included
      return a+(rand()%(b-a+1));
   }
//
   inline double DRND(){
      return double(rand())/RMX;//uniform in [0,1)
   }
};

#endif
