#ifndef __TARTALY_H__
#define __TARTALY_H__
#include "common.hpp"
#include "treap.hpp"
//tartalyok az ellista letrehozasahoz (hash,stb)
struct tartalyM{
   typedef long long int lli; 
   map<lli,bool> tar;
   tartalyM(int res){
   }
   bool insert(int a,int b){
      if(a>b){int t=a;a=b;b=t;}
      lli key=a;key=key<<32;key=key+b;
      if(tar.find(key)==tar.end()){
         printf("%d %d\n",a,b);
         tar[key]=true;
         return true;
      }
      return false;
   }
};

struct tartalyUM{
   typedef long long int lli; 
   unordered_map<lli,bool> tar;
   tartalyUM(int res){
      tar.reserve(res);
   }
   bool insert(int a,int b){
      if(a>b){int t=a;a=b;b=t;}
      lli key=a;key=key<<32;key=key+b;
      if(tar.find(key)==tar.end()){
         printf("%d %d\n",a,b);
         tar[key]=true;
         return true;
      }
      return false;
   }
};


//struct ipar {int a,b;};
// egészekből álló párok:
// typedef pair< int , int > ipar ;
bool operator==(const tII& lhs,const tII& rhs){
   return (lhs.x==rhs.x)&&(lhs.y==rhs.y);
}
//
struct IIhash{
   int operator()( tII const& X ) const{
//       int const h1( std::hash<int>()( X.x ) ) ;
//       int const h2( std::hash<int>()( X.y ) ) ;
//       return (h1^h2);
       return std::hash<int>()(53*(X.x+53)+X.y);
//       return 53*(X.x+53)+X.y;

       

       //       return (x.a>>1)^( x.b<<2 ) ;
   }
};
struct tartalyUS{
//   typedef long long int lli; 
   unordered_set<tII,IIhash> tar;
   int meret;
   tartalyUS(int Mx){
      tar.reserve(Mx);
      tar.max_load_factor(0.25);
      meret=0;
   }
   bool insert(int a,int b){
      if(a>b){int t=a;a=b;b=t;}
      auto res=tar.insert(tII{a,b}) ; 
      // res.second == true if successfully inserted
      if(res.second==true){
         ++meret;
         return true;
      }
      return false;
   }
   void clear(){
      tar.clear();
      meret=0;
   }
};

#define aTartaly tartalyUS

#endif
