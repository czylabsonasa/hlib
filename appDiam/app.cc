//diam app
#include "inc.hpp"
#include "utils.hpp"
#include "graph.hpp"
#include "diam.hpp"

int main(int np,char**p){

	tik();
   vector<tII> elist;
	//read the edgelist from command line given file
   readelist(p[1], elist); 
   graph G; G.init(elist);
   destat ds;
   ds.comp(G.deg);
   write(ds,"G.deg");
   _LOG(_ERR("********* build graph from elist: %lf sec\n",tak()));


	diam dm; dm.init(&G);

	// tik();
	// printf("diam=%d\n",dm.bruteforce());
   // _LOG(_ERR("********* diam, bruteforce: %lf sec\n",tak()));

	// tik();
	// dm.initLU();
	// printf("diam=%d\n",dm.bruteforce2());
   // _LOG(_ERR("********* diam, bruteforce2: %lf sec\n",tak()));


	// tik();
	// dm.initLU();
	// printf("diam=%d\n",dm.ifub(G.V/2));
   // _LOG(_ERR("********* diam, ifub: %lf sec\n",tak()));

	
	// tik();
	// dm.initLU();
	// printf("diam=%d\n",dm.ifub(dm.maxselect()));
	// //printf("diam=%d\n",dm.ifub(dm.sweep2(1)));

	tik();
	dm.initLU();
	int a=dm.maxselect();
	int da=G.deg[a];
	printf("start point:  node,deg=%d,%d\n",a,da);
	
	//	dm.sweep2(dm.sweep2(dm.sweep2(1)));
	printf("diam=%d\n",dm.ifub(dm.maxselect()));
	_LOG(_ERR("********* diam, ifub+sweep2: %lf sec\n",tak()));
	//	printf("%d %d\n",dm.L,dm.U);


	


   return 0;
}
