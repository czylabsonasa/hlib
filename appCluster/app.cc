//csillagos modell cluster app.
#include "common.h"
#include "graph.h"
#include "cluster.h"

int main(int np,char**p){

   tik(); 
   vector<tII> elist;
   readelist(p[1], elist); //read from file
   graph G(elist[0].x, elist[0].y); 
   G.init(elist);
   _LOG(_ERR("graph: %lf sec\n",tak()));

   destat ds;
//~ ds.comp(tVD{1,2,3,4,5,6},0,6);
//~ ds.write("proba");
//~ return 0;

   tik();
   ds.comp(G.deg,1,G.NV+1);
   ds.write("G.deg");
   _LOG(_ERR("G.deg stat: %lf sec\n",tak()));

   cluster cla(G.NV+1);

   tik();
   graph rG(G.NV,G.NE); cla.g2rg(G,rG);
   _LOG(_ERR("reduced graph: %lf sec\n",tak()));



   tik();
   cla.count(G);
   _LOG(_ERR("count: %lf sec\n",tak()));
   ds.comp(cla.numtri, 1, G.NV+1);
   ds.write("count vector");
//   write(cla.numtri, 1, G.NV+1);

   tik();
   cla.countR(rG);
   _LOG(_ERR("countR: %lf sec\n",tak()));
   ds.comp(cla.numtri,1,G.NV+1);
   ds.write("countR vector");

   tik();
   cla.coeff(G);
   _LOG(_ERR("coeff: %lf sec\n",tak()));
   ds.comp(cla.lcc, 1, G.NV+1);
   ds.write("coeff vector");

   tik();
   cla.coeffR(rG, G.deg);
   _LOG(_ERR("coeffR: %lf sec\n",tak()));
   ds.comp(cla.lcc, 1, G.NV+1);
   ds.write("coeffR vector");


   return 0;
}
