//diam All in One
//does not handle properly disconnected graphs without additional work
// partial fix: change 'V' to 'tail' returned by bfs
// flickr at conect,snap

#ifndef __DIAMAIO_H__
#define __DIAMAIO_H__
#include "common.hpp"

//declare

//the diam struct
struct tDiamAio{
	int V;
	int L,U;
   int INF;//beware of overflow :-)
   int numofbfs;
	int tol;
	graph* G;
   tVI dist[2],q[2],from[2]; //dist,queue,from
	tVI v2; //helper vector for ifubv2
	void init(graph*);//resizing vectors
	void initLU(int=0);//set init values, and tolarance for U-L
	//all bfs version returns the farthest node 
	int bfs(int, tVI&, tVI&, tVI&);//one source
	int bfs(int, tVI&, tVI&);//from mentes

	int bfs(tVI&, tVI&, tVI&, tVI&);//more than one source
	int bfs(tVI&, tVI&, tVI&);//more than one source w/o from

   int bruteForce();//brute force,for connected graphs
   int bruteForce2();//brute force,for connected graphs, adjust LU

   int sweep2(int);//sweep2 egy csucsbol
	int ifub(int);
	int ifubV2(int);// additional update of U
	int treeDiam(tVI&,tVI&,int);
	int rndSelect();
	int minSelect();
	int maxSelect();

};


// define

// general init
void tDiamAio::init(graph* _G){
	G=_G;
	V=G->V;
	INF=V+11;
	dist[0].resize(V+1);
	dist[1].resize(V+1);
	q[0].resize(V+1);
	q[1].resize(V+1);
	from[0].resize(V+1);
	from[1].resize(V+1);
	v2.resize(V+1);
}


//init L and U
void tDiamAio::initLU(int _tol){
	L=1;U=V-1; //assuming connected non-degenerate graph
	tol=_tol;
}


// sweep2
int tDiamAio::sweep2(int a){
	int tail=bfs(a,q[0],dist[0],from[0]);//tail: CC size
	int win=0;//which one is a winner
	int mx=dist[0][q[0][tail-1]];
	L=max(L,mx);U=min(U,2*mx);
	U=min(U,treeDiam(q[0],from[0],tail));
	
	bfs(q[0][tail-1],q[1],dist[1],from[1]);
	int mx1=dist[1][q[1][tail-1]];
	L=max(L,mx1);U=min(U,2*mx1);
	U=min(U,treeDiam(q[1],from[1],tail));

	
	if(mx1>mx){
		mx=mx1;win=1;
	}
	
	
	int step=mx/2;a=q[win][tail-1];
	const tVI& f(from[win]);
	while(step>0){a=f[a];--step;}

	return a;
}


// ifub
int tDiamAio::ifub(int s){
	tVI& q0(q[0]);tVI& d0(dist[0]);
	tVI& q1(q[1]);tVI& d1(dist[1]);

	int tail=bfs(s,q0,d0);
	s=d0[q0[tail-1]];
	U=min(U,2*s);
	L=max(L,s);

	int ph=INF;
	int i=tail-1;
	while(i>0 && U>L+tol){
		int h=d0[q0[i]];
		if(h<ph){//level change
			if(L>=2*h){U=L;break;}
			ph=h;
			U=2*h;//indirekt
		}

		int th=d1[q1[bfs(q0[i],q1,d1)-1]];
		//		if(2*th<U){printf("*\n");} 
		U=min(U,2*th);
		L=max(L,th);

		i--;
	}
	_ERR("tail,end: %d,%d\n",tail,i);
	return L;
}//ifub


//helper for ifubv2
int tDiamAio::treeDiam(tVI& tq, tVI& tf,int tail){
	tVI& d(v2);
	fill(d.begin(),d.end(),0);
	
	int tU=0;
	--tail;
	while(tail>0){
		int a=tq[tail--];
		int& dfa(d[tf[a]]);
		int td=d[a]+1;
		tU=max(tU,td+dfa);
		dfa=max(dfa,td);
	}
	return tU;
}


// ifubv2, does not matter (slower)
int tDiamAio::ifubV2(int s){
	tVI& q0(q[0]);tVI& d0(dist[0]);tVI& f0(from[0]);
	tVI& q1(q[1]);tVI& d1(dist[1]);tVI& f1(from[0]);

	int tail=bfs(s,q0,d0,f0);
	s=d0[q0[tail-1]];
	U=min(U,2*s);
	U=min(U,treeDiam(q0,f0,tail));//new
	L=max(L,s);

	int i=tail-1;
	int ph=INF;
	while(i>0 && U>L+tol){
		int h=d0[q0[i]];
		if(h<ph){//level change
			if(L>=2*h){break;}
			ph=h;
			U=2*h;//indirekt
		}

		int th=d1[q1[bfs(q0[i],q1,d1,f1)-1]];
		//		if(2*th<U){printf("*\n");} 
		U=min(U,2*th);
		U=min(U,treeDiam(q1,f1,tail));//new
		L=max(L,th);

		i--;
	}
	_ERR("tail,end: %d,%d\n",tail,i);
	
	return L;
}//ifubv2


// single source bfs (from), returns the tail, ie. the size of the actual component
int tDiamAio::bfs(int a,tVI& tq,tVI& td,tVI& tfr){
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
			it=(it->next);
		}
	}//queue
	//	printf("tail: %d\n",tail);
	return tail;
}


// single source bfs, w/o from, return the tail, ie. the size of the actual component
int tDiamAio::bfs(int a, tVI& tq, tVI& td){
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
			it=(it->next);
		}
	}//queue
	//	printf("tail: %d\n",tail);

	return tail;
}


// multiple source bfs
int tDiamAio::bfs(tVI& tmp,tVI& tq,tVI& td,tVI& tfr){
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
			it=it->next;
		}
	}//queue
	return tail;
}


// multiple source bfs w/o from
int tDiamAio::bfs(tVI& tmp,tVI& tq,tVI& td){
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
			it=it->next;
		}
	}//queue
	return tail;
}


// brute-force tDiamAio
int tDiamAio::bruteForce(){//brute force,for connected graphs
	int mx=0;
	tVI& q0(q[0]);tVI& d0(dist[0]);tVI& f0(from[0]);
	for(int a=1;a<=V;a++){
		bfs(a,q0,d0,f0);
		mx=max(mx,d0[q0[V-1]]);
	}
	return mx;
}//bftDiamAio


// brute-force tDiamAio, variant that uses and updates L,U
// no gain
int tDiamAio::bruteForce2(){//brute force,for connected graphs
	tVI& q0(q[0]);tVI& d0(dist[0]);tVI& f0(from[0]);
	for(int a=1;a<=V&&U>L+tol;a++){
		bfs(a,q0,d0,f0);
		L=max(L,d0[q0[V-1]]);
		U=min(U,2*d0[q0[V-1]]);
		U=min(U,treeDiam(q0,f0,V));
	}
	return L;
}//bftDiamAio


// mindeg
int tDiamAio::minSelect(){
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
int tDiamAio::maxSelect(){
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
int tDiamAio::rndSelect(){
//_LOG(_ERR("( unif.random node selection ) "));
   return mrand::IRND(1,V);
}


#endif
