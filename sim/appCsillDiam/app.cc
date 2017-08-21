//diam csill simulatpion
#include "common.hpp"
#include "graph.hpp"
#include "diamaio.hpp"
#include "csillagos.hpp"
#include "tartaly.hpp"

// tVI simLEP{10000,20000,30000,40000,50000,60000,70000,80000,90000,100000,200000,500000,1000000};
// tVI simISM{   20,   20,   100,      100,    100,    50,    50,    50,    50,    30,     20,     10,     10};	

tVIII sim{
	tIII{10000,30,0},
	tIII{20000,30,0},
	tIII{30000,30,0},
	tIII{40000,30,0},
	tIII{50000,30,1},
	tIII{60000,30,1},
	tIII{70000,30,1},
	tIII{80000,30,1},
	tIII{90000,30,1},
	tIII{100000,30,2}
	// tIII{150000,20,2},
	// tIII{200000,20,2},
	// tIII{250000,20,2},
	// tIII{300000,20,2},
	// tIII{350000,20,2},
	// tIII{400000,20,2},
	// tIII{450000,20,2},
	// tIII{500000,20,2},
	// tIII{1000000,20,2},
	// tIII{2000000,20,2}
};



int main(){

   csillagosInfo csi;
   aTartaly T(int(csi.LEPES*csi.P*csi.NCSM));
   csillagos CS(csi,T);
   graph G; G.init(csi.LEPES+1,csi.LEPES*csi.P*csi.NCSM);
   destat ds;
	tDiamAio diam;

   FILE*fdiam=fopen("_diamres","a");
	
	for(int i=0;i<sim.size()&&sim[i].x<=csi.LEPES;i++){
		int LEP=sim[i].x;
		for(int ism=0;ism<sim[i].y;ism++){
			CS.clear(LEP);
			CS.step1st();
			CS.gen();
			CS.write();      
			G.init(csi.V,T);
			diam.init(&G);
			diam.initLU(2);//tolerance=1

			int a=diam.maxSelect();
			// int s;
			// s=dm.sweep2(a);
			diam.ifub(a);
			fprintf(fdiam,"%d %d %d %d\n",csi.LEPES,csi.V,diam.L,diam.U);
			_LOG(_ERR("********* diam, ifub: %d,%d\n",i+1,ism+1));
		}

	}
	fclose(fdiam);

   return 0;
}
