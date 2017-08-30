#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

int frek[100000]={0};

struct asd{
	int x0,x1,x2;
	bool operator<(const asd& masik){
		if(x0<masik.x0){return true;}
		if(x0==masik.x0){
			if(x1<masik.x1){return true;}
			if(x1==masik.x1){
				if(x2<masik.x2){return true;}
			}
		}
		return false;
	}
};

int main(){
	int* tmp=new int[5];
	
	int n,nkm;scanf("%d%d",&n,&nkm);
	asd* lofasz=new asd[n+1];
	lofasz[0].x0=-1;
	
	int x0,x1,x2;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&x0,&x1,&x2);
		sort(tmp,tmp+3);
		lofasz[i].x0=x0;
		lofasz[i].x1=x1;
		lofasz[i].x2=x2;
	}
	sort(lofasz+1,lofasz+1+n);

	int f=0;
	int mxf=0;
	for(int i=1;i<=n;i++){
		if(lofasz[i-1]<lofasz[i]){
	 		mxf=max(f,mxf);
	 		++frek[f];
	 		f=1;
		}else{
			f++;
		}
	}
	++frek[f];

	int sum=0;
	for(int i=1;i<=mxf;i++){
	 	sum+=frek[i];
	}

	
	for(int i=1;i<=mxf;i++){
		if(frek[i]>0){
			printf("%d %.15lf\n",i,double(frek[i])/double(sum));
		}
	}
	
	
	
	
	delete[] lofasz;
	delete[] tmp;
	return 0;
}
