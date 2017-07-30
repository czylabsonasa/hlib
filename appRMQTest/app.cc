#include "common.h"
#include "rmqtest.h"
using namespace RMQ;

int main(){
   rmqConfig.init();
   rmqConfig.set(_arrN,_queryN,_R);

//printf("%d %d %d\n",RMQ::arrN,RMQ::queryN,RMQ::R);
//printf("a=\n");write(a+1,a+1+aN);
//printf("q=\n");write(q+1,q+1+2*qN);

   vector<base*> rmqList={new BF, new SEGITER, new SEGREC, new SPTABLE, new SQRTARON, new SQRTAPA, new COUNTBIN, new COUNTTABLE};
   int ind=1;
   int* ansLocal=new int[_queryN+1];
   int* ans=new int[_queryN+1];
   printf("\n%10s %15s %15s %15s\n","result","algo","time(sec)","mem(bytes)");

   for(auto rmq:rmqList) {
      
      tik();
      mynew.init();
      rmq->init(_arr);
      
      tester(*rmq, _query, ansLocal);
      
      double timePassed=tak();
      
//write(ansLocal+1,ansLocal+1+qN);
      
      if(ind>1) {
         bool ok=true;
         for(int i=1;i<=_queryN;i++) {
            if(ans[i]!=ansLocal[i]) {
               printf("\033[0;31m%10s\033[0m","FAIL");
               ok=false;
               break ;
            }
         }
         if(ok) {
            printf("\033[1;32m%10s\033[0m","OK");
         }
      }else {
         printf("\033[1;32m%10s\033[0m","THEGOOD");
      }
      printf(" \033[1;36m%15s\033[0m \033[0;36m%15.4lf\033[0m \033[0;35m%15Ld\033[0m\n",rmq->name().c_str(),timePassed,mynew.memReserved());
      
      if(ind==1) for(int i=1;i<=_queryN;++i) ans[i]=ansLocal[i];
      
      ind++;
   }
   delete[] ansLocal;
   delete[] ans;


  
   return 0;
}
