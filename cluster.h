#ifndef __CLUSTER_H__
#define __CLUSTER_H__
#include "common.h"
#include "graph.h"

struct cluster{
   int NV;
   vector<bool> volt;
   tVI numtri;
   tVD lcc;
   //max capacity : _NV
   cluster(int const _NV):volt(_NV),numtri(_NV),lcc(_NV){}

//~ //naive: forall vertex: take the neighbours, put them in a vector, and iterate through the vector
//~ //to find the closing edges NV*maxdeg^2
   void init(int _NV){
      NV=_NV;
      volt.resize(NV+1);
      numtri.resize(NV+1);
      lcc.resize(NV+1);
   }
   
   void count(const graph& G){//numtri num of triangles centered at idx
      init(G.NV);
      for(int i=1;i<=NV;i++){
         volt[i]=false;
         numtri[i]=0;
      }
      
      for(int s=1;s<=G.NV;s++){
         if(G.deg[s]<2){
            continue;
         }
         auto it=G.adj[s];
         while(it!=nullptr){
            volt[it->t]=true;
            it=(it->nxt);
         }
         int& nt(numtri[s]);
         it=G.adj[s];
         while(it!=nullptr){
            auto ti=G.adj[it->t];
            while(ti!=nullptr){
               if(volt[ti->t]){++nt;}
               ti=(ti->nxt);
            }
            volt[it->t]=false;
            it=(it->nxt);
         }
      }
   }

//same as before with the reduced graph   
   void countR(const graph& rG){//put into c the cluster coeffs (L:local)
      init(rG.NV);
      for(int i=1;i<=NV;i++){
         volt[i]=false;
         numtri[i]=0;
      }

      for(int s=1;s<=NV;s++){
         if(rG.deg[s]<2){
            continue;
         }
         
         auto it=rG.adj[s];
         while(it!=nullptr){
            volt[it->t]=true;
            it=(it->nxt);
         }
         it=rG.adj[s];
         while(it!=nullptr){
            auto ti=rG.adj[it->t];
            while(ti!=nullptr){
               if(volt[ti->t]){
                  ++numtri[s];
                  ++numtri[it->t];
                  ++numtri[ti->t];
               }
               ti=(ti->nxt);
            }
            it=(it->nxt);
         }
         it=rG.adj[s];
         while(it!=nullptr){
            volt[it->t]=false;
            it=(it->nxt);
         }
      }
   }


   //a naivecount-nak megfeleloen a local clustering coefficient vector szamolja
   void coeff(const graph& G){//lcc: local clustering coeff
      count(G);
      for(int s=1;s<=NV;s++){
         lcc[s]=complcc(G.deg,s);
      }
   }

   //a naivecountR-nak megfeleloen a local clustering coefficient vector szamolja
   void coeffR(const graph& rG,const tVI& deg){//lcc: local clustering coeff, reduced graph!!!
      countR(rG);
      for(int s=1;s<=NV;s++){
         lcc[s]=complcc(deg,s);
      }
   }

   double complcc(const tVI& deg, int const s){
      double ans=0.0;
      if(numtri[s]>0){
         double den=deg[s];den*=(den-1.0);
         ans=2.0*double(numtri[s])/den;
      }
      return ans;
   }

};
#endif
