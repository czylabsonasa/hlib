#include "common.hpp"
#include "erdosrenyi.hpp"
#include "uhv.hpp"



int main(){

   mrand::init(-1);
   erdosrenyiInfo eri;
   erdosrenyi er(eri);
   destat dst;

   FILE*fp=fopen("sim","a");
   vector<tII> elek;
   UHV uhv(eri.N);
   tVI n2s(eri.N+1,0);
   tik();    
   for(int ism=0;ism<eri.ISM;ism++){
      er.genGeom(elek);
      uhv.init();
      for(int i=1;i<elek.size();i++){
         uhv.unioifneq(elek[i].x,elek[i].y);
      }
      node2size(uhv,n2s);//n2s[i] size of the unionfind tree rooted at i
      simp(n2s);
      dst.comp(n2s);
      write(dst, "komponensek");//write previously computed descriptives

      sort(n2s.begin()+1,n2s.end());
      FILE*fq=fopen("compfrek","w");
      int akt=n2s[1];int fakt=1;
      int i=2;
      while(i<n2s.size()){
         if(n2s[i]!=akt){
            fprintf(fq,"%d %d\n",akt,fakt);
            akt=n2s[i];
            fakt=0;
         }
         ++fakt;
         i++;
      }
      fprintf(fq,"%d %d\n",akt,fakt);
      fclose(fq);

      
   }//ISM
   _ERR("er geom :%lf sec\n",tak());

   fclose(fp);

   



   return 0;
}
