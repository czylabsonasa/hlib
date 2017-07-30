//csillagos modell cluster app.
#include "common.h"
#include "graph.h"
#include "cluster.h"
#include "csillagos.h"
#include "tartaly.h"
#include "diam.h"

int main(){
   mrand::init(-1);// /dev/urandom

   csillagosInfo csi;
   aTartaly T(int(csi.LEPES*csi.P*csi.NCSM));
   csillagos CS(csi,T);


   FILE*fdeg=fopen("degres","a");
   FILE*fclus=fopen("clusres","a");
   FILE*fdiam=fopen("diamres","a");

printf("ISM=%d\n",csi.ISM);

   for(int ism=0;ism<csi.ISM;ism++){
      CS.clear();
      CS.step1();
      CS.gen();
      CS.write();      
      graph G(csi.NV,T);
      destat ds;

      ds.comp(G.deg,1,G.NV+1);
      ds.write(fdeg);

      cluster cla(G.NV+1);

      graph rG(G.NV,G.NE); cla.g2rg(G,rG);
      
      cla.coeffR(rG, G.deg);
      ds.comp(cla.lcc, 1, G.NV+1);
      ds.write(fclus);
      ds.write("cluster:");



   }
   
   fclose(fdeg);
   fclose(fclus);
   return 0;
}
