// graph.hpp testing app
#include "inc.hpp"
#include "utils.hpp"
#include "graph.hpp"

int main(){
   vector<tII> elist;
   graph G;
   destat ds;
	FILE*ifp=fopen("input","r");

	int esetek;
	fscanf(ifp,"%d",&esetek);
	for(int es=0;es<esetek;es++){
		readElist(ifp, elist); //read from file
		G.init(elist); //setting up the graph from the edge-list

		ds.comp(G.deg);
		
		write(ds,"_deg");
		writeVector(ds.freq(G.deg),"_degfrek",0);
		
	}

   return 0;
}
