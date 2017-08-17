#ifndef __ERDOSRENYI_H__
#define __ERDOSRENYI_H__

#include "common.hpp"

struct erdosrenyiInfo{
// grafparameterek
   double P;
   int N;
   int WELIST;
   int ISM;
   void defaults(){
      P=0.5;
      N=100;
      WELIST=1;
      ISM=1;
   }
//
   erdosrenyiInfo(){
      defaults();
      FILE*fp=fopen("erdosrenyi.conf","r");
      if(nullptr==fp){_ERR("config error,using defaults...");return;}
      char ass[128];//assignment
      while(1==fscanf(fp,"%s",ass)){
         char* t=paramshelper(ass);
         while(1){
            _CHECK(P,=%lf);
            _CHECK(N,=%d);
            _CHECK(WELIST,=%d);
            _CHECK(ISM,=%d);
            break;
         }
      }
      fclose(fp);
   }
};

struct erdosrenyi{
   erdosrenyiInfo& eri;
   int N;
   double P;
   erdosrenyi(erdosrenyiInfo& _eri):eri(_eri){
      N=eri.N;
      P=eri.P;
   }
   void genNaive(vector<tII>& elek){//brute force
      elek.clear();
      elek.push_back(tII{N,-1});
      for(int a=1;a<=N;a++){
         for(int b=a+1;b<=N;b++){
            if(mrand::DRND()<P){
               elek.push_back(tII{a,b});
            }
         }
      }
      elek[0].y=elek.size()-1;
      write(elek);
   }

   void genGeom(vector<tII>& elek){//geom dist
      elek.clear();
      elek.push_back(tII{N,-1});//NV,NE
      LLI kth=1;//we are at the kth edge in the row:(2,1),(3,1),(3,2)...(N,1)...(N,N-1)
      LLI NE=(LLI(N)*LLI(N-1))/2;
      while(kth<=NE){
         kth+=LLI(floor(log(1.0-mrand::DRND())/log(1.0-P)));//ennyi lepes
         if(kth>NE){break;}
         double dlth=0.5*(sqrt(8.0*kth+1.0)-1.0);
         int lth=int(dlth);
         if(floor(dlth)<dlth){
            ++lth;
         }
         
//printf("%d %d\n",kth-(lth*(lth-1))/2,lth+1);
         elek.push_back(tII{int(kth-(LLI(lth)*LLI(lth-1))/2),lth+1});
         kth++;
      }
      elek[0].y=elek.size()-1;//0th slot:.V,NE
      write(elek);
   }

   
   void write(vector<tII>& elek){
      if(eri.WELIST!=0){
         ::write(elek,"_elist");
      }
   }

};
#endif
