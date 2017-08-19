// a fixed size (V+1+2*(dmax+1)) collection of doubly linked lists
#ifndef __KCORE_H__
#define __KCORE_H__
#include "common.hpp"

//declare

//the KCore struct
struct KCore{
	int V;
   int INF;//beware of overflow :-)
   int head, tail;
	graph* G;
   tVI que; //queue
	void init(graph*);//resizing vectors
	int operator()();
};

// define

// general init, graph, V, resize containers, init mode with default
void KCore::init(graph* _G){
	G=_G;
	V=G->V;
	INF=V+11;
	que.resize(V+1);
}



// 
int KCore::operator()(){
	while(head!=tail){
		int a=que[head++];
		auto it=(G->adj[a]);
		while(it!=nullptr){
			int b=it->t;
			if(da<dist[b]){
				que[tail++]=b;
			}
			it=(it->next);
		}
	}//queue

	return que[tail-1];
}

#endif
