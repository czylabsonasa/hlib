#ifndef __KLIKKES_H__
#define __KLIKKES_H__


//legeneral egy peldanyt a csillagos modellbol
#include "common.hpp"
#include "tartaly.hpp"


struct klikkesInfo{
// grafparameterek
   double P,Q,R;
   int LEPES;
   int NKM;//nagy klikk merete
   int WKLIST,WELIST;
   int V, E;//a vegen 
   int ISM;//szimulaciohoz
   void defaults(){
      P=Q=R=0.5;
      LEPES=100;
      NKM=4;
      WKLIST=WELIST=0;
      ISM=0;
   }
//
   klikkesInfo(){
      defaults();
      FILE*fp=fopen("klikkes.conf","r");
      if(nullptr==fp){_ERR("config error,using defaults...");return;}
      char ass[128];//assignment
      while(1==fscanf(fp,"%s",ass)){
         char* t=paramshelper(ass);
         while(1){
            _CHECK(P,=%lf);
            _CHECK(Q,=%lf);
            _CHECK(R,=%lf);
            _CHECK(LEPES,=%d);
            _CHECK(NKM,=%d);
            _CHECK(WKLIST,=%d);
            _CHECK(WELIST,=%d);
            _CHECK(ISM,=%d);
            break;
         }
      }
      fclose(fp);
   }
};



struct klikkes{
   klikkesInfo& kp;
   aTartaly& tar;
//
   double const P;
   double const Q;
   double const R;
   int const LEPES;
   int const NKM;
//
   int* const buff;
   int** const kLista;
   int aLEPES,aCsucs;
   klikkes(klikkesInfo& _kp, aTartaly& _tar):
      kp(_kp),tar(_tar),
      P(_kp.P),Q(_kp.Q),R(_kp.R),LEPES(_kp.LEPES),NKM(_kp.NKM),
      buff(new int[NKM*(LEPES+3)]),kLista(new int*[(LEPES+3)])
   {
      aCsucs=aLEPES=0;
      int*pb=buff;
      for(int i=0;i<=LEPES;i++){kLista[i]=pb;pb+=NKM;}
   }
//
   ~klikkes(){
      delete[] kLista;
      delete[] buff;
   }
//
   void clear(){
      aLEPES=0;
      aCsucs=0;
      tar.clear();
   }

   void PASampleKicsi(){
      // mutató a választott régi "kicsi" klikkre
      int* const regi=kLista[mrand::IRND(1,aLEPES)];
      // ebben lesz az új
      int* const uj=kLista[++aLEPES];
      // másolás
      for(int i=0;i<NKM;i++){uj[i]=regi[i];}
      // az új csúcs periféria lesz
      int kihagy=mrand::IRND(1,NKM-1);
      for(int i=kihagy;i<NKM-1;i++){uj[i]=uj[i+1];}
      uj[NKM-1]=++aCsucs;
   }
   //
   // PA-val választ a létező nagy csillagokból
   // az egyöntetűség miatt függvény készült belőle
   //
   void PASampleNagy(){
      int* const uj=kLista[aLEPES+1];
      int* const regi=kLista[mrand::IRND(1,aLEPES)];
      for(int i=0;i<NKM;i++){uj[i]=regi[i];}
      ++aLEPES ;
   }
   //
   // egyenletesen választ a létező csúcsok közül NKM számút 
   // és csinál belőlük egy klikket
   // A P(1-R) ágban használjuk.
   //
   void USampleNagy(){
      int* const uj=kLista[++aLEPES];
      uj[0]=mrand::IRND(1,aCsucs);
      // addig próbálgat amig az előzőektől különbözőt nem kap:
      for(int i=1;i<NKM; ){
         while(1){
            int const a=uj[i]=mrand::IRND(1,aCsucs);
            int j=0;while(uj[j]!=a){j++;}
            if(j==i){i++;break;}
         }
      }
   }
   //
   // Egyenletesen választ a létező csúcsok közül NKM-1-et,
   // ezek az uj csuccsal alkotnak klikket
   // Nagyon hasonló az USampleNagy-hoz.
   //
   void USampleKicsi(){
      int* const uj=kLista[++aLEPES];
      uj[0]=aCsucs+1;
      // itt nem kell a volt-ot piszkálni, mert ez új csúcs
      // addig próbálgat amig az előzőektől különbözőt nem kap:
      for( int i=1;i<NKM; ){
         while(1){
            int a=uj[i]=mrand::IRND(1,aCsucs);
            int j=0;while(uj[j]!=a){j++;}
            if(j==i){i++;break;}
         }
      }
      ++aCsucs ;
   }
   //
   // 
   // kezdő alakzat beállítása
   //
   void step1(){
      // a kezdő klikk beállítása (1-2,1-3,1-4,...,(NKM-1)-NKM)
      int* const uj=kLista[1] ; 
      for(int i=0;i<NKM;i++){uj[i]=i+1;}
      aLEPES=1;            
      insert();
      aCsucs=NKM ;
   }
   //
   void gen(){
      step1() ;
      
      while(aLEPES<LEPES){
         if(mrand::DRND()<P){ // új csúcs születik
            // boviti a listat...
            if(mrand::DRND()<R){ // PR ág, az új szélső
               PASampleKicsi();
               insert();
            }
            else{ // P(1-R) ág
               USampleKicsi() ; // uni NCSM-1 + az új lesz a központ
               insert();
            }
         }
         else{
            if( mrand::DRND() < Q ){ // pa a nagyokból, (1-P)Q
               PASampleNagy() ;
               //nem kell insert a tartalyba, mert minden csucs regi
            }else{ // egyenletesen a csúcsok közül, (1-P)(1-Q)
               USampleNagy() ;
               insert();
            }
         }
      }
      // gráfgenerálás vége
   }
   //
   void write(){
      //NV+NE mindenkeppen beallitva
      kp.V=aCsucs;
      if(1==kp.WKLIST){
         FILE* fp=fopen("_klist","w");
         fprintf(fp,"%d %d\n",LEPES,NKM);
         for(int i=1;i<=LEPES;i++){
            int* const akt=kLista[i];
            for(int j=0;j<NKM;j++){
               fprintf(fp,"%d ",akt[j]);
            }
            fprintf(fp,"\n");
         }
         fclose(fp);
      }
      kp.E=tar.meret;
      if(1==kp.WELIST){
         FILE* fp=fopen("_elist","w");
         fprintf(fp,"%d %d\n",aCsucs,tar.meret);
         for(auto it=tar.tar.begin();it!=tar.tar.end();it++){
            fprintf(fp,"%d %d\n",it->x,it->y);
         }
         fclose(fp);
      }
   }
   
   void insert(){
      int* const akt=kLista[aLEPES];
      for(int j=0;j<NKM-1;j++){
         const int a=akt[j];
         for(int k=j+1;k<NKM;k++){
            tar.insert(a,akt[k]);
         }
      }
   }
   
}; // klikk

#endif
