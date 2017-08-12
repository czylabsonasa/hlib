//bfs app, testing bfs header
#include "inc.hpp"
#include "utils.hpp"
#include "graph.hpp"
#include "bfs.hpp"
#include "diam.hpp"

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


	

	{
		diam dm; dm.init(&G);
		tik();
		printf("diam=%d\n",dm.bruteforce());
		_LOG(_ERR("********* diam, bruteforce: %lf sec\n",tak()));
	}


	{
		tik();
		tBfs fifo; fifo.init(&G);
		int mx=0;
		for(int s=1;s<=G.V;s++){
			fifo.clear();
			fifo.insert(s);
			int tmx=fifo.dist[fifo()];
			mx=max(mx,tmx);
		}
		printf("diam=%d\n",mx);
		_LOG(_ERR("********* diam, bfs struct: %lf sec\n",tak()));
	}

	{
		tik();
		tBfs fifo; fifo.init(&G);fifo.set(PATH);
		tVI d(G.V+1,0);
		int L=1;
		int U=G.V-1;
		int s=1;
		for(;s<=G.V && U-L>2;s++){
			fifo.clear();
			fifo.insert(s);
			int tL=fifo.dist[fifo()];
			L=max(L,tL);


			fill(d.begin(),d.end(),0);
			int tU=0;
			tVI& from(fifo.from);
			tVI& que(fifo.que);
			int i=G.V-1;
			while(i>0){
				int a=que[i--];
				int& dfa(d[from[a]]);
				int td=d[a]+1;
				tU=max(tU,td+dfa);
				dfa=max(dfa,td);
			}
			U=min(tU,U);
			//			printf("s,U:%d,%d\n",s,U);
		}
		printf("diam: s,L,U=%d,%d,%d\n",s,L,U);
		_LOG(_ERR("********* diam, bfs struct: %lf sec\n",tak()));
	}
	
	return 0;
}
