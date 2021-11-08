#include <bits/stdc++.h>
using namespace std;

#define capacity 80
#define div 31

template<class K,class D>
class Unordr_map{
public:

class mnode{
	
public:
	K key;
	D data;
	mnode *link;
	};
	mnode* map_buk[capacity];

	Unordr_map()
	{
		long long i=0;
		while(i<capacity)
		{
			map_buk[i]=NULL;
			i++;
		
		}
	
	}
	
	int insert(K keyval, D dataval)
	{
		mnode *new_node = new mnode;
		new_node->key = keyval;
        new_node->data = dataval;
        new_node->link = NULL;
		
		long long pos = gethash_val(keyval);
		mnode *start= map_buk[pos];
		
		if(start==NULL)
		{
			start=new_node;
			map_buk[pos]=start;
			/*cout<<start->key<<" "<<start->data<<" "<<"\n";*/
			return 1;
		}
		else 
		{
			int ft=0;
			while(start->link != NULL)
			{
				if(keyval==start->key)
				{
					ft=1;
					return 0;
				}
				start=start->link;
			}
			
			if(ft==0)
			{
				if(keyval==start->key)
				return 0;
				else
				{
					start->link=new_node;
					start=start->link;
					/*cout<<start->key<<" "<<start->data<<" "<<"\n";*/
					return 1;
				}
			
			}
		}
		
	}
	
	long long gethash_val(K keyval)
	{
		long long a = 1;
		long long h_val = 0;
		
		ostringstream st;
        st << keyval;
        string str = st.str();
		
        for (long long i = 0; i < str.size(); i++)
        {
            h_val =h_val+ (a*str[i]);
			a = a*div;
            h_val =h_val%capacity;
        }
        return h_val;
		
		
	}
	
	int delete_mp(K keyval)
	{
		
		long long pos = gethash_val(keyval);
		mnode *start= map_buk[pos];
		mnode *ptr=start;
		
		if(start==NULL)
		{
			return 0;
		}
		else 
		{
			if(start->link==NULL )
			{
			    if( keyval==start->key)
			    {ptr = start;
                map_buk[pos] = NULL;
                free(ptr);
                return 1;}
                else
                {
                    return 0;
                }
                
			}
			else
			{
			    if( keyval==start->key)
			    {ptr = start;
                map_buk[pos] = ptr->link;
                free(ptr);
                return 1;}
			    
			}
			
			mnode *old=start;
			start=start->link;
			
			while(start != NULL)
			{
				if(keyval==start->key)
				{
					ptr=start;
					old->link=ptr->link;
					old=old->link;
					free(ptr);
					return 1;
				}
				if(start->link != NULL)
				{
					old=start;
					start=start->link;
					
				}
				else
				{
				    break;
				}
				
			}
			
			return 0;
			
			
		}
		
	}
	
	int find(K keyval)
	{
		
		long long pos = gethash_val(keyval);
		mnode *start= map_buk[pos];
		
		if(start==NULL)
		{
			return 0;
		}
		else 
		{
			while(start->link != NULL)
			{
				if(keyval==start->key)
				{
					return 1;
				}
				start=start->link;
			}
			
			if(keyval==start->key)
				return 1;
			else
				{
				return 0;
				}
			
		}
		
	}
	
	 pair<D,bool> map(K keyval)
	{
		 pair<D, bool> outp;
		long long pos = gethash_val(keyval);
		mnode *start= map_buk[pos];
		
		if(start==NULL)
		{
			outp.second=false;
			return outp;
		}
		else 
		{
			while(start->link != NULL)
			{
				if(keyval==start->key)
				{
					outp = {start->data,true};
					return outp;
				}
				start=start->link;
			}
			
			if(keyval==start->key)
			{
			   	outp = {start->data,true};
					return outp;
			}
				
			else
				{
				outp.second=false;
				return outp;
				}
			
		}
		
	}
	
void display()
    {
        for (long long j = 0; j < capacity ; j++)
        {
            
            cout<< j << " - ";
            mnode *ptr = map_buk[j];
            while (ptr != NULL)
            {
                cout << "{" << ptr->key << "=>" << ptr->data << "}";
                ptr = ptr->link;
            }
            cout << "\n";
        }
    }
	
};

int main()
{
	Unordr_map<string,int> umap;
	int i;
	i=umap.insert("4",4);
	i=umap.insert("3",3);
		i=umap.insert("2",2);
			i=umap.insert("7",7);
				i=umap.insert("8",8);
					i=umap.insert("5",5);
				i=umap.insert("9",9);
					i=umap.insert("11",11);
				i=umap.insert("12",12);
	cout<<i<<"\n";
	i=umap.insert("4",6);
	cout<<i<<"\n";
	i=umap.find("3");
	cout<<i<<"\n";
		i=umap.find("2");
		cout<<i<<"\n";
		i=umap.find("7");
		cout<<i<<"\n";
		i=umap.find("8");
		cout<<i<<"\n";
	 umap.display();
	 pair<int, bool> res;
	 res=umap.map("3");
	  if (res.second == true)
                cout << res.first << endl;
            else
                cout << "Not Found" << endl;
    i=umap.delete_mp("3");
    		cout<<i<<"\n";
    	i=umap.find("3");
    		cout<<i<<"\n";
    umap.display();
     i=umap.delete_mp("12");
    		cout<<i<<"\n";
     umap.display();
      i=umap.delete_mp("9");
    		cout<<i<<"\n";
     umap.display();
     i=umap.delete_mp("5");
    		cout<<i<<"\n";
     umap.display();
     i=umap.delete_mp("7");
    		cout<<i<<"\n";
     umap.display();
     i=umap.delete_mp("4");
    		cout<<i<<"\n";
     umap.display();
     i=umap.delete_mp("2");
    		cout<<i<<"\n";
     umap.display();
	return 0;
}