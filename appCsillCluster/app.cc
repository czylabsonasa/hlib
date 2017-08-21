//csillagos modell cluster app.
#include "common.hpp"
#include "graph.hpp"
#include "cluster.hpp"
#include "csillagos.hpp"
#include "tartaly.hpp"


int main(){
   mrand::init(-1);// /dev/urandom

   csillagosInfo csi;
   aTartaly T(int(csi.LEPES*csi.P*csi.NCSM));
   csillagos CS(csi,T);
   graph G; G.init(csi.LEPES+1,csi.LEPES*csi.P*csi.NCSM);
   graph rG; rG.init(csi.LEPES+1,csi.LEPES*csi.P*csi.NCSM);
   cluster cla; cla.init(csi.LEPES+csi.NCSM+1);
   


   FILE*fdeg=fopen("_degres","a");
   FILE*fclus=fopen("_clusres","a");

printf("ISM=%d\n",csi.ISM);

   for(int ism=0;ism<csi.ISM;ism++){
      CS.clear();
      CS.step1st();
      CS.gen();
      CS.write();      
      G.init(csi.V,T);
      destat ds;

      rG.init(G, iRDC);

      cla.init(G.V);
      cla.coeffR(rG, G.deg);
      ds.comp(cla.lcc);
		fprintf(fclus,"%d %.2lf %.2lf %.2lf ",csi.LEPES, csi.P, csi.Q, csi.R );
      write(ds, fclus);
      write(ds, "cluster:");

      ds.comp(G.deg);//****** referencia+rendezi !!!<<----
      write(ds, fdeg);




   }

   fclose(fdeg);
   fclose(fclus);
   return 0;
}
