//diam all in one test
//TODO make faster
#include "inc.hpp"
#include "utils.hpp"
#include "graph.hpp"
#include "diamaio.hpp"

int main(int np,char**p){
	//	int sp=1;sscanf(p[2],"%d",&sp);
	
	tik();
   vector<tII> elist;
	//read the edgelist from command line given file
   readElist(p[1], elist); 
   graph G; G.init(elist);
   destat ds;
   ds.comp(G.deg);
   write(ds,"G.deg");
   _LOG(_ERR("********* build graph from elist: %lf sec\n",tak()));


	tDiamAio dm; dm.init(&G);

	// tik();
	// printf("diam=%d\n",dm.bruteForce());
   // _LOG(_ERR("********* diam, bruteForce: %lf sec\n",tak()));

	// tik();
	// dm.initLU();
	// printf("diam=%d\n",dm.bruteForce2());
   // _LOG(_ERR("********* diam, bruteForce2: %lf sec\n",tak()));

	// return 0;
	

	// tik();
	// dm.initLU();
	// printf("diam=%d\n",dm.ifub(G.V/2));
   // _LOG(_ERR("********* diam, ifub: %lf sec\n",tak()));

	
	// tik();
	// dm.initLU();
	// printf("diam=%d\n",dm.ifub(dm.maxSelect()));
	// //printf("diam=%d\n",dm.ifub(dm.sweep2(1)));

	dm.initLU(0);
	for(int sp=1;sp<=30;sp++){
		tik();
		// int a=dm.maxSelect();
		// int s;

		// s=dm.sweep2(dm.minSelect());
		// printf("sweep2\n --- L:%d U:%d ",dm.L,dm.U);
		// printf("\n --- node,deg=%d,%d\n\n",s,G.deg[s]);
		// s=dm.sweep2(s);
		// printf("sweep2\n --- L:%d U:%d ",dm.L,dm.U);
		// printf("\n --- node,deg=%d,%d\n\n",s,G.deg[s]);
		// // s=dm.sweep2(s);
		// // printf("sweep2\n --- L:%d U:%d ",dm.L,dm.U);
		// // printf("\n --- node,deg=%d,%d\n\n",s,G.deg[s]);
		// // s=dm.sweep2(s);
		// // printf("sweep2\n --- L:%d U:%d ",dm.L,dm.U);
		// // printf("\n --- node,deg=%d,%d\n\n",s,G.deg[s]);
		// // s=dm.sweep2(s);
		// // printf("sweep2\n --- L:%d U:%d ",dm.L,dm.U);
		// // printf("\n --- node,deg=%d,%d\n\n",s,G.deg[s]);

		
		
		
		
		//	dm.sweep2(dm.sweep2(dm.sweep2(1)));
		printf("diam=%d\n",dm.ifub(sp));
		_LOG(_ERR("********* diam, ifub+sweep2: %lf sec\n",tak()));
			printf("%d %d\n",dm.L,dm.U);

		printf("diam=%d\n",dm.ifub(G.V+1-sp));
		_LOG(_ERR("********* diam, ifub+sweep2: %lf sec\n",tak()));
			printf("%d %d\n",dm.L,dm.U);


	}


	// {
	// 	tik();
	// 	dm.initLU();
	// 	int a=dm.minSelect();
	// 	int da=G.deg[a];
	// 	printf("start point:  node,deg=%d,%d\n",a,da);
	
	// 	//	dm.sweep2(dm.sweep2(dm.sweep2(1)));
	// 	printf("diam=%d\n",dm.ifubv2(a));
	// 	_LOG(_ERR("********* diam, ifub+sweep2+new: %lf sec\n",tak()));
	// }

	


   return 0;
}
