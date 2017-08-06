//cluster app
#include "inc.h"
#include "utils.h"
#include "graph.h"
#include "cluster.h"

int main(int np,char**p){

	tik();
   vector<tII> elist;
	//read the edgelist from command line given file
   readelist(p[1], elist); 
   graph G; G.init(elist);
   _LOG(_ERR("graph: %lf sec\n",tak()));

   destat ds;

   tik();
   ds.comp(G.deg);
   write(ds,"G.deg");
   _LOG(_ERR("G.deg stat: %lf sec\n",tak()));

   cluster cla;

   tik();
   graph rG; rG.init(G,REDUCED);
   _LOG(_ERR("reduced graph: %lf sec\n",tak()));



   // tik();
   // cla.count(G);
   // _LOG(_ERR("count: %lf sec\n",tak()));
   // ds.comp(cla.numtri);
   // write(ds,"count vector");
//   write(cla.numtri, 1, G.V+1);

   // tik();
   // cla.countR(rG);
   // _LOG(_ERR("countR: %lf sec\n",tak()));
   // ds.comp(cla.numtri);
   // ds.write("countR vector");

   // tik();
   // cla.coeff(G);
   // _LOG(_ERR("coeff: %lf sec\n",tak()));
   // ds.comp(cla.lcc);
   // write(ds,"coeff vector");

   tik();
   cla.coeff(rG, G.deg);
	_LOG(_ERR("coeffR+mean: %lf sec\n",tak()));
	

   ds.comp(cla.lcc);
   write(ds, "coeffR vector");


   return 0;
}
