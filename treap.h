
namespace Treap {
   struct Treap {
      pair<int,int> val;
      int pri;
      Treap *L, *R;
      
      Treap(const pair<int,int>& v) {
         val=v;
         pri=rand();
         L=NULL;R=NULL;
      }
   };
   
   void rotate_left(Treap*& root) {
      Treap* j=root->R;
      root->R=j->L;
      j->L=root;
      root=j;
   }
   
   void rotate_right(Treap*& root) {
      Treap* b=root->L;
      root->L=b->R;
      b->R=root;
      root=b;
   }
   
   bool insert(Treap*& root, const pair<int,int>& val) {
      if(root==NULL) {
         root=new Treap(val);
         return false;
      }
      
      bool res=false;
      if(root->val < val) {
         res|=insert(root->R, val);
         if(root->pri > root->R->pri) {
            rotate_left(root);
         }
      }else if(root->val > val) {
         res|=insert(root->L, val);
         if(root->pri > root->L->pri) {
            rotate_right(root);
         }
      }else {
         return true;
      }
      
      return res;
   }
}

struct tartalyT {
   //typedef long long int lli; 
   Treap::Treap* root;
   tartalyT(int res){
      root=NULL;
   }
   
   bool insert(int a,int b){
      if(a>b){int t=a;a=b;b=t;}
      bool ans=Treap::insert(root, pair<int,int>(a,b));
      if(!ans) printf("%d %d\n",a,b);

      return !ans;
      /*lli key=a;key=key<<32;key=key+b;
      if(tar.find(key)==tar.end()){
         printf("%d %d\n",a,b);
         tar[key]=true;
         return true;
      }*/
      
   }
   
};
