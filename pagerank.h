#ifndef __PAGERANK_H__
#define __PAGERANK_H__

#include "inc.h"
#include "utils.h"
#include "graph.h"
#include "wgraph.h"

struct pagerankInfo{
// grafparameterek
   int MAXITER;
   double TOL;//stopping
   double D;//damping
   int iter;
   double diff;
   void defaults(){
      MAXITER=100;
      TOL=1e-5;
      D=0.85;
   }
//
   pagerankInfo(){
      defaults();
      FILE*fp=fopen("pagerank.conf","r");
      if(nullptr==fp){_ERR("config error,using defaults...");return;}
      char ass[128];//assignment
      while(1==fscanf(fp,"%s",ass)){
         char* t=paramshelper(ass);
         while(1){
            _CHECK(TOL,=%lf);
            _CHECK(D,=%lf);
            _CHECK(MAXITER,=%d);
            break;
         }
      }
      fclose(fp);
   }
};


struct pagerank{
   pagerankInfo& prp;
   int const MAXITER;
   double const TOL;
   double const D;
   pagerank(pagerankInfo& _prp):prp(_prp), 
      MAXITER(prp.MAXITER),TOL(prp.TOL),D(prp.D)
   {}
   
   void comp(const graph& G,vector<double>& info){
      wgraph WG(G.NV,G.NE);
      const tVI& deg(G.deg);
//for(int i=1;i<=G.NV;i++){printf("%d ",deg[i]);}printf("\n");
      int const NV(G.NV);
      for(int s=1;s<=NV;s++){
         auto it=G.adj[s];
         while(it!=nullptr){
            WG.insertD(s,it->t,1.0/double(deg[it->t]));
   //         WG.insertD(*it,s,1.0/double(deg[s]));
            it=(it->nxt);
         }
      }
//for(int i=1;i<=G.NV;i++){printf("%d ",WG.deg[i]);}printf("\n");


//return;
      double* y=new double[NV+1];
      double* x=new double[NV+1];
      double* xx=new double[NV+1];
   
   {
      double tmp(1.0/NV);
      for(int s=1;s<=NV;s++){
         x[s]=tmp;
         y[s]=tmp*(1.0-D);
      }
   }
   
      double diff;
      int iter=1;
      while(iter<=MAXITER){
         swap(x,xx);
         for(int s=1;s<=NV;s++){x[s]=y[s];}
         for(int s=1;s<=NV;s++){
            double tmp=0.0;
            auto it=WG.adj[s];//going through the neighbours
            while(it!=nullptr){
               tmp+=xx[it->t]*(it->w);
               it=it->nxt;
            }
            x[s]+=D*tmp;
         }
         div(x+1,x+NV+1,sum(x+1,x+NV+1));
         diff=0;
         for(int s=1;s<=NV;s++){diff+=abs(x[s]-xx[s]);}
         if(diff<TOL){break;}
         iter++;
      }
      prp.iter=iter;
      prp.diff=diff;

      for(int i=1;i<=NV;i++){
         info[i]=x[i];
      }

      delete[]x;
      delete[]xx;
      delete[]y;
   }//comp
};
#endif
