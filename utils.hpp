#ifndef __UTILS_H__
#define __UTILS_H__

#include "inc.hpp"
#include "mrand.hpp"
#include "vecutils.hpp"
using namespace vecutils;

#define _ONOFF(x) 
#define _LOG(...) __VA_ARGS__
//#define _LOG(x) 
#define _ERR(...) fprintf(stderr,"   ");fprintf(stderr,__VA_ARGS__);fflush(stderr)

///////////////////////////////////////
///////////////////////////////////////


#define _CHECK(var,fs) if(!strcmp(t,#var)){sscanf(ass,#var#fs,&var);break;}
char* paramshelper(char* x){
   static char tmp[256];
   strcpy(tmp,x);
   int i=0;
   while(tmp[i]){
      if(tmp[i]=='='){break;}
//      tmp[i]=toupper(tmp[i]); //
      i++;
   }
   if(!tmp[i]){return nullptr;}
   tmp[i]=0;
   return tmp;
}

///////////////////////////////////////
///////////////////////////////////////

using namespace chrono;
time_point<steady_clock> start;
double tik(int f=0){
   if(0==f)
   {
      start=steady_clock::now();
      return (-1.0);
   }
   else
   {
      duration<double> diff=steady_clock::now()-start;
      return diff.count();
   }
}
double tak(){
   return tik(1);
}


///////////////////////////////////////
///////////////////////////////////////

template<typename T> T sum(T* _b,T* _e){
   T ret=0;
   while(_b<_e){ret+=(*_b);_b++;}
   return ret;
}

template<typename T,typename S> void mul(T* _b,S* _e,S alfa){
   while(_b<_e){(*_b)*=alfa;_b++;}
}

template<typename T,typename S> void div(T* _b,S* _e,S alfa){
   while(_b<_e){(*_b)/=alfa;_b++;}
}

#endif

