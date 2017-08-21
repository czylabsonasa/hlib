//csillagos modell cluster app.
#include "common.hpp"
#include "graph.hpp"
#include "cluster.hpp"
#include "klikkes.hpp"
#include "tartaly.hpp"


tVI simLEP{100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000,2000000,5000000,10000000};
tVI simISM{100,   100,   100,   100,   100,   50,    50,    50,    50,    30,     20,     10,     10};	

int main(){
   mrand::init(-1);// /dev/urandom

   klikkesInfo ki;
   aTartaly T(int(ki.LEPES*ki.P*ki.NKM));
   klikkes KL(ki,T);
   graph G; G.init(ki.LEPES+1,ki.LEPES*ki.P*ki.NKM);
   graph rG; rG.init(ki.LEPES+1,ki.LEPES*ki.P*ki.NKM);
   cluster cla; cla.init(ki.LEPES+ki.NKM+1);
   


   FILE*fdeg=fopen("_degres","a");
   FILE*fclus=fopen("_clusres","a");

	//	fprintf(stderr,"ISM=%d\n",ki.ISM);

	for(int i=0;i<simLEP.size()&&simLEP[i]<=ki.LEPES;i++){
		int LEP=simLEP[i];
		for(int ism=0;ism<simISM[i];ism++){
			KL.clear(LEP);
			KL.step1st();
			KL.gen();
			KL.write();      
			G.init(ki.V,T);
			destat ds;

			rG.init(G, iRDC);

			cla.init(G.V);
			cla.coeffR(rG, G.deg);
			ds.comp(cla.lcc);
			fprintf(fclus,"%d %.2lf %.2lf %.2lf %d ",LEP, ki.P, ki.Q, ki.R , ki.NKM );
			write(ds, fclus);
			write(ds, "klikkes cluster:");

			ds.comp(G.deg);//****** referencia+rendezi !!!<<----
			write(ds, fdeg);
		}//ismm
	}//lep

   fclose(fdeg);
   fclose(fclus);
   return 0;
}
