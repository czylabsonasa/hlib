#ifndef __DIAM_H__
#define __DIAM_H__
#include "inc.hpp"
#include "mrand.hpp"

//declare

//the diam struct
struct diam{
	int V;
	int L,U;
   int INF;//beware of overflow :-)
   int numofbfs;
	graph* G;
   tVI dist[2],q[2],from[2]; //dist,queue,from
	void init(graph*);//resizing vectors
	void initLU();//set init values 
	//all bfs version returns the farthest node 
	int bfs(int, tVI&, tVI&, tVI&);//one source
	int bfs(int, tVI&, tVI&);//from mentes

	int bfs(tVI&, tVI&, tVI&, tVI&);//more than one source
	int bfs(tVI&, tVI&, tVI&);//more than one source w/o from

   int bruteforce();//brute force,for connected graphs
   int bruteforce2();//brute force,for connected graphs, adjust LU

   int sweep2(int);//sweep2 egy csucsbol
	int ifub(int);
	int rndselect();
	int minselect();
	int maxselect();

};


// define
// general init
void diam::init(graph* _G){
	G=_G;
	V=G->V;
	INF=V+11;
	dist[0].resize(V+1);
	dist[1].resize(V+1);
	q[0].resize(V+1);
	q[1].resize(V+1);
	from[0].resize(V+1);
	from[1].resize(V+1);
}


//init L and U
void diam::initLU(){
	L=1;U=V-1; //assuming connected non-degenerate graph
}


// sweep2
int diam::sweep2(int a){
	bfs(a,q[0],dist[0],from[0]);
	int win=0;//which one is a winner
	int mx=dist[0][q[0][V-1]];
	L=max(L,mx);U=min(U,2*mx);

	bfs(q[0][V-1],q[1],dist[1],from[1]);
	int mx1=dist[1][q[1][V-1]];
	L=max(L,mx1);U=min(U,2*mx1);

	if(mx1>mx){
		mx=mx1;win=1;
	}
	
	
	int step=mx/2;a=q[win][V-1];
	const tVI& f(from[win]);
	while(step>0){a=f[a];--step;}

	return a;
}


// // ifub
// int diam::ifub(int s){
// 	tVI& q0(q[0]);tVI& d0(dist[0]);
// 	tVI& q1(q[1]);tVI& d1(dist[1]);

// 	//	printf("prev   L,U:%d,%d\n",L,U);
// 	s=bfs(s,q0,d0);
// 	U=min(U,2*d0[s]);
// 	L=max(L,d0[s]);
// 	//printf("szar?  :%d %d\n",q0[V-1],d0[q0[V-1]]);

// 	//printf("prev   L,U:%d,%d\n",L,U);

// 	int tL=1;
// 	int tU=V-1;

// 	int i=V-1;
// 	int pd=INF;
// 	while(i>0 && U>L){
// 		int d=d0[q0[i]];
// 		if(d<pd){//level change
// 			tU=min(tU,max(tL,2*d));
// 			//		printf("tU:%d\n",tU)			;
// 			pd=d;
// 		}

// 		int td=d1[bfs(q0[i],q1,d1)];
// 		tU=min(tU,2*td);
// 		tL=max(tL,td);
// 		//		printf("tL,tU:%d,%d\n",tL,tU)			;

// 		U=min(U,tU);
// 		L=max(L,tL);
		
		
// 		i--;
// 	}
// 	printf("%d\n",i);
// 	return L;
// }//ifub


// ifub
int diam::ifub(int s){
	tVI& q0(q[0]);tVI& d0(dist[0]);
	tVI& q1(q[1]);tVI& d1(dist[1]);

	//	printf("prev   L,U:%d,%d\n",L,U);
	s=bfs(s,q0,d0);
	U=min(U,2*d0[s]);
	L=max(L,d0[s]);
	//printf("szar?  :%d %d\n",q0[V-1],d0[q0[V-1]]);

	//printf("prev   L,U:%d,%d\n",L,U);

	int i=V-1;
	int pd=INF;
	while(i>0 && U>L){
		int d=d0[q0[i]];
		if(d<pd){//level change
			if(L>=2*d){break;}
			pd=d;
		}

		int td=d1[bfs(q0[i],q1,d1)];
		if(2*td<U){printf("*\n");}
		U=min(U,2*td);
		L=max(L,td);
		//		printf("tL,tU:%d,%d\n",tL,tU)			;

	
		i--;
	}
	printf("%d\n",i);
	return L;
}//ifub



