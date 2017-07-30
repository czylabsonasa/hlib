#include "common.h"
#include "erdosrenyi.h"


int main(){

   mrand::init(11);
   erdosrenyiInfo eri;
{
tik();    
   erdosrenyi er(eri);
   vector<tII> elek;
   er.genNaive(elek);
_ERR("er naive :%lf sec\n",tak());
}

{
tik();    
   erdosrenyi er(eri);
   vector<tII> elek;
   er.genGeom(elek);
_ERR("er geom :%lf sec\n",tak());
}


   return 0;
}
