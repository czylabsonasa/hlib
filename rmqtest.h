#ifndef __RMQTEST_H__
#define __RMQTEST_H__

namespace RMQ{

   struct{
      LLI rsvd;//reserved
      void init(){
         rsvd=0;
      }
      template<typename T> T* getmem(int len){
         rsvd+=len*sizeof(T);
         return new T[len];
      }
      LLI memReserved(){return rsvd;}
   }mynew;

   struct base{

      int aN;
      pI a;
      int mem;
      base(){};
      ~base(){};
      virtual void init(pI _a){
         aN=_a[0];a=_a;
         mem=0;
      }
      virtual int operator()(int,int)=0;
      virtual string name() {
         return "undefined";
      }
      
      //~ int* RequestIntArray(int len) {
         //~ mem+=sizeof(int)*len;
         //~ return new int[len];
      //~ }
      
      //~ int** RequestIntPArray(int len) {
         //~ mem+=sizeof(int*)*len;
         //~ return new int*[len];
      //~ }
      
      //~ int MemoryUsage() {
         //~ return mem;
      //~ }
   };


   struct rmqBF:base{
      int operator()(int q0, int q1){//q0<=q1
         return rangemin(a+q0,a+q1+1);
      }
      
      string name() {
         return "BRUTEFORCE";
      }
   };

   struct rmqSQRT2:base {
      int block_sz;
      pI t;
      int *table;
      int h,m;
         
      void init(pI _t) {
         base::init(_t);
         block_sz=sqrt(aN);
         t=_t;
   //      table=RequestIntArray(aN/block_sz+2);
         table=mynew.getmem<int>(aN/block_sz+2);

         t++;
         int lim=(aN+block_sz-1)/block_sz;
         for(int i=1;i<=lim;++i) {
            table[i]=2000000000;
            for(int j=(i-1)*block_sz;j<i*block_sz && j<aN;++j) {
               table[i]=min(table[i], t[j]);
            }
         }
      }
      
      int operator()(int a, int b) {
         a--;b--;
         int ans=2000000000;
         //cerr<<a<<" "<<b<<" "<<ans<<"\n";

         if((b+1)-(a+1)<=2*block_sz) {
            for(int i=a;i<=b;++i) {
               ans=min(ans,t[i]);
            }
            
           // cerr<<"\n";
            return ans;
         }
         //cerr<<a<<" "<<b<<" "<<ans<<"\n";

         int eddig=(a+block_sz-1)/block_sz*block_sz;
         for(;a<eddig;a++) {
            ans=min(ans,t[a]);
         }
         //cerr<<a<<" "<<b<<" "<<ans<<"\n";
         
         eddig=(b-block_sz+1)/block_sz*block_sz;
         for(;a<=b && eddig<=b;b--) {
            ans=min(ans,t[b]);
         }
         //cerr<<a<<" "<<b<<" "<<ans<<"\n";
         int ind=(b+1)/block_sz;
         while(a<=b) {
            if(ans>table[ind]) ans=table[ind];
            b-=block_sz;
            ind--;
         }
         //cerr<<a<<" "<<b<<" "<<"\n\n";
         return ans;
      }
      
      string name() {
         return "SQRTARON";
      }
   };

   struct rmqSegment2:base {
         int *tree;
         int *t;

         void init(pI t_) {
            base::init(t_);
            t=t_;

            tree = mynew.getmem<int>(2*aN);
            t++;
            for(int i=0;i<aN;++i) {
                  tree[i+aN]=t[i];
            }

            build();
         }

         void build() {
            for(int i=aN-1;i>0;--i) tree[i]=min(tree[2*i], tree[2*i+1]);
         }

         int query(int l, int r) {
            int res=2000000000;
            for(l+=aN, r+=aN;l<r;l>>=1, r>>=1) {
                  if(l&1) res=min(res, tree[l++]);
                  if(r&1) res=min(res, tree[--r]);
            }

            return res;
         }

         int operator() (int a, int b) {
            a--;
            return query(a,b);
         }

         string name() {
            return "SEGMENTNONREC";
         }

         ~rmqSegment2() {
            delete []tree;
         }
   };

   struct rmqSparse:base {
      int sz,log;
      pI t;
      int* dp;
      #define INDEXDP(x,y) dp[(x)+(y)*sz]
      
