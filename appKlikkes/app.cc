// klikkes modell generalas es a graph letrehozasa (a tartalyon keresztul)
#include "common.hpp"
#include "klikkes.hpp"
#include "tartaly.hpp"

int main(){
   mrand::init(-1);

tik();
   klikkesInfo ki;
   aTartaly T(int(ki.LEPES*ki.P*ki.NKM));

   klikkes KL(ki, T);
   KL.clear(ki.LEPES);
   KL.gen();
_LOG(_ERR("model (tartaly)=%lf sec\n",tak()));
   KL.write();      

	return 0;
}
