//cluster app
// iRDC a nyero
#include "inc.hpp"
#include "utils.hpp"
#include "graph.hpp"
#include "cluster.hpp"

int main(int np,char**p){

	tik();
   vector<tII> elist;
	//read the edgelist from command line given file
   readElist(p[1], elist); 
   graph G; G.init(elist);
   _LOG(_ERR("graph: %lf sec\n",tak()));

   destat ds;

   tik();
   ds.comp(G.deg);
   write(ds,"G.deg");

   cluster cla;

	{
		tik();
		cla.coeff(G, G.deg);
		_LOG(_ERR("vanilla coeff+mean: %lf sec\n",tak()));
	}

	{
		tik();
		cla.coeffR2(G, G.deg);
		_LOG(_ERR("R2 coeff+mean: %lf sec\n",tak()));
	}

	
	{
		tik();
		graph rG; rG.init(G, dRDC);
		cla.coeffR(rG, G.deg);
		_LOG(_ERR("dRDC coeff+mean: %lf sec\n",tak()));
	}

	{
		tik();
		graph rG; rG.init(G, d2RDC);
		cla.coeffR(rG, G.deg);
		_LOG(_ERR("d2RDC coeff+mean: %lf sec\n",tak()));
	}
	
	{
		tik();
		graph rG; rG.init(G, iRDC);
		cla.coeffR(rG, G.deg);
		_LOG(_ERR("iRDC coeff+mean: %lf sec\n",tak()));
	}

   ds.comp(cla.lcc);
   write(ds, "coeffR vector");

   return 0;
}