      void init(pI _t) {
         base::init(_t);
         t=_t;
         log=int(log2(aN))+2;
         sz=aN;
         t++;
      
               

         dp = mynew.getmem<int>((sz+1)*(log+1));
         
         //for(int i=0;i<sz;++i) {
         //   dp[i]=RequestIntArray(log);
         //}
      
         
         for(int i=0;i<sz;++i) {
            INDEXDP(i, 0)=t[i];
         }
         
         

         for(int j=1;j<log;++j) {
            for(int i=0;i<sz;++i) {
               INDEXDP(i, j)=min(INDEXDP(i, j-1), INDEXDP(min(sz-1,i+(1<<(j-1))), j-1));
            }
         }
         
      
      }
      
      int operator() (int a, int b) {
         a--;b--;
         
         int ans=2000000000;

         while(a<=b){
            if(a==b) {
               ans=min(ans, INDEXDP(a, 0));
               break ;
            }
            
            int i=0;
            for(i=log-1;i>=0 && a+(1<<i)>b;--i){
              if(a+(1<<i)<=b) break; 
            }
            
            ans=min(ans, INDEXDP(a, i));
            a+=(1<<i);
         }
         return ans;
      }
      
      ~rmqSparse() {
         delete[] dp;
      }
      
      string name() {
         return "SPARSE";
      }
   };

   struct rmqSegment1:base{
      pI t;
      int sz;
      int *tree;
      void init(pI _t) {
         base::init(_t);
         t=_t;
         t++;
         sz=aN;
         tree=mynew.getmem<int>(4*sz+100);
         build(1, 0, sz-1);
      }
      
      void pull(int ind) {
         tree[ind]=min(tree[2*ind], tree[2*ind+1]);
      }
      
      void build(int ind, int L, int R) {
         if(L==R) {
            tree[ind]=t[L];
         }else {
            build(2*ind, L, (L+R)/2);
            build(2*ind+1, (L+R)/2+1, R);
            pull(ind);
         }
      }
      
      int query(int ind, int L, int R, int i, int j) {
         if(R<i || j<L) return INT_MAX;
         if(i<=L && R<=j) {
            return tree[ind];
         }
         
         return min(query(2*ind, L, (L+R)/2, i, j), query(2*ind+1, (L+R)/2+1,R,i,j));
      }
      
      int operator() (int a, int b) {
         return query(1, 0, sz-1, a-1, b-1);
      }
      
      string name() {
         return "SEGMENTREC";
      }
      
      ~rmqSegment1() {
         delete[] tree;
      }
   };

   struct rmqCounting1:base {
      pI t;
      
      int **s;
      int *cnt;
      int R;
      
      void init(pI t_) {
         base::init(t_);
         t=t_;
         t++;
         R=0;
         for(int i=0;i<aN;++i) {
            R=max(R, t[i]);
         }
         
         
         
         cnt=mynew.getmem<int>(R+1);
         
         for(int i=0;i<=R;++i) {
            cnt[i]=0;
         }
         
         for(int i=0;i<aN;++i) {
            cnt[t[i]]++;
         }
         
         
         s = mynew.getmem<int*>(R+1);
         for(int i=0;i<=R;++i) {
            s[i]=new int[cnt[i]];
         }
         
         int *ind = mynew.getmem<int>(R+1);
         for(int i=0;i<=R;++i) {
            ind[i]=0;
         }
         for(int i=0;i<aN;++i) {
            s[t[i]][ind[t[i]]++]=i;
         }
         
         delete []ind;
         
      }
      
      int operator() (int a, int b) {
      a--;b--;
         int mxmi=min(t[a+rand()%(b-a+1)], min(t[a], t[b]));
         for(int i=0;i<mxmi;++i) {
            int* it=lower_bound(s[i], s[i]+cnt[i], a);
            if(s[i]+cnt[i]==it || *it>b) continue ;
            else {
               return i;
            }
         }
         
         return mxmi;
      }
      string name() {
         return "COUNTINGBIN";
      }
      
      ~rmqCounting1() {
         for(int i=0;i<=R;++i) delete[] s[i];
         delete[] s;
         delete[] cnt;
      }
      
      
   };

