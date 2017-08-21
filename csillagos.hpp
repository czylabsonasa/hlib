#ifndef __CSILLAGOS_H__
#define __CSILLAGOS_H__

// todo implement progress
//legeneral egy peldanyt a csillagos modellbol
#include "common.hpp"
#include "tartaly.hpp"


// handling (reading) parameters)
struct csillagosInfo{
// grafparameterek
   double P,Q,R;
   int LEPES;
   int NCSM;
   int WCSLIST,WELIST,WVTXWGT,WDEGLIST,PROGRESS;
	int V, E;//a vegen 
   int ISM;//szimulaciohoz
   void defaults(){
      P=Q=R=0.5;
      LEPES=100;
      NCSM=4;
      WCSLIST=WELIST=WVTXWGT=WDEGLIST=PROGRESS=0;
      ISM=0;
   }
//
   csillagosInfo(){
      defaults();
      FILE*fp=fopen("csillagos.conf","r");
      if(nullptr==fp){_ERR("config error,using defaults...");return;}
      char ass[128];//assignment
      while(1==fscanf(fp,"%s",ass)){
         char* t=paramshelper(ass);
         while(1){
            _CHECK(P,=%lf);
            _CHECK(Q,=%lf);
            _CHECK(R,=%lf);
            _CHECK(LEPES,=%d);
            _CHECK(NCSM,=%d);
            _CHECK(WCSLIST,=%d);
            _CHECK(WELIST,=%d);
            _CHECK(WVTXWGT,=%d);
            _CHECK(WDEGLIST,=%d);
            _CHECK(ISM,=%d);
            break;
         }
      }
      fclose(fp);
   }
};


// the starish struct
struct csillagos{
   csillagosInfo& csp;
   aTartaly& tar;
//
   double const P;
   double const Q;
   double const R;
   int const LEPES;
   int const NCSM;
//
   int* const buff;
   int** const csLista;
   int aLEPES,aCsucs;
	csillagos(csillagosInfo&, aTartaly& );
   ~csillagos();
   void clear();
   void PASampleKicsi();
   void PASampleNagy();
	void USampleNagy();
	void USampleKicsi();
	void step1st();
	void gen();
	void insert();
	void write();
};


csillagos::csillagos(csillagosInfo& _csp, aTartaly& _tar):
	csp(_csp),tar(_tar),
	P(_csp.P),Q(_csp.Q),R(_csp.R),LEPES(_csp.LEPES),NCSM(_csp.NCSM),
	buff(new int[NCSM*(LEPES+3)]),csLista(new int*[(LEPES+3)])
{
	aCsucs=aLEPES=0;
	int*pb=buff;
	for(int i=0;i<=LEPES;i++){csLista[i]=pb;pb+=NCSM;}
}


csillagos::~csillagos(){
	delete[] csLista;
	delete[] buff;
}


void csillagos::clear(){
	aLEPES=0;
	aCsucs=0;
	tar.clear();
}

 
// DOC::segédfüggvények a generáláshoz:
// 
// 
// PR-ágban használja az (NCS-1)= kisméretű csillagok súly szerinti választásához:
// a nagy csillagok közül választ súly szerint, majd egyet választ egyenletesen 
// az ő kis részcsillagaiból és berakja ennek a perifériájára az újat.
// 
// ???: 
//ez súly szerint választ a kicsikből? Azaz megfelel a preferential attachment
// választásnak ha az itt alkalmazott módon választunk?
//
// Annak az indoklása, hogy a módszer miért jó:
// tfh. NCSM=4, es (a,b,c)-t választjuk, és azon 4-es csillagok összsúly melyekben megvan 
// ez kis-csillag w, ekkor (a,b,c)-t a w/LEPES*1/3=w/(3*LEPES) valséggel választjuk ki,
// de generáló módszer szerint is w a súly ennek a kis-csillagnak, és összesen 3*LEPES 
// kis csillag van - tehát ugyanolyan valséggel választunk a két módszer szerint, 
// vagyis elég csak a nagycsillagok listájat karbantartani.

// Az aLEPES és aCsucs adminisztráció itt történik.
// PR ágban használja.


void csillagos::PASampleKicsi(){
	// mutató a választott régi "kicsi" csillagra
	int* const regi = csLista[ mrand::IRND( 1 , aLEPES ) ] ;
	// ebben lesz az új
	int* const uj = csLista[ ++aLEPES ] ;
	// másolás
	for( int i = 0 ; i < NCSM ; i++ ) { uj[ i ] = regi[ i ] ; }
	// az új csúcs periféria lesz
	int kihagy = mrand::IRND( 1 , NCSM-1 ) ;
	for( int i = kihagy ; i < NCSM-1 ; i++ ) { uj[ i ] = uj[ i+1 ] ; }
	uj[ NCSM-1 ] = ++aCsucs ;
}


