#include "inc.hpp"
#include "mrand.hpp"
#include "csillagos.hpp"
#include "tartaly.hpp"
#include "graph.hpp"
#include "wgraph.hpp"
#include "artipt.hpp"
#include "pagerank.hpp"



int main(){

   mrand::init(-1);
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
 graph G; G.init(csi.V,T);
_LOG(_ERR("graph (tartaly)=%lf sec\n",tak()));

  
   //compAPTA(G);
tik();
   tVI info(G.V+1);
   compGAPR(G,info);
_LOG(_ERR("GAPR lasted %lf sec\n",tak()));


   {
      int nAP=0;
      tVI frek(G.V+1,0);
      for(int i=1;i<=G.V;i++){
         if(info[i]==-1){++nAP;continue;}
         if(info[i]>0){
//assert(info[i]<=G.V);
            ++frek[info[i]];
         }
      }
      int mx=0;int fmx=0;
      for(int i=1;i<=G.V;i++){
         if(frek[i]>mx){mx=frek[i];fmx=1;continue;}
         if(frek[i]==mx){++fmx;}
      }
      _ERR("V=%d AP=%d rgb=%d (%d)\n",G.V,nAP,mx,fmx);
   }

   _ERR("num of edges %d\n",G.E);

   pagerankInfo pri;
   pagerank pr(pri);
   vector<double> infopr(G.V+1);
tik();
   pr.comp(G,infopr);
_LOG(_ERR("pagerank=%lf sec\n",tak()));

   for(int i=1;i<=G.V;i++){
      printf("%5d %lf %d\n",info[i],100*infopr[i],G.deg[i]);
   }
   double s=0.0;
   for(int i=1;i<=G.V;i++){
      if(info[i]<0){
         s+=infopr[i];
      }
   }
   _ERR("sum pageranks removed ap-s: %lf\n",s);



   


   return 0;
}
