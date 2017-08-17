#ifndef __ARTIPT_H__
#define __ARTIPT_H__
#include "common.hpp"
#include "graph.hpp"

// declare
struct artipt{
   const graph& G;//shall we modify it?no
   tVI deg;//local copy,overwrited
   int const V;
   vector<bool> ava; //available (=1 iff not removed AP, not removed bicomponents node )
   tVI vsdNodes;//store for all nodes visited in a component
   tVI lab,low;//low: 
   tVI foundAP;//az AP-k vektora
   int tlab;//counter for prenum
   artipt(const graph&);
   void init(tModes=PARTIAL);//tModes defined in inc
   void dfs(int, int);
};

void compGAPR(graph&, tVI&);



// internal
artipt::artipt(const graph& _G):G(_G),deg(G.deg),V(G.V),
  ava(V+1),lab(V+1),low(V+1){}

void artipt::init(tModes mode){
	if(mode==PARTIAL){
		for(int i=0;i<=V;i++){
			lab[i]=low[i]=0;
		}
		return;
	}
	if(mode==FULL){
		for(int i=0;i<=V;i++){
			lab[i]=low[i]=0;
			ava[i]=true;
		}
		return;
	}
}

void artipt::dfs(int s,int prnt){
	vsdNodes.push_back(s);
_ONOFF(_LOG(_ERR("---------------in dfs: s=%d\n",s)));
	low[s]=lab[s]=++tlab;
	int nfia=0;//number of children in the dfs tree
	int wlow=0;//its childrens worst low
	int dg=1;//deg[s] a residual grafban
	auto it=G.adj[s];
	while(it!=nullptr){
		int t=(it->t);
		if(true==ava[t]){//unremoved
			++dg;
			if(0==lab[t]){//unvis
				dfs(t,s);
				low[s]=min(low[s],low[t]);
				wlow=max(wlow,low[t]);
				++nfia;
			}else{
				if(t!=prnt){//the child is not parent
					low[s]=min(low[s],lab[t]);//low[t]?no.
				}
			}
		}
		it=(it->next);
	}
	if(0==prnt){//root node  
		deg[s]=dg-1;//starting from 1
		if(nfia>1){
			foundAP.push_back(s);
		}
	}
	else{
		deg[s]=dg;
		if(nfia>0&&wlow>=lab[s]){//nfia>0 is unneeded
			foundAP.push_back(s);
		}
	}
	return;
}


//~ void compAPTA(graph& G,tVI& out){
//~ _LOG(_ERR("**************\n hi, this is APTA!\n**************\n"));
   //~ artp art(G);
   //~ art.init(false);//partial=false
   //~ int rm=0;
   //~ while(1){
      //~ art.init(true);
      //~ for(int i=1;i<=G.V;i++){
         //~ if(0==art.lab[i]&&0!=art.node2cid[i]){
            //~ art.AP(i);
         //~ }
      //~ }
      //~ //search and remove for the most destructive AP
//~ _ERR(_LOG("artpontok szama: %d\n",int(art.foundAP.size())));   
      //~ if(!art.remove()){break;}
      //~ ++rm;
   //~ }
//~ _ERR(_LOG("no of rm-s:%d\n",rm));   
//~ }


// external def
void compGAPR(graph& G,tVI& info){//info[]
_LOG(_ERR("**************\n"));
_LOG(_ERR("hi, this is GAPR!\n"));
_LOG(_ERR("**************\n"));
   artipt art(G);
   art.init(FULL);//zeroing all stuff
   int run=0;//searching and removing all AP-s found in a run
   int tipus=0;
   while(1){
      ++run;
      art.init(PARTIAL);
      bool volt=false;
      for(int s=1;s<=G.V;s++){//this is a run
_ONOFF(_LOG(_ERR("   run=%d node=%d\n",run,s)));
         if(0==art.lab[s]&&true==art.ava[s]){
            art.vsdNodes.clear();
            art.tlab=0;//ez a dfsnum
            art.foundAP.clear();
            art.dfs(s,0);
            if(art.foundAP.size()>0){
               volt=true;
               for(auto it=art.foundAP.begin();it!=art.foundAP.end();it++){
                  info[*it]=(-run);//same for all AP in one run
                  art.ava[*it]=false;
               }
            }else{
               ++tipus; //different for all component (even for size 1)
               for(auto it=art.vsdNodes.begin();it!=art.vsdNodes.end();it++){
                  info[*it]=tipus;
                  art.ava[*it]=false;
               }
            }
         }
      }//for(s)
      if(false==volt){break;}
   }//w(1)
_ONOFF(_ERR(_LOG("no of runs:%d\n",run)));   

}

#endif