// PA-val választ a létező nagy csillagokból
// az egyöntetűség miatt függvény készült belőle

void csillagos::PASampleNagy(){
	int* const uj = csLista[ aLEPES + 1 ] ;
	int* const regi = csLista[ mrand::IRND( 1 , aLEPES ) ] ;
	for( int i = 0 ; i < NCSM ; i++ ) { uj[ i ] = regi[ i ] ; }
	++aLEPES ;
}

// egyenletesen választ a létező csúcsok közül NCSM számút 
// és csinál belőlük egy csillagot
// a volt segedtömbben tartjuk karban a generálás során már 
// felhasznált csúcsokat.
// A P(1-R) ágban használjuk.

void csillagos::USampleNagy(){
	int* const uj=csLista[++aLEPES];
	uj[0]=mrand::IRND(1,aCsucs);
	// addig próbálgat amig az előzőektől különbözőt nem kap:
	for( int i=1;i<NCSM; ){
		while(1){
			int a=uj[i]=mrand::IRND(1,aCsucs);
			int j=0;while(uj[j]!=a){j++;}
			if(j==i){i++;break;}
		}
	}
}


// Egyenletesen választ a létező csúcsok közül NCSM-1-et,
// majd ezeket az uj csucs köré rakja perifériának
// Nagyon hasonló az USampleNagy-hoz.
//

void csillagos::USampleKicsi(){
	int* const uj=csLista[++aLEPES];
	uj[0]=aCsucs+1;
	// itt nem kell a volt-ot piszkálni, mert ez új csúcs
	// addig próbálgat amig az előzőektől különbözőt nem kap:
	for( int i=1;i<NCSM; ){
		while(1){
			int a=uj[i]=mrand::IRND(1,aCsucs);
			int j=0;while(uj[j]!=a){j++;}
			if(j==i){i++;break;}
		}
	}
	++aCsucs ;
}


// 
// kezdő alakzat beállítása
//

void csillagos::step1st(){
	// a kezdő csillag beállítása (1-2,1-3,1-4,...,1-NCS)
	int* const uj = csLista[ 1 ] ; 
	for( int i = 0 ; i < NCSM ; i++ ) { uj[ i ] = i+1 ; }
	aLEPES = 1 ;            
	insert();
	aCsucs = NCSM ;
}


// generating the graph

void csillagos::gen(){
	step1st() ;

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
			}else{ // egyenletesen a csúcsok közül, (1-P)(1-Q)
				USampleNagy() ;
				insert();
			}
		}
	}
	// gráfgenerálás vége
}


// inserts the newest stars edges to the hashtable

void csillagos::insert(){
	int* const akt=csLista[aLEPES];
	int a=akt[0];
	for(int j=1;j<NCSM;j++){
		tar.insert(a,akt[j]);
	}
}


//write the elist and cslist accordind to the config

void csillagos::write(){
	//function
	csp.V=aCsucs;
	if(1==csp.WCSLIST){
		FILE* fp=fopen("_cslist","w");
		fprintf(fp,"%d %d\n",LEPES,NCSM);
		for(int i=1;i<=LEPES;i++){
			int* const akt=csLista[i];
			for(int j=0;j<NCSM;j++){
				fprintf(fp,"%d ",akt[j]);
			}
			fprintf(fp,"\n");
		}
		fclose(fp);
	}
	csp.E=tar.meret;
	if(1==csp.WELIST){
		FILE* fp=fopen("_elist","w");
		fprintf(fp,"%d %d\n",aCsucs,tar.meret);
		for(auto it=tar.tar.begin();it!=tar.tar.end();it++){
			fprintf(fp,"%d %d\n",it->x,it->y);
		}
		fclose(fp);
	}
	if(1==csp.WVTXWGT){
		tVI res(1+aCsucs,0);
		for(int i=1;i<=LEPES;i++){
			int* const akt=csLista[i];
			for(int j=0;j<NCSM;j++){
				++res[akt[j]];
			}
		}
		writeVector(res,"_vtxwgtlist",1,"\n");
	}
	if(1==csp.WDEGLIST){
		tVI res(1+aCsucs,0);
		for(auto it=tar.tar.begin();it!=tar.tar.end();it++){
			++res[it->x];
			++res[it->y];
		}
		writeVector(res,"_deglist",1,"\n");
	}

}
   

#endif
