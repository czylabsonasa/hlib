#ifndef __GRAPH2_H__
#define __GRAPH2_H__
#include "tartaly.h"
#include "inc.h"

//a sima graph atirata (NE vel varialok)
struct graph{//maxV altalaban ismert, de maxE változhat 
   struct tINFO{int t;tINFO* nxt;};
   int const maxV;
   int const maxE;
   int NV;
   int NE,iE;
   vector<tINFO*> adj;
   vector<tINFO> lista;
   tVI deg;
   graph(int const _maxV,int const _maxE):maxV(_maxV),maxE(_maxE),
   NV(0),NE(0),iE(0),adj(maxV+1),lista(2*maxE+9),deg(maxV+1){
      iE=0;
   }
   
   void init(int _NV, int _NE){
      NV=_NV;
      NE=_NE;
      adj.resize(NV+1);
      deg.resize(NV+1);
      for(int s=1;s<=NV;s++){
         adj[s]=nullptr;
         deg[s]=0;
      }
      lista.resize(2*NE+1);
      iE=0;
   }
   
   void init(const graph& G, int mode){
      if(0==mode){}
      if(1==mode){
         init(G.NV,G.NE);
         for(int s=1;s<=G.NV;s++){
            auto it=G.adj[s];
            while(it!=nullptr){
               if((it->t)>s){
                  insertD(s,it->t);
               }
               it=(it->nxt);
            }
         }
      }
   }

   void init(int _NV,const aTartaly& tar){
      init(_NV,tar.meret);
      const auto _B(tar.tar.begin());
      const auto _E(tar.tar.end());
      for(auto it=_B;it!=_E;it++){
         insertU(it->x,it->y);
      }
   }

   void init(const vector<tII>& elist){
      init(elist[0].x, elist[0].y);
      for(int i=1;i<=NE;i++){
         insertU(elist[i].x, elist[i].y);
      }
   }

   void insertU(int a,int b){//undirected
      auto tmp=adj[a];
      adj[a]=&lista[++iE];
      lista[iE]=tINFO{b,tmp};
      ++deg[a];

      tmp=adj[b];
      adj[b]=&lista[++iE];
      lista[iE]=tINFO{a,tmp};
      ++deg[b];
   }

   void insertD(int a,int b){//directed
      auto tmp=adj[a];
      adj[a]=&lista[++iE];
      lista[iE]=tINFO{b,tmp};
      ++deg[a];
   }
   
};


void write(const graph& G,const char* const fname){
   FILE*fp=fopen(fname,"w");
   fprintf(fp,"%d %d\n",G.NV,G.NE);
   for(int s=1;s<=G.NV;s++){
      auto it=G.adj[s];
      while(it!=nullptr){
         if((it->t)>s){
            fprintf(fp,"%d %d\n",s,it->t);
         }
         it=(it->nxt);
      }
   }
   fclose(fp);
}

#endif
