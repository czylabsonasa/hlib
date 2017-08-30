//klikkes modell cluster app.
#include "common.hpp"
#include "graph.hpp"
#include "cluster.hpp"
#include "klikkes.hpp"
#include "tartaly.hpp"


// tVI simLEP{100000,200000,300000,400000,500000,600000,700000,800000,900000,1000000,2000000,5000000,10000000};
// tVI simISM{100,   100,   100,   100,   100,   50,    50,    50,    50,    30,     20,     10,     10};	

tVIII sim{
	tIII{10000,50,0},
	tIII{20000,50,0},
	tIII{30000,50,0},
	tIII{40000,50,0},
	tIII{50000,50,1},
	tIII{60000,50,1},
	tIII{70000,50,1},
	tIII{80000,50,1},
	tIII{90000,50,1},
	tIII{100000,30,2},
	tIII{150000,30,2},
	tIII{200000,30,2},
	tIII{250000,30,2},
	tIII{300000,30,2},
	tIII{350000,30,2},
	tIII{400000,30,2},
	tIII{450000,30,2},
	tIII{500000,30,2},
	tIII{600000,30,2},
	tIII{700000,30,2},
	tIII{800000,30,2},
	tIII{1000000,20,2},
	tIII{1500000,20,2},
	tIII{2000000,20,2},
	tIII{3000000,20,2},
	tIII{5000000,20,2},
	tIII{70000000,10,2},
	tIII{10000000,10,2}
};




int main(int np,char**p){
	int multi=1;//multiplier for the sim (number of graph instances generated)
	if(np>1){
		if(1!=sscanf(p[1],"%d",&multi)){_ERR("wrong multi...exit\n");exit(1);}
	}
	
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

	for(int i=10;i<sim.size()&&sim[i].x<=ki.LEPES;i++){
		int LEP=sim[i].x;
		int ISM=sim[i].y;
		for(int ism=0;ism<ISM;ism++){
			double tmp=0.7+mrand::DRND()*0.3;
			int aLEP=int(tmp*LEP);
			KL.clear(aLEP);
			KL.step1st();
			KL.gen();
			KL.write();      
			G.init(ki.V,T);
			destat ds;

			rG.init(G, iRDC);

			cla.init(G.V);
			cla.coeffR(rG, G.deg);
			ds.comp(cla.lcc);
			fprintf(fclus,"%d %.2lf %.2lf %.2lf %d ",aLEP, ki.P, ki.Q, ki.R , ki.NKM );
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
