// csillagos modell generalas es a graph letrehozasa (a tartalyon keresztul)
#include "common.h"
#include "klikkes.h"
#include "tartaly.h"
#include "graph.h"
#include "destat.h"
#include "cluster.h"



int main(){
   mrand::init(-1);
tik();
   klikkesInfo ki;
   aTartaly T(int(ki.LEPES*ki.P*ki.NKM));
   {
      klikkes KL(ki,T);
      KL.clear();
      KL.step1();
      KL.gen();
_LOG(_ERR("model (tartaly)=%lf sec\n",tak()));
      KL.write();      
   }

tik();
   
   graph G(ki.NV,ki.NE);
   G.init(ki.NV,T);
_LOG(_ERR("graph (tartaly)=%lf sec\n",tak()));

   graph rG(G.NV, G.NE);
   rG.init(G,1);
   cluster cla(G.NV);
   cla.init(G.NV);
   cla.coeffR(rG, G.deg);

   destat dst;
   dst.comp(cla.lcc);
   dst.write("cluster:");


   dst.comp(G.deg);
   dst.write("deg:");

   return 0;
}
