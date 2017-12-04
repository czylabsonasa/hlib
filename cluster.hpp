#ifndef __CLUSTER_H__
#define __CLUSTER_H__
#include "common.hpp"
#include "graph.hpp"

struct cluster{
   int V;
   vector<bool> volt; //flag vector for the counting
   tVI numtri; //numtri[v]: num of triangles centered at v
	tVI prenum;//vector for dfs states
   tVD lcc; //local cc vector
   void init(int);//set the sizes

   void count(const graph&);//compute numtri[idx]: num of triangles centered at idx
	void countR(const graph&);//REDUCED version
	void countR2(const graph&);//REDUCED version

   void coeff(const graph&, const tVI&);//lcc: local clustering coeff
   void coeffR(const graph&, const tVI&);//lcc: local clustering coeff,REDUCED version
   void coeffR2(const graph&, const tVI&);//lcc: local clustering coeff,REDUCED version

	
	double complcc(const int, const int);
};


void cluster::init(int _V){
	V=_V;
	volt.resize(V+1);
	numtri.resize(V+1);
	lcc.resize(V+1);
	prenum.resize(V+1);
	for(int i=1;i<=V;i++){
		volt[i]=false;
		numtri[i]=0;
		prenum[i]=0;
	}
}

	
//naive: forall vertex: take the neighbours, put them in a vector, and iterate through the vector
//to find the closing edges O(V*maxdeg^2)
void cluster::count(const graph& G){//numtri[idx]: num of triangles centered at idx
	init(G.V);
	for(int s=1;s<=G.V;s++){
		if(G.deg[s]<2){
			continue;
		}
		auto it=G.adj[s];
		while(it!=nullptr){
			volt[it->t]=true;
			it=(it->next);
		}
		int& nt(numtri[s]);
		it=G.adj[s];
		while(it!=nullptr){
			auto ti=G.adj[it->t];
			while(ti!=nullptr){
				if(volt[ti->t]){++nt;}
				ti=(ti->next);
			}
			volt[it->t]=false;
			it=(it->next);
		}
	}
}


//same as before with the reduced graph   
void cluster::countR(const graph& rG){//
	init(rG.V);
	const auto& adj(rG.adj);
	
	for(int s=1;s<=V;s++){
		if(rG.deg[s]<2){
			continue;
		}

		auto it=adj[s];
		while(it!=nullptr){
			volt[it->t]=true;
			it=(it->next);
		}

		it=adj[s];
		while(it!=nullptr){
			auto ti=adj[it->t];
			while(ti!=nullptr){
				if(volt[ti->t]){
					++numtri[s];
					++numtri[it->t];
					++numtri[ti->t];
				}
				ti=(ti->next);
			}
			it=(it->next);
		}
		it=adj[s];
		while(it!=nullptr){
			volt[it->t]=false;
			it=(it->next);
		}
	}
}



void cluster::countR2(const graph& G){//numtri[idx]: num of triangles centered at idx
	init(G.V);
	for(int s=1;s<=G.V;s++){
		int const ds(G.deg[s]);
		if(ds<2){
			continue;
		}
		
		auto it=G.adj[s];
		while(it!=nullptr){
			if(ds>G.deg[it->t]){
				volt[it->t]=true;
			}
			it=(it->next);
		}
		int& nt(numtri[s]);
		it=G.adj[s];
		while(it!=nullptr){
			if(ds>G.deg[it->t]){
				auto ti=G.adj[it->t];
				while(ti!=nullptr){
					if(volt[ti->t]){++nt;}
					ti=(ti->next);
				}
				volt[it->t]=false;
			}
			it=(it->next);
		}
	}
}




//a naivecount-nak megfeleloen a local clustering coefficient vectort szamolja
void cluster::coeff(const graph& G,const tVI& deg){//lcc: local clustering coeff
	count(G);
	for(int s=1;s<=V;s++){
		lcc[s]=complcc(deg[s], s);
	}
}

//a naivecountR-nak megfeleloen a local clustering coefficient vectort szamolja
void cluster::coeffR(const graph& rG,const tVI& deg){//lcc: local clustering coeff, reduced graph!!!
	countR(rG);
	for(int s=1;s<=V;s++){
		lcc[s]=complcc(deg[s], s);
	}
}


//a naivecount-nak megfeleloen a local clustering coefficient vectort szamolja,
// de az eredeti G-t használja
void cluster::coeffR2(const graph& G,const tVI& deg){//lcc: local clustering coeff, reduced graph!!!
	countR2(G);
	for(int s=1;s<=V;s++){
		lcc[s]=complcc(deg[s], s);
	}
}


double cluster::complcc(const int ds, const int s){
	double ans=0.0;
	if(numtri[s]>0){
		double den=ds;den*=(den-1.0);
		ans=2.0*double(numtri[s])/den;
	}
	return ans;
}




#endif
