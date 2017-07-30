#ifndef __WGRAPH_H__
#define __WGRAPH_H__
#include "tartaly.h"
#include "inc.h"

struct wgraph{
   struct tINFO{int t;double w;tINFO* nxt;};
   int NV;
   int NE,aE;
   vector<tINFO*> adj;
   vector<tINFO> tar;//idx=0 unused (sentinel)
   tVI deg;
   wgraph(int _NV,int _NE):NV(_NV),NE(_NE),adj(NV+1),tar(2*NE+9),deg(NV+1){
      aE=0;
   }

//    wgraph(graph _G):NV(_G.NV),adj(NV+1),deg(_G.deg){
//       for(int s=1;s<=NV;s++){
//          const auto _B(_G.adj[s].begin());
//          const auto _E(_G.adj[s].end());
//          for(auto it=_B;it!=_E;it++){
//             insert(s,*it,0.0);
//             //deg reamins the same
//          }
//       }
//    }
//    wgraph(int _NV,const aTartaly& tar):NV(_NV),adj(NV+1),deg(NV+1){
//       const auto _B(tar.tar.begin());
//       const auto _E(tar.tar.end());
//       for(auto it=_B;it!=_E;it++){
//          insert(it->a,it->b,0.0);
//          ++deg[it->a];
//          ++deg[it->b];
//       }
//    }
   
   void clear(){
      aE=0;
   }
   void insertU(int a,int b,double w){//undirected
      auto tmp=adj[a];
      adj[a]=&tar[++aE];
      tar[aE]=tINFO{b,w,tmp};
      ++deg[a];

      tmp=adj[b];
      adj[b]=&tar[++aE];
      tar[aE]=tINFO{a,w,tmp};
      ++deg[b];
   }

   void insertD(int a,int b,double w){//directed
      auto tmp=adj[a];
      adj[a]=&tar[++aE];
      tar[aE]=tINFO{b,w,tmp};
      ++deg[a];
   }
   
};
#endif
