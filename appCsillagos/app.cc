// csillagos modell generalas es a graph letrehozasa (a tartalyon keresztul)
#include "common.h"
#include "csillagos.h"
#include "tartaly.h"
#include "graph.h"
#include "destat.h"




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
   
   graph G(csi.NV,csi.NE);
   G.init(csi.NV,T);
_LOG(_ERR("graph (tartaly)=%lf sec\n",tak()));

   destat dst;
   dst.comp(G.deg,1,G.NV+1);
   dst.write("deg:");

   return 0;
}
