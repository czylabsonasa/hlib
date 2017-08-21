#ifndef __VECUTILS_H__
#define __VECUTILS_H__

#include "inc.hpp"

typedef vector<int> tVI;
typedef vector<tII> tVII;
typedef vector<tIII> tVIII;
typedef vector<double> tVD;

namespace vecutils{
	int flprec=12;
	template<typename T> double mean(const vector<T>&, int const=1);//shift by s the start idx
	template<typename T> double sum(const vector<T>&, int const=1);
	void writeVector(const tVI&, const char* const, int const=1,const char* const=" ");
	void writeVector(const tVI&, FILE* =stderr, int const=1,const char* const=" ");

	void writeVector(const tVD&, const char* const, int const=1,const char* const=" ");
	void writeVector(const tVD&, FILE* =stderr, int const=1,const char* const=" ");

	void writeColVector(const tVI&, const char*, int const s=0);
	void writeColVector(vector<tVI*> v, const char*, int const s=0);

	void writeElist(vector<tII>&, const char* const);

	void readElist(const char* const, vector<tII>&);
	void readElist(FILE*, vector<tII>&);

	void readVector(FILE*, vector<double>&,int const=1);
	//
	void write(double*, double* const);
	template<typename T> T Min(T*, T* const);
	template<typename T> T Max(T*, T* const);

}

using vecutils::flprec;


template<typename T> double vecutils::mean(const vector<T>& v,int const s){
   double ret=0.0;
	auto _b=v.begin()+s;
	const auto _e=v.end();
   while(_b<_e){
      ret+=*(_b++);
   }
	return ret/double(v.size()-s);
}


template<typename T> double vecutils::sum(const vector<T>& v,int const s){
   double ret=0.0;
	auto _b=v.begin()+s;
	const auto _e=v.end();
   while(_b<_e){
      ret+=v[_b++];
   }
   return ret;
}

/////////////// ------------------ //////////////

void vecutils::writeVector(const tVI& v, const char* const fname , int const s, const char* const sep){
	FILE* fp=fopen(fname,"w");
	vecutils::writeVector(v,fp,s,sep);
	fclose(fp);
}


void vecutils::writeVector(const tVI& v, FILE* fp, int const s,const char* const sep){
	auto _b=v.begin()+s;
	const auto _e=v.end();
   while(_b<_e){
      fprintf(fp, "%d%s", (*(_b++)), sep);
   }
   fprintf(fp,"\n");
}


void vecutils::writeVector(const tVD& v, const char* const fname , int const s, const char* const sep){
	FILE* fp=fopen(fname,"w");
	vecutils::writeVector(v,fp,s,sep);
	fclose(fp);
}


void vecutils::writeVector(const tVD& v, FILE* fp, int const s, const char* const sep){
	auto _b=v.begin()+s;
	const auto _e=v.end();
   while(_b<_e){
      fprintf(fp, "%.*lf%s",flprec,(*(_b++)),sep);
   }
   fprintf(fp,"\n");
}



void vecutils::writeColVector(const tVI& v, const char*fn, const int s){
	FILE*fp=fopen(fn,"w");
	int const N=v.size();
   for(int i=s;i<N;i++){
		fprintf(fp,"%d %d\n", i, v[i]);
   }
	fclose(fp);
}


void vecutils::writeColVector(vector<tVI*> v, const char*fn, int const s){
	FILE*fp=fopen(fn,"w");
	int const V=v.size();
	int const N=(*v[0]).size();
   for(int i=s;i<N;i++){
		fprintf(fp,"%d", i);
		for(int j=0;j<V;j++){
			fprintf(fp," %d", (*v[j])[i]);
		}
		fprintf(fp,"\n");
   }
	fclose(fp);
}


void vecutils::writeElist(vector<tII>& elek,const char* const fname){
   FILE*fp=fopen(fname,"w");
   for(auto it=elek.begin();it!=elek.end();it++){
      fprintf(fp,"%d %d\n",it->x,it->y);
   }
   fclose(fp);
}


void vecutils::readElist(const char* const fname, vector<tII>& elek){
   FILE*fp=fopen(fname,"r");
	if(fp==nullptr){
		fprintf(stderr,"file error\n");
		exit(1);
	}
	readElist(fp, elek);
}


void vecutils::readElist(FILE*fp, vector<tII>& elek){
   int V,E;fscanf(fp,"%d%d",&V,&E);
   elek.resize(E+1);
   elek[0].x=V;elek[0].y=E;
   for(int i=1;i<=E;i++){
      int x,y;fscanf(fp,"%d%d",&x,&y);
      elek[i].x=x;elek[i].y=y;
   }
}


void vecutils::readVector(FILE*fp, vector<double>& v,int const s){//for multiple reading
   int N;fscanf(fp,"%d",&N);
   v.resize(N+s);
	if(s){v[0]=N;}
   for(int i=s;i<N+s;i++){
      fscanf(fp,"%lf",&v[i]);
   }
}

//

void vecutils::write(double* _b, double* const _e){
   while(_b<_e){
		printf("%.*lf ", flprec, *(_b++));
   }
   printf("\n");
}


template<typename T> T vecutils::Min(T* beg, T* const end){
   T ans=*beg;
   while(++beg<end){
      ans=min(ans,*beg);
   }
   return ans;
}


template<typename T> T vecutils::Max(T* beg, T* const end){
   T ans=*beg;
   while(++beg<end){
      ans=max(ans,*beg);
   }
   return ans;
}



#endif

