#ifndef __DESTAT_H__
#define __DESTAT_H__
#include "inc.h"

// --- declarations --
struct destat{
	tVD _v;
   double _mean, _sigma;
   double _min , _max, _R;
   int _N;
   template<typename T> void comp(vector<T>&);//only fill v
	void realcomp();

	//todo:::
   void prop2frek(vector<int>& prop, vector<int>& frek){
      int const NV=prop.size()-1;//0 nem hasznalt
      sort(prop.begin()+1, prop.end());
      frek.resize(prop[NV]);
   }
};


void write(const destat&, const char*);//only for testing
void write(const destat&, FILE*);

//////////////////////////////////////////////////////////

// --- method defs ---
template<typename T> void destat::comp(vector<T>& v){
   _N=v.size()-1;//0 is unused
	if(_N<1){
		_sigma=_mean=-1;
		return;
	}
	_v.resize(_N+1);
	copy(v.begin(),v.end(),_v.begin());
	realcomp();
}

void destat::realcomp(){
   _min=_max=_v[1]; 
   _mean=0.0;_sigma=0.0;
   for(int i=1;i<=_N;i++){
		double vi=_v[i];
		if(vi>_max){_max=vi;}
		if(vi<_min){_min=vi;}
		_mean+=vi;         
		_sigma+=vi*vi;
	}
	_R=_max-_min;
	_mean=_mean/double(_N);
	_sigma=sqrt(_sigma/double(_N)-_mean*_mean);
}



// -- external fun defs ---
void write(const destat& ds, const char* _name){//only for testing
	const char*const tmp=" ******* ";
	printf("\n%s%s%s\nN=%d min=%.3lf max=%.3lf R=%.3lf\nmean=%.8lf sigma=%.8lf\n\n"
	,tmp,_name,tmp,
	ds._N,ds._min,ds._max,ds._R,ds._mean,ds._sigma);
}

void write(const destat& ds, FILE* fp){
	fprintf(fp,"%d %.8lf %.8lf %.8lf %.8lf\n",
	ds._N,ds._min,ds._max,ds._mean,ds._sigma);
}



#endif

