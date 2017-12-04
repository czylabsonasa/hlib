// destat.hpp testing app
// data generated and result computed by octave,
// destat's results compared with them

#include "inc.hpp"
#include "utils.hpp"
#include "graph.hpp"

int main(){
	const double tol=1e-12;
	char name[128];
   vector<double> data;
   destat ds;
	int numofT;
	FILE*fp=nullptr;

	double _min,_max,_R,_mean,_sigma;
	

	fp=fopen("_data/numofTests","r");
	fscanf(fp,"%d",&numofT);
	fclose(fp);
	//	fprintf(stderr,"numoft:%d\n",numofT);
	
	for(int t=1;t<=numofT;t++){

		sprintf(name,"_data/%d.in",t);
		fp=fopen(name,"r");
		readVector(fp,data);
		fclose(fp);
		//	fprintf(stderr,"data[1]:%.15lf\n",data[1]);

		
		ds.comp(data);

		sprintf(name,"_data/%d.out",t);
		fp=fopen(name,"r");
		int tmp;
		fscanf(fp,"%d%lf%lf%lf%lf%lf",&tmp,&_min,&_max,&_R,&_mean,&_sigma);
		fclose(fp);
		
		if(abs(_min-ds._min)>tol){
			fprintf(stderr,"hiba, %d, %s\n",t,"min");
			return 1;
		}
		if(abs(_max-ds._max)>tol){
			fprintf(stderr,"hiba, %d, %s\n",t,"max");
			return 1;
		}
		if(abs(_R-ds._R)>tol){
			fprintf(stderr,"hiba, %d, %s\n",t,"R");
			return 1;
		}
		if(abs(_mean-ds._mean)>tol){
			fprintf(stderr,"hiba, %d, %s\n",t,"mean");
			return 1;
		}
		if(abs(_sigma-ds._sigma)>tol){
			fprintf(stderr,"hiba, %d, %s\n",t,"sigma");
			return 1;
		}
	}

	fprintf(stderr,"OK.\n");
	
   return 0;
}
