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
		readelist(ifp, elist); //read from file
		G.init(elist); //setting up the graph from the edge-list
		
		ds.comp(G.deg);
		printf("raw deg: ");
		write(G.deg);
		
		write(ds,"G.deg");
		write(ds.freq(G.deg),0);
		
	}
		

   return 0;
}
