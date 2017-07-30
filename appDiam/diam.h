#ifndef __DIAM_H__
#define __DIAM_H__
#include "inc.h"
#include "mrand.h"

struct bfsdiam:graph{
   int const INF;//beware of overflow :-)
   tVI dist[2],q[2],from[2]; //dist,queue,from
   int numofbfs;
   bfsdiam(int _NV):graph(_NV),INF(_NV+11){
      dist[0].resize(NV+1);
      dist[1].resize(NV+1);
      q[0].resize(NV+1);
      q[1].resize(NV+1);
      from[0].resize(NV+1);
      from[1].resize(NV+1);
   }

   void bfs(int const a,tVI& tq,tVI& td,tVI& tfr){
      ++numofbfs;
      fill(td.begin(),td.end(),INF);
      int head=0; int tail=1;
      tq[0]=a;td[a]=0;tfr[a]=0;
      while(head!=tail){
         int b=tq[head++];
         int db=td[b]+1;
         for(auto it=adj[b].begin();it!=adj[b].end();it++){
            if(db<td[*it]){
               td[*it]=db;
               tq[tail++]=*it;
               tfr[*it]=b;
            }
         }
      }//queue
      return;
   }

   void bfs(tVI& tmp,tVI& tq,tVI& td,tVI& tfr){//multiple starting vertex
      ++numofbfs;
      fill(td.begin(),td.end(),INF);
      int head=0,tail=0;
      for(auto it=tmp.begin();it!=tmp.end();it++){
         tq[tail++]=*it;
         td[*it]=0;
         tfr[*it]=0;
      }
      while(head!=tail){
         int b=tq[head++];
         int db=td[b]+1;
         for(auto it=adj[b].begin();it!=adj[b].end();it++){
            if(db<td[*it]){
               td[*it]=db;
               tq[tail++]=*it;
               tfr[*it]=b;
            }
         }
      }//queue
      return;
   }

   
/////////////////////
//    BRUTE FORCE
/////////////////////
   int bruteforce(){//brute force,for connected graphs
_LOG(_ERR("brute-force: "),tik(),numofbfs=0);
      int mx=0;
      tVI& q0(q[0]);tVI& d0(dist[0]);tVI& f0(from[0]);
      for(int a=1;a<=NV;a++){
         bfs(a,q0,d0,f0);
         mx=max(mx,d0[q0[NV-1]]);
      }
_LOG(_ERR("%lfs  visits: %d\n",tak(),numofbfs));      
      return mx;
   }//bfdiam

/////////////////////
//    SWEEP2
/////////////////////

   tPII sweep2(tFUNIV f){return sweep2(f());}
   tPII sweep2(int a){
_LOG(_ERR("sweep2: "),tik(),numofbfs=0);
      bfs(a,q[0],dist[0],from[0]);
      int i=0;
      int mx=dist[0][q[0][NV-1]];

      bfs(q[0][NV-1],q[1],dist[1],from[1]);
_LOG(_ERR("%lfs  visits: %d\n",tak(),numofbfs));      
      
      if(dist[1][q[1][NV-1]]>mx){
         mx=dist[1][q[1][NV-1]];
         i=1;
      }
      int step=mx/2;a=q[i][NV-1];
      const tVI& f(from[i]);
      while(step>0){a=f[a];--step;}
      
      return tPII{mx,a};
   }
   
/////////////////////
//    IFUB
/////////////////////
   int ifub(int s,int L=-1){
_LOG(_ERR("ifub: "),tik(),numofbfs=0);
      
      tVI& q0(q[0]);tVI& d0(dist[0]);tVI& f0(from[0]);
      tVI& q1(q[1]);tVI& d1(dist[1]);tVI& f1(from[1]);

      bfs(s,q0,d0,f0);
      int U;
      if(L>0){
         L=max(d0[NV-1],L);
         U=2*min(d0[NV-1],L);
      }else{
         L=d0[NV-1];
         U=2*L;
      }
      int i=NV-1;int pd=NV+11;
      while(i>0&&U-L>0){
         int d=d0[q0[i]];
         if(d<pd){
            U=min(U,2*d0[q0[i]]);
            pd=d;
         }
         
         bfs(q0[i],q1,d1,f1);
         int td=d1[q1[NV-1]];
         if(td>L){
            L=td;
         }
         i--;
      }
_LOG(_ERR("%lfs  visits: %d\n",tak(),numofbfs));      
      return L;
   }//ifub

   int ifub2(int s,int L=-1){
_LOG(_ERR("ifub2: "),tik(),numofbfs=0);
      tVI tmp;
      tVI& q0(q[0]);tVI& d0(dist[0]);tVI& f0(from[0]);
      tVI& q1(q[1]);tVI& d1(dist[1]);tVI& f1(from[1]);

      bfs(s,q0,d0,f0);
      int U;
      if(L>0){
         U=2*min(d0[NV-1],L);
         L=max(d0[NV-1],L);
      }else{
         L=d0[NV-1];
         U=2*L;
      }
      int i=NV-1;
      while(L<U){
         if(i==0){break;}
         tmp.push_back(q0[i]);
         int d=d0[q0[i]];
         while(d==d0[q0[i-1]]){tmp.push_back(q0[i-1]);i--;}
         bfs(tmp,q1,d1,f1);
         d=d1[q1[NV-1]];
         if(d>L){L=d;}
         U=min(U,2*d0[q0[--i]]);
      }
_LOG(_ERR("%lfs  visits: %d\n",tak(),numofbfs));      
      return L;
   }//ifub2


   
   
   int rndselect(){
//_LOG(_ERR("( unif.random node selection ) "));
      return mrand::IRND(1,NV);
   }
   
};
#endif
