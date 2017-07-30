#include "inc.h"
#include "mrand.h"
#include "params.h"
#include "csillagos.h"
#include "tartaly.h"
#include "graph.h"
#include "wgraph2.h"
#include "artp.h"


void compAPTA(const params& p,graph& G){
_LOG(_ERR("**************\n hi, this is APTA!\n**************\n"));
   artp art(G);
   art.init(false);//partial=false
   int rm=0;
   while(1){
      art.init(true);
      for(int i=1;i<=G.NV;i++){
         if(0==art.lab[i]&&0!=art.node2cid[i]){
            art.AP(i);
         }
      }
      //search and remove for the most destructive AP
_ERR(_LOG("artpontok szama: %d\n",int(art.foundAP.size())));   
      if(!art.remove()){break;}
      ++rm;
   }
_ERR(_LOG("no of rm-s:%d\n",rm));   
}

void compGAPR(const params& p,graph& G){//params:access P,Q,R for output
_LOG(_ERR("**************\n"));
_LOG(_ERR("hi, this is GAPR!\n"));
_LOG(_ERR("**************\n"));
   tVI step2AP;
   int rgb=0;
   artp art(G);
   art.init(false);//partial=false
   int step=0;
   while(1){
      art.init();
      int preAP=art.foundAP.size();
      for(int i=1;i<=G.NV;i++){
_ONOFF(_LOG(_ERR("   step=%d node=%d\n",step,i)));
         if(0==art.lab[i]&&0!=art.node2cid[i]){
            int t=art.AP(i);
            rgb=max(rgb,t);
         }
      }
      //search and remove for the most destructive AP
_ONOFF(_ERR(_LOG("artpontok szama a lepesben: %d\n",int(art.foundAP.size()))));   
      step2AP.push_back(art.foundAP.size()-preAP);
      if(!art.remove(true)){break;}
      step++;
   }
_ONOFF(_ERR(_LOG("no of steps:%d\n",step)));   

   FILE*fp=fopen("gapr","a");
   fprintf(fp,"%d %d %d %lf %lf %lf\n",G.NV,step2AP[0],rgb,p.P,p.Q,p.R);
   fclose(fp);
}

void compPAGERANK(const params& p,const graph& G){
   wgraph WG(G.NV,2*p.NE);
   const tVI& deg(G.deg);

   int const NV(G.NV);
   for(int s=1;s<=NV;s++){
      const auto _B(G.adj[s].begin());
      const auto _E(G.adj[s].end());
      for(auto it=_B;it!=_E;it++){
         WG.insertD(s,*it,1.0/double(deg[*it]));
      }
   }
//return;
   double* y=new double[p.NV+1];
   double* x=new double[p.NV+1];
   double* xx=new double[p.NV+1];
   double const d=0.85;
   
   {
      double tmp(1.0/NV);
      for(int i=1;i<=NV;i++){
         x[i]=tmp;
         y[i]=tmp*(1.0-d);
      }
   }
   
   double tol=1e-5;
   int const STEP=100;
   int step=1;
   while(step<STEP){
      swap(x,xx);
      for(int i=1;i<=NV;i++){x[i]=y[i];}
      for(int i=1;i<=NV;i++){
         double tmp=0.0;
         auto it=WG.adj[i];
         while(it!=nullptr){
            tmp+=xx[it->t]*(it->w);
            it=it->nxt;
         }
         x[i]+=tmp;
      }
      double diff=0;
      for(int i=1;i<=NV;i++){diff=max(diff,abs(x[i]-xx[i]));}
      if(diff<tol){break;}
      step++;
   }

}


int main(){

   mrand::init(111);//fix sorozat
tik();
   params p;
   p.conf(0);//0-nal letrehozza a model.work-ot

   aTartaly T(int(p.LEPES*p.P*p.NCSM));
   {
      csillagos CS(p,T);
      CS.clear();
      CS.step1();
      CS.gen();
      CS.write();      
   }
_LOG(_ERR("model (tartaly)=%lf sec\n",tak()));

tik();
   p.conf(1);
   graph G(p.NV,T);
_LOG(_ERR("graph (tartaly)=%lf sec\n",tak()));

tik();
   compPAGERANK(p,G);
_LOG(_ERR("pagerank=%lf sec\n",tak()));

return 0;

// tik();
//    T.clear();
// _LOG(_ERR("aTartaly cleared in %lf sec\n",tak()));


   
   //compAPTA(G);
tik();
   compGAPR(p,G);
_LOG(_ERR("GAPR lasted %lf sec\n",tak()));
   
// _LOG(
// for(int i=0;i<res.size();i++){
//    fprintf(stderr,"%d\n",G.deg[res[i]]);
// });
// return 0;   




_ERR(_LOG("\nvege\n\n"));

   return 0;
}
