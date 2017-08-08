#ifndef __ARTP_H__
#define __ARTP_H__
#include "inc.hpp"
#include "graph.hpp"

struct artipt{
   const tVFLI& adj;//shall we modify it?
   tVI deg;
   int const NV;
   tVI node2cid; //component id of a node: 0 if removed
   int cid; //"global" for set the component label
   tVI cdb;//component mérete,darabszam
   tVI lab,low;//low: 
   tVI foundAP;//az AP-k vektora
   int tlab;//counter for prenum
   artipt(graph& _G):adj(_G.adj),deg(_G.deg),NV(_G.NV),
      node2cid(NV+1),cdb(NV+1),lab(NV+1),low(NV+1){}

   void init(bool partial=true){
      if(partial){
         for(int i=0;i<=NV;i++){
            lab[i]=low[i]=0;
         }
         cid=0;//!
         foundAP.clear();
      }else{
         for(int i=0;i<=NV;i++){
            node2cid[i]=-1;//nonzero
         }
      }
   }

   int AP(int s){
      int ret=0;//ha a vizsgalt komponensben nincs AP a komponens merete (RGB jelolt), else 0
      tlab=0;
      ++cid;
      int prelab=tlab;
      int presize=int(foundAP.size());
      dfs(s,0);
      cdb[cid]=tlab-prelab;//mennyit ment a tlab?

_ONOFF(if(cdb[cid]>1){_LOG(_ERR("%d gyokeru dfs-fa nagysaga,benne az AP-k szama:%d %d\n",s,cdb[cid],int(foundAP.size())-presize));});

   if(int(foundAP.size())==presize){
         ret=cdb[cid];
      }
      
      if(0==deg[s]){
         node2cid[s]=0;
      }
      return ret;
      
   }
   
   int remove(bool all=false){
      if(0==foundAP.size()){return false;}
      if(all==false){
         int bAP=0,bdg=0,bdb=0; //best node and deg
         for(auto it=foundAP.begin();it!=foundAP.end();it++){
            int adb=cdb[node2cid[*it]];
            if(adb>bdb){
               bdb=adb;
               bdg=deg[*it];
               bAP=*it;
               continue;
            }
            if(adb==bdb){
               if(deg[*it]>bdg){
                  bdg=deg[*it];
                  bAP=*it;
               }
            }
         }
   _LOG(_ERR("removing %d(%d)\n",bAP,deg[bAP]));
         node2cid[bAP]=0;
      }else{
         for(auto it=foundAP.begin();it!=foundAP.end();it++){
            node2cid[*it]=0;
         }
      }
      
      return true;
   }
   

   void dfs(int s,int prnt){
assert(s<=NV);
      
_ONOFF(_LOG(_ERR("---------------hibaker: s=%d\n",s)));
      low[s]=lab[s]=++tlab;
      node2cid[s]=cid;
      int nfia=0;//number of children in the dfs tree
      int wlow=0;//its childrens worst low
      int dg=1;//deg[s] a residual grafban
      const auto _B(adj[s].begin());
      const auto _E(adj[s].end());
      for(auto it=_B;it!=_E;it++){
         int t=*it;
         if(0==node2cid[t]){continue;}//already removed
         ++dg;
         if(0==lab[t]){//unvis
            dfs(t,s);
            low[s]=min(low[s],low[t]);
            wlow=max(wlow,low[t]);
            ++nfia;
         }else{
            if(t!=prnt){//the child is not parent
               low[s]=min(low[s],lab[t]);//low[t]?
            }
         }
      }
      if(0==prnt){//root node  
         deg[s]=dg-1;//starting from 1
         if(nfia>1){
            foundAP.push_back(s);
         }
      }
      else{
         deg[s]=dg;
         if(nfia>0&&wlow>=lab[s]){//nfia>0 is unneeded
            foundAP.push_back(s);
         }
      }
      return;
   }
};
#endif
