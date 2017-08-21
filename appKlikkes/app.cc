// klikkes modell generalas es a graph letrehozasa (a tartalyon keresztul)
#include "common.hpp"
#include "klikkes.hpp"
#include "tartaly.hpp"
#include "graph.hpp"
#include "destat.hpp"
#include "cluster.hpp"



int main(){
   mrand::init(1123);
tik();
   klikkesInfo ki;
   aTartaly T(int(ki.LEPES*ki.P*ki.NKM));
   {
      klikkes KL(ki, T);
      KL.clear();
      KL.step1st();
      KL.gen();
_LOG(_ERR("model (tartaly)=%lf sec\n",tak()));
      KL.write();      
   }

tik();

   graph G; G.init(ki.V, T);

_LOG(_ERR("graph (tartaly)=%lf sec\n",tak()));

   tik();
   graph rG(G.V, G.E);

   rG.init(G, dRDC);
   cluster cla; cla.init(G.V);
   cla.coeffR(rG, G.deg);

   destat dst;
   dst.comp(cla.lcc);
   write(dst, "cluster:");

   dst.comp(G.deg);
   write(dst, "deg:");

fprintf(stderr,"tobbi: %lf sec\n",tak());

   return 0;
}
