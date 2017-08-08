// csillagos modell generalas es a graph letrehozasa (a tartalyon keresztul)
#include "common.hpp"
#include "csillagos.hpp"
#include "tartaly.hpp"
#include "graph.hpp"
#include "destat.hpp"


int main(){
   mrand::init(-1);//fix sorozat
tik();
   csillagosInfo csi;
   aTartaly T(int(csi.LEPES*csi.P*csi.NCSM));
   {
      csillagos CS(csi,T);
      CS.clear();
      CS.step1();
      CS.gen();
_LOG(_ERR("model (tartaly)=%lf sec\n",tak()));
      CS.write();      
   }

tik();
   
   graph G;
   G.init(csi.V,T);
_LOG(_ERR("graph (tartaly)=%lf sec\n",tak()));

   destat dst;
   dst.comp(G.deg);
   write(dst, "deg:");

   return 0;
}
