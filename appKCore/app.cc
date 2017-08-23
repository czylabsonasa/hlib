// dlist  app
#include "inc.hpp"
#include "utils.hpp"
#include "graph.hpp"
#include "kcore.hpp"

int main(int np,char**p){

	tik();
   vector<tII> elist;
	//read the edgelist from command line given file
   readElist(p[1], elist); 
   graph G; G.init(elist);
   _LOG(_ERR("graph: %lf sec\n",tak()));


	kCore kcr; kcr(&G);

	tVI deg2(G.V+1,0);
	for(int s=1;s<=G.V;s++){
		int cs=kcr.loc[s];
		auto git=G.adj[s];
		while(git!=nullptr){
			int v=git->t;
			if(v>s&&kcr.loc[v]!=cs){
				++deg2[v];
				++deg2[s];
			}
			git=git->next;
		}
	}
	
	writeColVector(vector<tVI*>{&kcr.loc,&G.deg,&deg2},"_out");
	
   return 0;
}
