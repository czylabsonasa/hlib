//csillagos modell cluster app.
#include "common.h"
#include "graph.h"
#include "cluster.h"
#include "csillagos.h"
#include "tartaly.h"


int main(){
   mrand::init(-1);// /dev/urandom

   csillagosInfo csi;
   aTartaly T(int(csi.LEPES*csi.P*csi.NCSM));
   csillagos CS(csi,T);
   graph G(csi.LEPES+1,csi.LEPES*csi.P*csi.NCSM);
   graph rG(csi.LEPES+1,csi.LEPES*csi.P*csi.NCSM);
   cluster cla(csi.LEPES+csi.NCSM+1);
   


   FILE*fdeg=fopen("_degres","a");
   FILE*fclus=fopen("_clusres","a");

printf("ISM=%d\n",csi.ISM);

   for(int ism=0;ism<csi.ISM;ism++){
      CS.clear();
      CS.step1();
      CS.gen();
      CS.write();      
      G.init(csi.NV,T);
      destat ds;

      rG.init(G,1);

      cla.init(G.NV);
      cla.coeffR(rG, G.deg);
      ds.comp(cla.lcc);
      ds.write(fclus);
      ds.write("cluster:");

      ds.comp(G.deg);//****** referencia+rendezi !!!<<----
      ds.write(fdeg);




   }

   fclose(fdeg);
   fclose(fclus);
   return 0;
}
