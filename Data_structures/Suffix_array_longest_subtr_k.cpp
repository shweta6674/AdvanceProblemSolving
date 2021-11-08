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

int *lcp_array(string &str,int *suff_arr,int n)
{
		int inverse_arr[n],p=0,next;
		int i=0;
		int *lcparr= new int[n];
		while(i<n)
		{
			inverse_arr[suff_arr[i]]=i;
			i++;
		}
		
		for(int j=0;j<n;j++)
		{
			if (inverse_arr[j]==n-1)
			{	p=0;
			continue;}
			next=suff_arr[inverse_arr[j]+1];
			while (j+p<n && next+p<n && str[j+p]==str[next+p])
				p=p+1;
			lcparr[inverse_arr[j]]=p;
			if(p)
				p=p-1;
		}
		
		return lcparr;
			
			
}
		
int get_min(int *lcp,int s,int e)
{
   int  min=lcp[s];
    for(int i=s;i<e;i++)
    {
        if(lcp[i]<min)
        min=lcp[i];
    }
    
    return min;
}


int main(){
    
string str;

int k;
cin>>k;


cin>>str;

/*string p1="dcabca"    ;*/
/*string str=st+st   ;*/

    int n = str.size(); 
    int *suff_arr =suffix_array_c(str,  n);
	/*for(int i=0;i<n;i++)
		cout<<suff_arr[i]<<"\t";
	cout<<"\n";*/
    int *lcp = lcp_array(str,suff_arr,n);
/*	for(int i=0;i<n;i++)
		cout<<lcp[i]<<"\t";*/
	
	
		
	int max=0;
	
	for(int i=0;i<=n-k;i++)
	{
	    int cpval= get_min(lcp,i,i+k-1);
	    
	    if(cpval>max )
	    {
	    max=cpval;
	    }
	    
	}
   
  if(max==0)
  cout<<-1;
  else
  cout<<max;
    
  



return 0;
}