   struct rmqSQRT:base{
      pI pc;
      int sqaN;
      int h,m;//hanyados,maradek
      void init(pI _a){
         base::init(_a);
         sqaN=int(sqrt(aN));
         h=aN/sqaN;
         m=aN-sqaN*h;
         pc=mynew.getmem<int>(h+1);//precomputed
         ++a;//0 base is clearer
         for(int i=0;i<h;i++){
            pc[i]=rangemin(a+i*sqaN,a+(i+1)*sqaN);
         }
         if(m>0){
            pc[h]=rangemin(a+h*sqaN,a+aN);
         }
      }

      int operator()(int q0, int q1){
         --q0;--q1;
         int lo=q0/sqaN;
         int up=q1/sqaN;
         if(up-lo<2){//brute
            return rangemin(a+q0,a+q1+1);
         }

         int ans=rangemin(a+q0,a+(lo+1)*sqaN);//beg
         ans=min(ans,rangemin(pc+lo+1,pc+up));//mid
         ans=min(ans,rangemin(a+up*sqaN,a+q1+1));//end
         return ans;
      }
      
      string name() {
         return "SQRTAPA";
      }

      ~rmqSQRT(){
         delete[] pc;
      }
   };

   struct rmqCounting2:base {
         int *freq, R, *t;

         #define INDEXFREQ(x, y) freq[(x)+(y)*(R+1)]
         void init(pI t_) {
               base::init(t_);     
               t=t_;t++;

               R=0;
               for(int i=0;i<aN;++i) R=max(R, t[i]);

               freq = mynew.getmem<int>((R+1)*aN);
               for(int i=0;i<(R+1)*aN;++i) freq[i]=0;

               for(int i=0;i<aN;++i) {
                     INDEXFREQ(t[i],i)++;
               }

               for(int i=0;i<=R;++i) {
                     for(int j=0;j<aN;++j) {
                          INDEXFREQ(i, j) += (j>0 ? INDEXFREQ(i, j-1) : 0) + (i>0 ? INDEXFREQ(i-1, j) : 0) - (i>0&&j>0 ? INDEXFREQ(i-1,j-1) : 0);
                     }
               }
             
         }

         int operator() (int a, int b) {
               a--;b--;
               int l=0, r=R;
               while(l<r) {
                     int mid=(l+r)/2;
                     if(INDEXFREQ(mid, b)-(a>0?INDEXFREQ(mid,a-1):0)) {
                           r=mid;
                     }else {
                           l=mid+1;
                     }
               }

               return l;
         }

         string name() {
               return "COUNTINGTABLE";
         }

         ~rmqCounting2() {
               delete[] freq;
         }
   };



   void tester(base& mth, pI q, pI ans){//mth=method
      int& nans(ans[0]);nans=0;
      for(pI tq=q+1,eq=q+1+2*q[0];tq<eq; tq+=2){
         ans[++nans]=mth(tq[0],tq[1]);
      }
   }

   int*arr=nullptr;
   int arrN=10000;
   int*query=nullptr;
   int queryN=10000;
   int R=10000;
   struct {
   // grafparameterek
      char MELYIK[32];
      int SEED;
      //~ void defaults(){
         //~ _arrN=10000;
         //~ _queryN=10000;
         //~ _R=1000;
         //~ strcpy(_MELYIK,"1111111111111111");
         //~ _SEED=-1;
      //~ }
   //
      void init(){
         // defaults();
         FILE*fp=fopen("rmq.conf","r");
         if(nullptr==fp){_ERR("config error,using defaults...");return;}
printf("elvileg rmq.conf nyitva\n");
         char ass[128];//assignment
         while(1==fscanf(fp,"%s",ass)){
printf("ass: %s\n",ass);
            char* t=paramshelper(ass);
            while(1){
               _CHECK(arrN,=%d);
               _CHECK(queryN,=%d);
               _CHECK(R,=%d);
               //_CHECK(MELYIK,=%s);
               _CHECK(SEED,=%d);
               break;
            }
         }
         fclose(fp);
         mrand::init(SEED);
         arr=new int[arrN+1];
         arr[0]=arrN;
         for(int i=1;i<=arrN;i++){
            arr[i]=mrand::IRND(1,R);
         }
         query=new int[2*queryN+1];
         query[0]=queryN;
         for(int i=1;i<=queryN;i++){
            int x=mrand::IRND(1,arrN);
            int y=mrand::IRND(1,arrN);
            if(x>y){swap(x,y);}
            query[2*i-1]=x;query[2*i]=y;
         }
      }
   }rmqConfig;

}//namespace RMQ

#endif
