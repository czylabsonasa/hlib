// a (very special) collection of linked lists
#ifndef __LLIST_H__
#define __LLIST_H__
#include "common.hpp"

//declare

struct tLlist{
	int H,V;//heads+nodes(vertices)
	vector<tLL> all;
	vector<tLL*> heads;
	vector<tLL*> tails; // the rang is 0..H
	vector<tLL*> vertices;// the is range 1..V (0 is unused)
	void init(int,int);
	void push_back(int,int);//before tail
	void push_front(int,int);//after head, later
	void remove(int,int);//a h csak a meret adjust-hoz kell
};


void tLlist::init(int _H,int _V){
	H=_H;
	V=_V;
	all.resize(2*(H+1)+V+1);
	heads.resize(H+1);
	tails.resize(H+1);
	vertices.resize(V+1);
	
	int idx=0;
	for(int h=0;h<=H;h++){
		heads[h]=&all[idx++];
		tails[h]=&all[idx++];
		heads[h]->next=tails[h];
		heads[h]->val=0;
		tails[h]->next=nullptr;
		tails[h]->val=V+1+h;//the h-th list
	}
	for(int v=0;v<=V;v++){
		vertices[v]=&all[idx++];
		vertices[v]->val=v;
	}
	
}

void tLlist::push_back(int v, int h){
	auto tmp=vertices[v];
	tmp->next=nullptr;
	tmp->val=V+1+h;//useful for remove, informs 
	vertices[v]=tails[h];
	vertices[v]->val=v;
	
	tails[h]=(vertices[v]->next)=tmp;
	++(heads[h]->val);//size
}


void tLlist::push_front(int v,int h){
	auto tmp=heads[h]->next;
	heads[h]->next=vertices[v];
	vertices[v]->next=tmp;
	++(heads[h]->val);//size
}

void tLlist::remove(int v,int h){
	auto tmp=vertices[v]->next;
	int& vv(tmp->val);
	vertices[v]->next=tmp->next;//for the last element it is nullptr
	vertices[v]->val=vv;
	if(vv>V){//last element
		tails[vv-V-1]=vertices[v];
	}else{//the next element is a plain node
		vertices[vv]=vertices[v];
	}
	vertices[v]=tmp;
	vv=v;
	--(heads[h]->val);
}


void write(tLlist& llst, FILE*fp=stderr){
	for(int d=0;d<=llst.H;d++){
		fprintf(fp,"%d(%d):",d,llst.heads[d]->val);
		auto it=llst.heads[d]->next;
		while((it->next)!=nullptr){
			fprintf(fp," %d",it->val);
			it=it->next;
		}
		fprintf(fp,"\n");
	}

	//	fprintf(stderr,"\n");
	fflush(fp);

}

#endif
