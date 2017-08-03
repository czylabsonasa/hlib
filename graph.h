#ifndef __GRAPH_H__
#define __GRAPH_H__
#include "tartaly.h"
#include "inc.h"

// -- declarations ---
enum tMode{REDUCED, FULL};//REDUCED: from adj[s] only some of the neighbours are taken
struct graph{
   struct tINFO{int t; tINFO* nxt;};
   int V,E,iE;
   vector<tINFO*> adj;
   vector<tINFO> lista;
   tVI deg;

   graph(int=0, int=0);
   void init(int, int, tMode=FULL);
	void init(const graph&, tMode);
   void init(int, const aTartaly&);
	void init(const vector<tII>&);
	void insertU(int, int);
	void insertD(int, int);

};

// -- declarations external methods --
void write(const graph&, const char* const);
graph genKlikk(int);


///////////////////////////////////////////////////////////////////


// internal method defs
graph::graph(int _V,int _E):V(_V),E(_E){}
  
void graph::init(int _V, int _E,tMode mode){
	V=_V;
   E=_E;
   adj.resize(V+1);
   deg.resize(V+1);
   for(int s=1;s<=V;s++){
      adj[s]=nullptr;
      deg[s]=0;
   }
	int tE=2*E+1;
	if(mode==REDUCED){tE=E+1;}
   lista.resize(tE);
   iE=0;
}
   
void graph::init(const graph& G, tMode mode){
   if(REDUCED==mode){
      init(G.V,G.E,mode);
      for(int s=1;s<=G.V;s++){
			auto it=G.adj[s];
         while(it!=nullptr){
            if((it->t)>s){
               insertD(s,it->t);
            }
            it=(it->nxt);
         }
      }
		return;
	}
   if(FULL==mode){
      init(G.V,G.E);
      for(int s=1;s<=G.V;s++){
         auto it=G.adj[s];
         while(it!=nullptr){
            insertD(s,it->t);
            it=(it->nxt);
         }
      }
   }
}

void graph::init(int _V,const aTartaly& tar){
	init(_V,tar.meret);
	const auto _B(tar.tar.begin());
	const auto _E(tar.tar.end());
	for(auto it=_B;it!=_E;it++){
		insertU(it->x,it->y);
	}
}

void graph::init(const vector<tII>& elist){
	init(elist[0].x, elist[0].y);
	for(int i=1;i<=E;i++){
		insertU(elist[i].x, elist[i].y);
	}
}

void graph::insertU(int a,int b){//undirected
	auto tmp=adj[a];
	adj[a]=&lista[++iE];
	lista[iE]=tINFO{b,tmp};
	++deg[a];

	tmp=adj[b];
	adj[b]=&lista[++iE];
	lista[iE]=tINFO{a,tmp};
	++deg[b];
}

void graph::insertD(int a,int b){//directed
	auto tmp=adj[a];
	adj[a]=&lista[++iE];
	lista[iE]=tINFO{b,tmp};
	++deg[a];
}
   




// --- definitions of externals --
void write(const graph& G,const char* const fname){
   FILE*fp=fopen(fname,"w");
   fprintf(fp,"%d %d\n",G.V,G.E);
   for(int s=1;s<=G.V;s++){
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


graph genKlikk(int V){
	graph G; G.init(V,(V*(V-1))/2);
	for(int i=1;i<V;i++){
		for(int j=i+1;j<=V;j++){
			G.insertU(i,j);
		}
	}
	return G;
}

#endif
