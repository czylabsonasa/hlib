#include "common.h"
#include "csillagos.h"
#include "tartaly.h"
#include "graph.h"
#include "wgraph.h"
#include "artipt.h"


int main(){

   mrand::init(22);//fix sorozat
tik();
   csillagosInfo csi;
   aTartaly T(int(csi.LEPES*csi.P*csi.NCSM));
   {
      csillagos CS(csi,T);
      CS.clear();
      CS.step1();
      CS.gen();
      CS.write();      
   }
_LOG(_ERR("model (tartaly)=%lf sec\n",tak()));

tik();
   graph G(csi.NV,T);
_LOG(_ERR("graph (tartaly)=%lf sec\n",tak()));
_LOG(_ERR("NV,NE=%d,%d\n",G.NV,G.NE));

  
   //compAPTA(G);
tik();
   tVI info(G.NV+1);
   compGAPR(G,info);
_LOG(_ERR("GAPR lasted %lf sec\n",tak()));


   {
      int nAP=0;
      tVI frek(G.NV+1,0);
      for(int i=1;i<=G.NV;i++){
         if(info[i]==-1){++nAP;continue;}
         if(info[i]>0){
//assert(info[i]<=G.NV);
            ++frek[info[i]];
         }
      }
      int mx=0;int fmx=0;
      for(int i=1;i<=G.NV;i++){
         if(frek[i]>mx){mx=frek[i];fmx=1;continue;}
         if(frek[i]==mx){++fmx;}
      }
      printf("V=%d AP=%d rgb=%d (%d)\n",G.NV,nAP,mx,fmx);
   }

   return 0;
}