// single source bfs, return the farthest node
int diam::bfs(int a,tVI& tq,tVI& td,tVI& tfr){
	++numofbfs;
	fill(td.begin(), td.end(), INF);

	int head=0; int tail=1;
	tq[0]=a;td[a]=0;tfr[a]=0;
	while(head!=tail){
		a=tq[head++];
		int da=td[a]+1;
		//		printf("%d %d\n",a,da);

		auto it=(G->adj[a]);
		while(it!=nullptr){
			int b=it->t;
			if(da<td[b]){
				td[b]=da;
				tq[tail++]=b;
				tfr[b]=a;
			}
			it=(it->nxt);
		}
	}//queue
	return tq[tail-1];
}


// single source bfs, w/o from, return the index of the farthest node
int diam::bfs(int a, tVI& tq, tVI& td){
	++numofbfs;
	fill(td.begin(), td.end(), INF);

	int head=0; int tail=1;
	tq[0]=a;td[a]=0;
	while(head!=tail){
		a=tq[head++];
		int da=td[a]+1;
		//		printf("%d %d\n",a,da);

		auto it=(G->adj[a]);
		while(it!=nullptr){
			int b=it->t;
			if(da<td[b]){
				td[b]=da;
				tq[tail++]=b;
			}
			it=(it->nxt);
		}
	}//queue
	return tq[tail-1];
}


// multiple source bfs
int diam::bfs(tVI& tmp,tVI& tq,tVI& td,tVI& tfr){
	++numofbfs;
	fill(td.begin(), td.end(), INF);
	int head=0,tail=0;
	for(auto it=tmp.begin();it!=tmp.end();it++){
		tq[tail++]=*it;
		td[*it]=0;
		tfr[*it]=0;
	}
	while(head!=tail){
		int a=tq[head++];
		int da=td[a]+1;
		auto it=G->adj[a];
		while(it!=nullptr){
			int b=it->t;
			if(da<td[b]){
				td[b]=da;
				tq[tail++]=b;
				tfr[b]=a;
			}
			it=it->nxt;
		}
	}//queue
	return tq[tail-1];
}


// multiple source bfs w/o from
int diam::bfs(tVI& tmp,tVI& tq,tVI& td){
	++numofbfs;
	fill(td.begin(), td.end(), INF);
	int head=0,tail=0;
	for(auto it=tmp.begin();it!=tmp.end();it++){
		tq[tail++]=*it;
		td[*it]=0;
	}
	while(head!=tail){
		int a=tq[head++];
		int da=td[a]+1;
		auto it=G->adj[a];
		while(it!=nullptr){
			int b=it->t;
			if(da<td[b]){
				td[b]=da;
				tq[tail++]=b;
			}
			it=it->nxt;
		}
	}//queue
	return tq[tail-1];}


// brute-force diam
int diam::bruteforce(){//brute force,for connected graphs
	int mx=0;
	tVI& q0(q[0]);tVI& d0(dist[0]);tVI& f0(from[0]);
	for(int a=1;a<=V;a++){
		bfs(a,q0,d0,f0);
		mx=max(mx,d0[q0[V-1]]);
	}
	return mx;
}//bfdiam


// brute-force diam, variant that uses and updates L,U
// no gain
int diam::bruteforce2(){//brute force,for connected graphs
	tVI& q0(q[0]);tVI& d0(dist[0]);tVI& f0(from[0]);
	for(int a=1;a<=V&&U>L;a++){
		bfs(a,q0,d0,f0);
		L=max(L,d0[q0[V-1]]);
		U=min(U,2*d0[q0[V-1]]);
	}
	return L;
}//bfdiam


// mindeg
int diam::minselect(){
	auto deg(G->deg);
	int val=deg[1],loc=1;
	for(int i=2;i<=V;i++){
		if(deg[i]<val){
			val=deg[i];loc=i;
		}
	}
	return loc;
}


// maxdeg
int diam::maxselect(){
	auto deg(G->deg);
	int val=deg[1],loc=1;
	for(int i=2;i<=V;i++){
		if(deg[i]>val){
			val=deg[i];loc=i;
		}
	}
	return loc;
}

   
// select a random number in 1..V   
int diam::rndselect(){
//_LOG(_ERR("( unif.random node selection ) "));
   return mrand::IRND(1,V);
}



#endif
