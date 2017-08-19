// dlist  app
#include "inc.hpp"
#include "utils.hpp"
#include "graph.hpp"
#include "llist.hpp"

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
	int dmax=ds._max;
   _LOG(_ERR("destat: %lf sec\n",tak()));

	

   tik();
	tVI loc(G.V+1);
   tLlist llst; llst.init(dmax,G.V);
	for(int i=1;i<=G.V;i++){
		loc[i]=G.deg[i];
		llst.push_back(i,loc[i]);//v,h
	}
   _LOG(_ERR("llist: %lf sec\n",tak()));


   // tik();
	// write(llst);
   // _LOG(_ERR("llist write %lf sec\n",tak()));

	
	
	tik();
	for(int d=1;d<=llst.H;d++){
		//		fprintf(fp,"%d(%d):",d,llst.heads[d]->val);
		auto lit=llst.heads[d]->next;
		while((lit->next)!=nullptr){
			auto git=G.adj[lit->val];
			while(git!=nullptr){
				int v=git->t;
				if(loc[v]>d){
					llst.remove(v,loc[v]);
					llst.push_back(v,--loc[v]);
				}
				git=git->next;
			}
			lit=lit->next;
		}
	}

	writeColVector(vector<tVI*>{&loc,&G.deg},"_out");
	
	int h=dmax;
	while(llst.heads[h]->val==0){h--;}
	loc.resize(h+1);
	while(h>=0){
		loc[h]=llst.heads[h]->val;
		h--;
	}
   _LOG(_ERR("kcore compute %lf sec\n",tak()));
	
	
	tik();
	writeVector(loc,"_kcoredist");
   _LOG(_ERR("llist write to file %lf sec\n",tak()));
	
	
   // _LOG(_ERR("kcore %lf sec\n",tak()));
   // tik();
	// write(llst);
   // _LOG(_ERR("kcore write %lf sec\n",tak()));

	
	
	

   return 0;
}
