//diam csill simulatpion
#include "common.hpp"
#include "graph.hpp"
#include "diamaio.hpp"
#include "csillagos.hpp"
#include "tartaly.hpp"

// tVI simLEP{10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,500000,1000000};
// tVI simISM{   20,   20,   100,      100,    100,    50,    50,    50,    50,    30,     20,     10,     10};	

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
	tIII{5000000,20,2}
};



int main(int np,char**p){
	int multi=1;
	if(np>1){
		if(1!=sscanf(p[1],"%d",&multi)){printf("wrong multi...exit\n");exit(1);}
	}
	mrand::init(-1);

   csillagosInfo csi;
   aTartaly T(int(csi.LEPES*csi.P*csi.NCSM));
   csillagos CS(csi,T);
   graph G; G.init(csi.LEPES+1,csi.LEPES*csi.P*csi.NCSM);
   destat ds;
	tDiamAio diam;

   FILE*fdiam=fopen("_diamres","a");
	for(int m=0;m<multi;m++){
		for(int i=0;i<sim.size()&&sim[i].x<=csi.LEPES;i++){
			int LEP=sim[i].x;
			int ISM=multi*sim[i].y;
			for(int ism=0;ism<ISM;ism++){
				//8,7,6 - make it more diverse
				double tmp=0.7+mrand::DRND()*0.3;
				int aLEP=int(tmp*LEP);
				CS.clear(aLEP);
				CS.step1st();
				CS.gen();
				CS.write();      

				G.init(csi.V,T);
				diam.init(&G);
				diam.initLU(sim[i].z);//tolerance=1

				int a=diam.maxSelect();
				// int s;
				// s=dm.sweep2(a);
				diam.ifub(a);
				fprintf(fdiam,"%d %d %d %d\n",aLEP, csi.V, diam.L, diam.U);
				fflush(fdiam);
				_LOG(_ERR("********* diam, ifub: %d,%d,%d\n",m,i+1,ism+1));
			}
		}
	}//multi
	fclose(fdiam);
	//create the config for R
	fdiam=fopen("_diamres.conf","w");
	fprintf(fdiam,"%d-star | p=%.1lf q=%.1lf r=%.1lf | ? instances\n",csi.NCSM, csi.P,csi.Q,csi.R);
	fclose(fdiam);
   return 0;
}
