// klasszikus pagerank szamolas
#include "common.hpp"
#include "graph.hpp"
#include "pagerank.hpp"

int main(int np,char**p){

tik();
   vector<tII> elist;
   readElist(p[1], elist);

   graph G; G.init(elist);


_LOG(_ERR("graph=%lf sec\n",tak()));

printf("V,E=%d %d\n",G.V,G.E);

   pagerankInfo pri;
   pagerank pr(pri);


    
   vector<double> prv(G.V+1);
tik();
   pr.comp(G, prv);
_LOG(_ERR("pagerank=%lf sec\n",tak()));
_LOG(_ERR("iter,diff=%d,%.12lf\n", pri.iter, pri.diff));

   destat dst;
   dst.comp(prv);
   write(dst, "pagerank");

   return 0;
}
