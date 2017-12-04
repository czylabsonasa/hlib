// dlist  app
#include "inc.hpp"
#include "utils.hpp"
#include "graph.hpp"
#include "kcore.hpp"
#include "klikkes.hpp"

vector<double> sim{
	0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.90
		};

int main(int np,char**p){

	mrand::init(-1);

   klikkesInfo ki;
   aTartaly T(int(0.9*ki.LEPES*ki.NKM));
   klikkes KL(ki,T);
   graph G; G.init(ki.LEPES+1,0.9*ki.LEPES*ki.NKM);

	kCore kcr;
	double* varP=nullptr;
	double* varQ=nullptr;
	double* varR=nullptr;
	
	if(KL.P<0){varP=&KL.P;}
	if(KL.Q<0){varQ=&KL.Q;}
	if(KL.R<0){varR=&KL.R;}
	if(varP==nullptr&&varQ==nullptr&&varR==nullptr){
		fprintf(stderr,"konfig error...exit\n");return 1;
	}


   FILE*fcore=fopen("_kcores","a");

	int ISM=ki.ISM;
	int LEPES=ki.LEPES;
	for(int i=0;i<sim.size();i++){
		if(varP!=nullptr){*varP=sim[i];}
		if(varQ!=nullptr){*varQ=sim[i];}
		if(varR!=nullptr){*varR=sim[i];}

		double mcorr=0.0;
		double mdegmax=0.0;
		double mkcmax=0.0;
		double mmeandeg=0.0;
		for(int ism=0;ism<ISM;ism++){
			KL.clear();
			KL.step1st();
			KL.gen();
			KL.write();      
			G.init(ki.V,T);
			kcr(&G);
			mcorr+=corr(G.deg,kcr.loc);
			mmeandeg+=mean(G.deg,1);
			mdegmax+=(*max_element(G.deg.begin()+1,G.deg.end()));
			mkcmax+=(kcr.dist.size()-1);
		}
		fprintf(fcore,"%d %d %.2lf %.2lf %.2lf %lf %.3lf %.3lf %.3lf\n",
		ki.NKM, LEPES, KL.P, KL.Q, KL.R, 
		mcorr/double(ISM) , mmeandeg/double(ISM), mdegmax/double(ISM) , mkcmax/double(ISM) );
		fflush(fcore);
	}
	fprintf(fcore,"\n");
	fclose(fcore);
	
//	writeColVector(vector<tVI*>{&kcr.loc,&G.deg,&deg2},"_out");
	
   return 0;
}
