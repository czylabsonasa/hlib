// simple tests for vecutils
#include "common.hpp"
#include "vecutils.hpp"


int main(){
	writeVector(tVI{0,1,2,3},"egy",0);
	writeVector(tVI{0,1,2,3},"ketto",1);

	writeVector(tVI{0,1,2,3},fopen("egy0","w"),0);
	writeVector(tVI{0,1,2,3},fopen("ketto0","w"),1);


	writeVector(tVD{.0,.1,.2,.3},"egy1",0);
	writeVector(tVD{.0,.1,.2,.3},"ketto1",1);
	writeVector(tVD{.0,.1,.2,.3},fopen("egy2","w"),0);//remains open 
	writeVector(tVD{.0,.1,.2,.3},fopen("ketto2","w"),1);

	writeColVector(vector<tVI*>{new tVI{1,2,3,4},new tVI{4,3,2,1}},"oszlop");
	writeColVector(tVI{1,2,3,4},"oszlop0");
	

	
   return 0;
}
