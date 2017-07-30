#ifndef __UHV_H__
#define __UHV_H__
struct UHV{
   int N;
	vector<tII> info;
   int NC;
	UHV(int _N):N(_N),info(N+1),NC(N){}

	void init(){
      info[0].x=-1;info[0].y=0;
      for(int i=1;i<=N;i++){
         info[i].x=0;
         info[i].y=1;
      }
      NC=N;
	}

	int find(int ez){ // tomoriteses (PathCompressing)
		int mo=ez,t;
		while((t=info[mo].x)>0){mo=t;}
		while((t=info[ez].x)>0){
			info[ez].x=mo;
			ez=t;
		}
		return mo;
	}


	inline void unio(int egyik,int masik){
      egyik=find(egyik);
      masik=find(masik);
      if(egyik!=masik){
         info[egyik].x=masik;
         info[masik].y+=info[egyik].y;
         NC--;
      }
	}
};
#endif


//~ int main()
//~ {
	//~ const int N = 100008 ;
	//~ UHV uhv( N ) ;

	//~ int esetek ; Olvas( esetek ) ;
	//~ while( esetek -- )
	//~ {
		//~ int nodes ; Olvas( nodes ) ;
		//~ int edges ; Olvas( edges ) ;
		//~ int ans = nodes ;
		//~ if( edges )
		//~ {
			//~ uhv.Init( 0 , nodes ) ;
			//~ while( edges -- )
			//~ {
				//~ int a ;	Olvas( a ) ; 
				//~ int b ;	Olvas( b ) ;
				//~ a = uhv.PH( a ) ;
				//~ b = uhv.PH( b ) ;
				//~ if( a != b )
				//~ {
					//~ uhv.Unio( a , b ) ;
					//~ ans -- ;
				//~ }
			//~ }
		//~ }			
		//~ printf( "%d\n" , ans ) ;

	//~ }


	//~ return 0 ;
//~ }
