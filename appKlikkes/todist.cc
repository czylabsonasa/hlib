#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

int frek[100000]={0};

int main(){
	int* tmp=new int[5];
	
	int n,nkm;scanf("%d%d",&n,&nkm);
	for(int i=0;i<n;i++){
		for(int j=0;j<nkm;j++){
			scanf("%d",&tmp[j]);
		}
		sort(tmp,tmp+nkm);
		int p=-1;
		for(int j=0;j<nkm;j++){
			assert(tmp[j]>p);
			printf("%d ",tmp[j]);
			p=tmp[j];
		}
		printf("\n");
		
	}

	// char*prev=new char[128];
	// char*akt=new char[128];
	// prev[0]=0;
	// int f=0;
	// int mxf=0;
	// while(1==scanf("%s",akt)){
	// 	if(!strcmp(akt,prev)){
	// 		f++;
	// 	}else{
	// 		mxf=max(f,mxf);
	// 		++frek[f];
	// 		swap(akt,prev);
	// 		f=1;
	// 	}
	// }
	// ++frek[f];

	// int sum=0;
	// for(int i=1;i<=mxf;i++){
	// 	sum+=frek[i];
	// }

	
	// for(int i=1;i<=mxf;i++){
	// 	if(frek[i]>0){
	// 		printf("%d %.15lf\n",i,double(frek[i])/double(sum));
	// 	}
	// }
	
	
	
	

	delete[] tmp;
	return 0;
}
