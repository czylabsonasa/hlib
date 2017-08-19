#ifndef __GRAPH_H__
#define __GRAPH_H__
#include "common.hpp"
#include "tartaly.hpp"

// -- declarations ---

//RDC: from adj[s] only some of the neighbours are taken iRDC:only smaller idx, dRDC only neighbours with a specific deg
struct graph{
   struct tINFO{int t; tINFO* next;};
   int V,E,iE;
   vector<tINFO*> adj;
   vector<tINFO> lista;
   tVI deg;
	tVI deg2;

   graph(int=0, int=0);
   void init(int, int, tModes=FULL);
	void init(const graph&, tModes);
   void init(int, const aTartaly&);
	void init(const vector<tII>&);
	void insertU(int, int);
	void insertD(int, int);

};

// -- declarations external methods --
void write(const graph&, const char* const);
graph genKlikk(int);
graph genStar(int);




///////////////////////////////////////////////////////////////////


// internal method defs
graph::graph(int _V,int _E):V(_V),E(_E){}
  
void graph::init(int _V, int _E,tModes mode){
	V=_V;
   E=_E;
   adj.resize(V+1);
   deg.resize(V+1);
   for(int s=1;s<=V;s++){
      adj[s]=nullptr;
      deg[s]=0;
   }
	int tE=2*E+1;
	if(mode!=FULL){tE=E+1;}
   lista.resize(tE);
   iE=0;
}
   
void graph::init(const graph& G, tModes mode){
   if(iRDC==mode){
      init(G.V,G.E,mode);
      for(int s=1;s<=G.V;s++){
			auto it=G.adj[s];
         while(it!=nullptr){
            if(s>it->t){
               insertD(s,it->t);
            }
            it=(it->next);
         }
      }
		return;
	}

   if(dRDC==mode){
      init(G.V,G.E,mode);
      for(int s=1;s<=G.V;s++){
			int ds=G.deg[s];
			auto it=G.adj[s];
         while(it!=nullptr){
            if(ds>G.deg[it->t]||((ds==G.deg[it->t])&&(s>it->t))){
               insertD(s,it->t);
            }
            it=(it->next);
         }
      }
		return;
	}

   if(d2RDC==mode){
      init(G.V,G.E,mode);
		deg2.resize(G.V+1);
		//set deg2
		for(int s=1;s<=G.V;s++){
			int& d2s(deg2[s]);d2s=G.deg[s];
			auto it=G.adj[s];
         while(it!=nullptr){
				d2s+=deg[it->t];
            it=(it->next);
         }
		}

		//build 
      for(int s=1;s<=G.V;s++){
			//			int ds=G.deg[s];
			int d2s=deg2[s];

			auto it=G.adj[s];
         while(it!=nullptr){
            if(d2s>deg2[it->t]||((d2s==deg2[it->t])&&(s>it->t))){
               insertD(s,it->t);
            }
            it=(it->next);
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
            it=(it->next);
         }
      }
		return;
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
         it=(it->next);
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

graph genStar(int V){
	graph G; G.init(V,(V-1));
	for(int i=2;i<=V;i++){
		G.insertU(1,i);
	}
	return G;
}


#endif
