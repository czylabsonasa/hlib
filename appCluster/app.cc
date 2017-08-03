//cluster app
#include "inc.h"
#include "utils.h"
#include "graph.h"
#include "cluster.h"

int main(int np,char**p){

   tik(); 
   vector<tII> elist;
   readelist(p[1], elist); //read from file
   graph G;
	G.init(elist);
   _LOG(_ERR("graph: %lf sec\n",tak()));

   destat ds;
	// tVD v{0,1,2,3,4,5,6};
	// ds.comp(v);
	// ds.write("proba");
	// return 0;

   tik();
   ds.comp(G.deg);
   ds.write("G.deg");
   _LOG(_ERR("G.deg stat: %lf sec\n",tak()));

   cluster cla(G.V);

   tik();
   graph rG; rG.init(G,REDUCED);
   _LOG(_ERR("reduced graph: %lf sec\n",tak()));



   tik();
   cla.count(G);
   _LOG(_ERR("count: %lf sec\n",tak()));
   ds.comp(cla.numtri);
   ds.write("count vector");
//   write(cla.numtri, 1, G.V+1);

   // tik();
   // cla.countR(rG);
   // _LOG(_ERR("countR: %lf sec\n",tak()));
   // ds.comp(cla.numtri);
   // ds.write("countR vector");

   tik();
   cla.coeff(G);
   _LOG(_ERR("coeff: %lf sec\n",tak()));
   ds.comp(cla.lcc);
   ds.write("coeff vector");

   // tik();
   // cla.coeffR(rG, G.deg);
   // _LOG(_ERR("coeffR: %lf sec\n",tak()));
   // ds.comp(cla.lcc);
   // ds.write("coeffR vector");


   return 0;
}
