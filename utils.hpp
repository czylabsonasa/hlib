#ifndef __UTILS_H__
#define __UTILS_H__

#include "inc.hpp"
#include "mrand.hpp"


#define _ONOFF(x) 
#define _LOG(...) __VA_ARGS__
//#define _LOG(x) 
#define _ERR(...) fprintf(stderr,"   ");fprintf(stderr,__VA_ARGS__);fflush(stderr)

///////////////////////////////////////
///////////////////////////////////////


#define _CHECK(var,fs) if(!strcmp(t,#var)){sscanf(ass,#var#fs,&var);break;}
char* paramshelper(char* x){
   static char tmp[256];
   strcpy(tmp,x);
   int i=0;
   while(tmp[i]){
      if(tmp[i]=='='){break;}
//      tmp[i]=toupper(tmp[i]); //
      i++;
   }
   if(!tmp[i]){return nullptr;}
   tmp[i]=0;
   return tmp;
}

///////////////////////////////////////
///////////////////////////////////////

using namespace chrono;
time_point<steady_clock> start;
double tik(int f=0){
   if(0==f)
   {
      start=steady_clock::now();
      return (-1.0);
   }
   else
   {
      duration<double> diff=steady_clock::now()-start;
      return diff.count();
   }
}
double tak(){
   return tik(1);
}


///////////////////////////////////////
///////////////////////////////////////

template<typename T> T sum(T* _b,T* _e){
   T ret=0;
   while(_b<_e){ret+=(*_b);_b++;}
   return ret;
}

template<typename T,typename S> void mul(T* _b,S* _e,S alfa){
   while(_b<_e){(*_b)*=alfa;_b++;}
}

template<typename T,typename S> void div(T* _b,S* _e,S alfa){
   while(_b<_e){(*_b)/=alfa;_b++;}
}

template<typename T> double mean(const vector<T>& v,int const s=1){
   double ret=0.0;
	for(auto it=v.begin()+s;it<v.end();it++){
      ret+=*it;
   }
return ret/double(v.size()-s);
}

template<typename R=double,typename T> R sum(const vector<T>& x,int _b,int const _e){
   R ret=0.0;
   while(_b<_e){
      ret+=x[_b++];
   }
   return ret;
}




// int vector output
void write(int* _b, int* const _e){
   while(_b<_e){
      printf("%d ",*(_b++));
   }
   printf("\n");
}

void write(const tVI& x, const int _s=1){//s:shift the begin
	auto _b=x.begin()+_s;
	const auto _e=x.end();
   while(_b<_e){
      printf("%d ",*(_b++));
   }
   printf("\n");
}




// 
void write(const tVD& x,int const _s=1,int const prec=3){
	auto _b=x.begin()+_s;
	const auto _e=x.end();
   while(_b<_e){
      printf("%.*lf ",prec,(*_b++));
   }
   printf("\n");
}

void write(double* _b, double* const _e,int const prec=3){
   while(_b<_e){
		printf("%.*lf ", prec, *(_b++));
   }
   printf("\n");
}




void write(vector<tII>& elek,const char* const fname){
   FILE*fp=fopen(fname,"w");
   for(auto it=elek.begin();it!=elek.end();it++){
      fprintf(fp,"%d %d\n",it->x,it->y);
   }
   fclose(fp);
}

void readelist(const char* const fname, vector<tII>& elek){
   FILE*fp=fopen(fname,"r");
   int NE,NV;fscanf(fp,"%d%d",&NV,&NE);
   elek.resize(NE+1);
   elek[0].x=NV;elek[0].y=NE;
   for(int i=1;i<=NE;i++){
      int x,y;fscanf(fp,"%d%d",&x,&y);
      elek[i].x=x;elek[i].y=y;
   }
   fclose(fp);
}

void readelist(FILE*fp, vector<tII>& elek){//for multiple reading
   int V,E;fscanf(fp,"%d%d",&V,&E);
   elek.resize(E+1);
   elek[0].x=V;elek[0].y=E;
   for(int i=1;i<=E;i++){
      int x,y;fscanf(fp,"%d%d",&x,&y);
      elek[i].x=x;elek[i].y=y;
   }
}

void readVector(FILE*fp, vector<double>& x,int const s=1){//for multiple reading
   int N;fscanf(fp,"%d",&N);
   x.resize(N+s);
	if(s){x[0]=N;}
   for(int i=s;i<N+s;i++){
      fscanf(fp,"%lf",&x[i]);
   }
}


int rangemin(pI beg, pI end){
   int ans=*beg;
   while(++beg<end){
      ans=min(ans,*beg);
   }
   return ans;
}



#endif
