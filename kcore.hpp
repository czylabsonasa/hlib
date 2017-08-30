// a fixed size (V+1+2*(dmax+1)) collection of doubly linked lists
#ifndef __KCORE_H__
#define __KCORE_H__
#include "common.hpp"
#include "llist.hpp"

//declare

struct kCore{
	tVI loc;
	tVI dist;
   tLlist llst; 
	void operator()(graph* _G){
		graph& G(*_G);
		int dmax=*max_element(G.deg.begin()+1,G.deg.end());
		llst.init(dmax,G.V);
		loc.resize(1+G.V);
		for(int i=1;i<=G.V;i++){
			loc[i]=G.deg[i];
			llst.push_back(i,loc[i]);//v,h
		}
		for(int d=1;d<dmax;d++){//d<dmax
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
		int mx=*max_element(loc.begin(),loc.end());
		dist.resize(mx+1);
		fill(dist.begin(),dist.end(),0);
		for(int i=1;i<=G.V;i++){
			++dist[loc[i]];
		}
	}
};


#endif
