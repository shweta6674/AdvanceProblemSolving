#include<bits/stdc++.h>
using namespace std;

class Trie{
public: 
    Trie* child[2] = {};
    bool leaf;
    Trie(){
        leaf = false;
    }
};
class Checker {
private:
    Trie* root = new Trie();
public:

void build_trie(long long *num,long long n)
{
  
  long long val,pos;
  Trie* ptr=root;
   for(long long i=0;i<n;i++){
            val=num[i];
 ptr=root;
  for(long long i=40;i>=0;i--)
  {
    
    if(val&(long long)(1L<<i))
      pos=1;
    else
      pos=0;
    if(ptr->child[pos]==NULL)
     ptr->child[pos]=new Trie();

    ptr=ptr->child[pos]; 
  }
ptr->leaf=true;  
   }
}
long long max_xor(long long val)
{  
    Trie* ptr=root;
    long long pos,ind;
    long long output=0;
   
   for(long long i=40;i>=0;i--)
   {
      if(val&(long long)(1L<<i))
        pos=1;
      else
        pos=0;
         
       ind=(pos+1)%2;

     if(ptr->child[ind]!=NULL && ptr->leaf==false)
     {
      
       ptr=ptr->child[ind];
        output=output+pow(2,i) ;
     } 
     else {
     ptr=ptr->child[pos];
     }
   }
   
  return output; 
}
};

int main()
{
  long long n,x,t,q1;
  cin>>n;
  cin>>t; 
  long long vec[n];
  long long nn=n;
  int i=0;
  while(nn--)
   cin>>vec[i++];
    
    Checker c;
    c.build_trie(vec,n);
   
   q1=t;
   long long q[t];
   for(long long i=0;i<t;i++)
    cin>>q[i];

   
  for(long long i=0;i<t;i++)
  { 
    cout<<c.max_xor(q[i])<<"\n";
  }
return 0;
}