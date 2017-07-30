#ifndef __DESTAT_H__
#define __DESTAT_H__
#include "inc.h"

struct destat{
   double _mean, _sigma;
   double _min , _max, _R;
   int _N;
   template<typename T> void comp(vector<T>& v){//copy or reference???
      _N=v.size()-1;//0 nem hasznalt
      _min=_max=v[1]; 
      _mean=0.0;_sigma=0.0;
      for(int i=1;i<=_N;i++){
         T vi=v[i];
         if(vi>_max){_max=vi;}
         if(vi<_min){_min=vi;}
         _mean+=vi;         
         _sigma+=double(vi)*double(vi);
      }
      _R=_max-_min;
      _mean=_mean/double(_N);
      _sigma=sqrt(_sigma/double(_N)-_mean*_mean);
   }

   void prop2frek(vector<int>& prop, vector<int>& frek){
      int const NV=prop.size()-1;//0 nem hasznalt
      sort(prop.begin()+1, prop.end());
      frek.resize(prop[NV]);
   }

   void write(const char* _name){
      const char*const tmp=" ******* ";
      printf("\n%s%s%s\nN=%d min=%.3lf max=%.3lf R=%.3lf\nmean=%.8lf sigma=%.8lf\n\n"
      ,tmp,_name,tmp,
      _N,_min,_max,_R,_mean,_sigma);
   }
   void write(FILE* fp){
      fprintf(fp,"%d %.8lf %.8lf %.8lf %.8lf\n",
      _N,_min,_max,_mean,_sigma);
   }


};



#endif

