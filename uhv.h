#ifndef __UHV_H__
#define __UHV_H__
struct UHV{
   int N;
	vector<int> prnt;//parent, 0 if none
	UHV(int _N):N(_N),prnt(N+1){}

	void init(){
      prnt[0]=-1;//unused
      for(int i=1;i<=N;i++){
         prnt[i]=0;
      }
	}

	int find(int ez){ // tomoriteses (PathCompressing)
		int mo=ez,t;
		while((t=prnt[mo])>0){mo=t;}
		while((t=prnt[ez])>0){
			prnt[ez]=mo;
			ez=t;
		}
		return mo;
	}

	inline void unioifneq(int a,int b){
      if((a=find(a))!=(b=find(b))){
         prnt[a]=b;
      }
	}
	inline void unio(int a,int b){//unconditional
      prnt[a]=b;
	}

};

//extract component sizes
void node2size(UHV& uhv,tVI& n2s){
   n2s.resize(uhv.N+1);
   for(int i=0;i<=uhv.N;i++){
      n2s[i]=0;
   }
   for(int i=1;i<=uhv.N;i++){
      ++n2s[uhv.find(i)];
   }
}

void simp(tVI& v){//there is a plenty zeroes
   int tar=1;int src=1;
   int const N=v.size()-1;
   while(src<=N){
      int vs=v[src++];
      if(vs!=0){
         v[tar++]=vs;
      }
   }
   v.resize(tar);
}

#endif
