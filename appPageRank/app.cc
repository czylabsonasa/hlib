// klasszikus pagerank szamolas
#include "common.h"
#include "graph.h"
#include "pagerank.h"

int main(int np,char**p){

tik();
   vector<tII> elist;
   readelist(p[1], elist);
   graph G(elist[0].x, elist[0].y);

   G.init(elist);


_LOG(_ERR("graph=%lf sec\n",tak()));

printf("NV,NE=%d %d\n",G.NV,G.NE);

   pagerankInfo pri;
   pagerank pr(pri);


    
   vector<double> prv(G.NV+1);
tik();
   pr.comp(G,prv);
_LOG(_ERR("pagerank=%lf sec\n",tak()));
_LOG(_ERR("iter,diff=%d,%.12lf\n", pri.iter, pri.diff));

   destat dst;
   dst.comp(prv,1,G.NV+1);
   dst.write("pagerank");

   return 0;
}
