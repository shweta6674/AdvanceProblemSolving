#include <bits/stdc++.h>
using namespace std; 

int *suffix_array_c(char &txt, int n) ;

struct suff_node 
{ 
    int pos; 
    int rank[2]; 
}; 
  

int cmp(struct suff_node x, struct suff_node y) 
{ 

	if (x.rank[0] == y.rank[0])
	{
		if(x.rank[1] < y.rank[1])
			return 1;
		else
			return 0;
	}
	else{
		if(x.rank[0] < y.rank[0] )
			return 1;
		else
			return 0;
	}

} 
  

int *suffix_array_c(string &arr, int n) 
{ 
    
    struct suff_node suffix[n]; 
	int i=0;
	 int new_pos[n];  
	while(i<n)
	{
        suffix[i].pos = i; 
        suffix[i].rank[0] = int(arr[i]); 
		
		if((i+1) < n)
			suffix[i].rank[1]=int(arr[i + 1]);
		else
			suffix[i].rank[1]=-1;
		i++;
    } 
  
    sort(suffix, suffix+n, cmp); 
  
    for (int k = 4; k < 2*n; k = k*2) 
    { 
      
        
        int prev_rank = suffix[0].rank[0]; 
		int cur_rank = 0; 
        suffix[0].rank[0] = cur_rank; 
        new_pos[suffix[0].pos] = 0; 
 
        for (int i = 1; i < n; i++) 
        { 
            
            if (suffix[i].rank[0] == prev_rank &&  suffix[i].rank[1] == suffix[i-1].rank[1]) 
                   
            { 
                prev_rank = suffix[i].rank[0]; 
                suffix[i].rank[0] = cur_rank; 
            } 
            else 
            { 
				cur_rank=cur_rank+1;
                prev_rank = suffix[i].rank[0]; 
                suffix[i].rank[0] = cur_rank; 
            } 
			
			int tt=suffix[i].pos;
            new_pos[tt] = i; 
        } 
  
        
        for (int i = 0; i < n; i++) 
        { 
            int nextindex =  k/2+suffix[i].pos ; 
			
			if(nextindex < n)
			{
				int t=new_pos[nextindex];
				suffix[i].rank[1] = suffix[t].rank[0];	
					
				}
			else
				suffix[i].rank[1]=-1;
			
           /* suffix[i].rank[1] = (nextindex < n)? 
                                  suffix[new_pos[nextindex]].rank[0]: -1; */
        } 
  
         
        sort(suffix, suffix+n, cmp); 
    } 
  
   
    int *suffix_arr = new int[n]; 
	int j=0;
	while(j<n)
	{
		suffix_arr[j] = suffix[j].pos;
		j++;
	}
    /*for (int i = 0; i < n; i++) 
        suffix_arr[i] = suffix[i].pos; */
  
    return  suffix_arr; 
} 

 

int main(){
    
string st;

int nn;
cin>>nn;
while(nn--)
{
cin>>st;

/*string p1="dcabca"    ;*/
string str=st+st   ;

    int n = str.size(); 
    int *suff_arr =suffix_array_c(str,  n); 
    /*cout << "Following is suffix array for " << txt << endl; 
    printArr(suffixArr, n); */
    int len=0;
    
    for(int i=0;i<n;i++)
    {
      len= n-suff_arr[i] ;
      if(len>=n/2)
      {
      cout<<str.substr(suff_arr[i],n/2);
      break;}
      /*cout<<len<<" ";*/
        
    }
    
    delete [] suff_arr;
    cout<<"\n";
}    
    
  



return 0;
}