//csillagos modell cluster app.
#include "common.hpp"
#include "graph.hpp"
#include "cluster.hpp"
#include "csillagos.hpp"
#include "tartaly.hpp"


tVI simLEP{100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000,2000000,5000000,10000000};
tVI simISM{100,   100,   100,   100,   100,   50,    50,    50,    50,    30,     20,     10,     10};	

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

	//	fprintf(stderr,"ISM=%d\n",csi.ISM);

	for(int i=0;i<simLEP.size()&&simLEP[i]<=csi.LEPES;i++){
		int LEP=simLEP[i];
		for(int ism=0;ism<simISM[i];ism++){
			CS.clear(LEP);
			CS.step1st();
			CS.gen();
			CS.write();      
			G.init(csi.V,T);
			destat ds;

			rG.init(G, iRDC);

			cla.init(G.V);
			cla.coeffR(rG, G.deg);
			ds.comp(cla.lcc);
			fprintf(fclus,"%d %.2lf %.2lf %.2lf %d ",LEP, csi.P, csi.Q, csi.R, csi.NCSM );
			write(ds, fclus);
			write(ds, "cluster:");

			ds.comp(G.deg);//****** referencia+rendezi !!!<<----
			write(ds, fdeg);
		}//ismm
	}//lep

   fclose(fdeg);
   fclose(fclus);
   return 0;
}
