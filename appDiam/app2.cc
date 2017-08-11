//diam app
#include "inc.hpp"
#include "utils.hpp"
#include "graph.hpp"
#include "diam.hpp"
#include "artipt.hpp"

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


	artipt ap(G);
	ap.init(FULL);
	ap.dfs(1,0);
	int a=ap.foundAP[0];//search for most dense ap 
	int da=G.deg[a];
	for(int i=1;i<ap.foundAP.size();i++){
		int t=ap.foundAP[i];
		if(G.deg[t]>da){a=t;da=G.deg[t];}
	}

	printf("start point:  node,deg=%d,%d\n",a,da);
	//	return 0;
	
	diam dm; dm.init(&G);

	tik();
	dm.initLU();
	printf("diam=%d\n",dm.ifub(a));
	_LOG(_ERR("********* diam, ifub: %lf sec\n",tak()));


	


   return 0;
}
