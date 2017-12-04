#ifndef __BFS_H__
#define __BFS_H__
#include "common.hpp"

//declare

//the Bfs struct
struct tBfs{
	int V;
   int INF;//beware of overflow :-)
   int head, tail;
	graph* G;
   tVI dist,que,from; //dist,queue,from
	tModes mode;
	void init(graph*);//resizing vectors
	void set(tModes=SIMPLE);
	//all bfs version returns the farthest node 
	void clear();
	void insert(int);
	int operator()();
};

// define

// general init, graph, V, resize containers, init mode with default
void tBfs::init(graph* _G){
	G=_G;
	V=G->V;
	INF=V+11;
	dist.resize(V+1);
	que.resize(V+1);
	from.resize(V+1);
	set();
}


void tBfs::set(tModes _mode){
	mode=_mode;
}


// clear, after init(graph*)
void tBfs::clear(){
	if(mode==PATH){
		for(int i=0;i<=V;i++){
			dist[i]=INF;
			from[i]=0;
		}
	}else{
		for(int i=0;i<=V;i++){
			dist[i]=INF;
		}
	}
	head=0; tail=0;
}


// insert source int the queue, after clear
void tBfs::insert(int s){
	que[tail++]=s;
	dist[s]=0;
}

// run bfs, from the inserted nodes, return the farthest node
int tBfs::operator()(){
	if(mode==PATH){//
		while(head!=tail){
			int a=que[head++];
			int da=dist[a]+1;
			auto it=(G->adj[a]);
			while(it!=nullptr){
				int b=it->t;
				if(da<dist[b]){
					dist[b]=da;
					que[tail++]=b;
					from[b]=a;
				}
				it=(it->next);
			}
		}//queue
	}else{
		while(head!=tail){
			int a=que[head++];
			int da=dist[a]+1;
			auto it=(G->adj[a]);
			while(it!=nullptr){
				int b=it->t;
				if(da<dist[b]){
					dist[b]=da;
					que[tail++]=b;
				}
				it=(it->next);
			}
		}//queue
	}

	return que[tail-1];
}


#endif
