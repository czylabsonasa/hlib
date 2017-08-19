#ifndef __RMQTEST_H__
#define __RMQTEST_H__
#include "common.hpp"

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
      base(){};
      ~base(){};
      virtual void init(pI _a){
         aN=_a[0];a=_a;
      }
      virtual int operator()(int,int)=0;
      virtual string name() {
         return "undefined";
      }
   };


   struct BF:base{
      int operator()(int q0, int q1){//q0<=q1
         return Min(a+q0,a+q1+1);
      }
      
      string name() {
         return "BF";
      }
   };

   struct SQRTARON:base {
      int block_sz;
      pI t;
      int *table;
      int h,m;
         
      void init(pI _t) {
         base::init(_t);
         block_sz=sqrt(aN);
         t=_t;
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

   struct SEGITER:base {
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
            return "SEGITER";
         }

         ~SEGITER() {
            delete []tree;
         }
   };

   struct SPTABLE:base {
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
      
      ~SPTABLE() {
         delete[] dp;
      }
      
      string name() {
         return "SPTABLE";
      }
   };


#define eval(x,y) dp[(x)+(y)*aN]
   struct SPTABLE2:base {
      int* dp;//dp[i,j]=min [i,i+2^j) semi-open interval 0<= i+2^j < aN
      void init(pI _a){
         base::init(_a);
         const int l2s=1+int(log2(aN));//
         dp = mynew.getmem<int>(l2s*aN);
         a++;//!!!
         for(int i=0;i<aN;i++){//i<aN-1
            eval(i,0)=a[i];
         }
         for(int j=1,j1=2;j<l2s;j++,j1<<=1){
            for(int i=0;i+j1<aN;i++){
               eval(i,j)=min(eval(i,j-1),eval(i+(j1>>1),j-1));
            }
         }
      }
      
      int operator() (int lo, int up) {
         --lo;--up;
         if(up-lo<2){return Min(a+lo,a+up+1);}
         int ans=a[up];//pont jo, mert jobbrol nyitott a dp
//         int t=int(log2(up-lo));
         int t=31-__builtin_clz(up-lo);
         ans=min(ans,eval(lo,t));
         return min(ans,eval(up-(1<<t),t));
      }
      
      ~SPTABLE2() {
         delete[] dp;
      }
      
      string name() {
         return "SPTABLE2";
      }
   };




   struct SEGREC:base{
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
         return "SEGREC";
      }
      
      ~SEGREC() {
         delete[] tree;
      }
   };

   struct COUNTBIN:base {
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
         return "COUNTBIN";
      }
      
      ~COUNTBIN() {
         for(int i=0;i<=R;++i) delete[] s[i];
         delete[] s;
         delete[] cnt;
      }
      
      
   };

   struct SQRTAPA:base{
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
            pc[i]=Min(a+i*sqaN,a+(i+1)*sqaN);
         }
         if(m>0){
            pc[h]=Min(a+h*sqaN,a+aN);
         }
      }

      int operator()(int q0, int q1){
         --q0;--q1;
         int lo=q0/sqaN;
         int up=q1/sqaN;
         if(up-lo<2){//brute
            return Min(a+q0,a+q1+1);
         }

         int ans=Min(a+q0,a+(lo+1)*sqaN);//beg
         ans=min(ans,Min(pc+lo+1,pc+up));//mid
         ans=min(ans,Min(a+up*sqaN,a+q1+1));//end
         return ans;
      }
      
      string name() {
         return "SQRTAPA";
      }

      ~SQRTAPA(){
         delete[] pc;
      }
   };

   struct COUNTTABLE:base {
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
               return "COUNTTABLE";
         }

         ~COUNTTABLE() {
               delete[] freq;
         }
   };



   void tester(base& mth, pI q, pI ans){//mth=method
      int& nans(ans[0]);nans=0;
      for(pI tq=q+1,eq=q+1+2*q[0];tq<eq; tq+=2){
         ans[++nans]=mth(tq[0],tq[1]);
      }
   }

   vector<base*> listAll=
   {new BF, new SEGITER, new SEGREC, new SPTABLE, new SPTABLE2, 
   new SQRTARON, new SQRTAPA, new COUNTBIN, new COUNTTABLE};

   vector<base*> listAkt;


   int*_arr=nullptr;
   int _arrN=10000;
   int*_query=nullptr;
   int _queryN=10000;
   int _R=10000;
   char _WHICH[256];
   struct {
   // grafparameterek
      char MELYIK[32];
      int _SEED;

      void init(){
         _WHICH[0]=0;
         FILE*fp=fopen("rmq.conf","r");
         if(nullptr==fp){_ERR("config error,using defaults...");return;}
         char ass[256];//assignment
         while(1==fscanf(fp,"%255[^\n] ",ass)){//they called it "negated scanset"
            char* t=paramshelper(ass);
            if(t==nullptr){continue;}
            while(1){
               _CHECK(_arrN,=%d);
               _CHECK(_queryN,=%d);
               _CHECK(_R,=%d);
               _CHECK(_WHICH,=%s);
               _CHECK(_SEED,=%d);
               break;
            }
//printf("%s\n",_WHICH);
         }
         fclose(fp);
         mrand::init(_SEED);
         _arr=new int[_arrN+1];
         _query=new int[2*_queryN+1];
         _arr[0]=_arrN;
         _query[0]=_queryN;

         setlist();
      }
      void set(int taN=_arrN, int tqN=_queryN, int tR=_R){
         _arr[0]=taN;
         for(int i=1;i<=taN;i++){
            _arr[i]=mrand::IRND(1,tR);
         }
         _query[0]=tqN;
         for(int i=1;i<=tqN;i++){
            int x=mrand::IRND(1,taN);
            int y=mrand::IRND(1,taN);
            if(x>y){swap(x,y);}
            _query[2*i-1]=x;_query[2*i]=y;
         }
      }
      void setlist(){
         if(_WHICH[0]==0){return;}
         char*beg=_WHICH;
         while(1){
            while(*beg&&!isalnum(*beg)){beg++;}
            if(!*beg){break;}
            char*end=beg;
            while(isalnum(*end)){end++;}
            string tmp(beg,end);
            for(auto it=listAll.begin();it!=listAll.end();it++){
               if((*it)->name()==tmp){
                  listAkt.push_back(*it);
                  break;
               }
            }
            beg=end;
         }
      }
      
      void cleanup(){
         delete[] _arr;
         delete[] _query;
      }
   }rmqConfig;


   

}//namespace RMQ

#endif
