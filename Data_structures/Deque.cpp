#include<iostream>
#include <string>
using namespace std;
/*deque*/
template <class T>
class deque{
private:
        int length;
		int front;
		int rear;
		T *arr;

		
public:
deque(){
				length=0;
                front=-1;
				rear=-1;
				arr=nullptr;
        }
deque(int size, T data)
{
	length=size;
	front=0;
	rear=size-1;
	arr=new T(size);
	for (int i = 0; i < length; i++) {
        arr[i]=data;
    }
}

void push_back(T item)
{
	if(is_full())
	{
		resize( length+1, item );
	}
	else if(length==0)
	{
		length=1;
	front=0;
	rear=0;
	arr=new T(1);
        arr[0]=item;
	}
	else 
	{
	if(empty())
	{
		rear=0;
		front=0;
	}
	else if(rear==length-1)
	{
		rear=0;
	}
	else
		rear=rear+1;
	arr[rear]=item;
	}
}

void pop_back()
{
	if(empty())
	{
		cout<<"Deque is currently empty,use push_back/push_front function to fill it";
	}
		else if(front==rear)
	{
		front=-1;
		rear=-1;
	}
	else if(rear==0)
	{
		rear=length-1;
	}

	else
		rear=rear-1;	
	  
}

void push_front(T item)
{
	if(is_full())
	{
		T *arr_new, *tmp;
		tmp=arr;
		int new_size=size()+1;
	arr_new =new T(new_size);
	int k=0;
	 if(rear>=front)
	{
		arr_new[k++]=item;
		
		for(int i =front;i<=rear;i++)
		{
			arr_new[k++]=arr[i];
		}
		rear=new_size-1;
		front=0;
		delete[] tmp;
		arr=arr_new;
		length=new_size;
		
	}
	else
	{
		arr_new[k++]=item;
		for(int i=front;i<length;i++)
		{
			arr_new[k++]=arr[i];
		}
		for(int i=0;i<=rear;i++)
		{
			arr_new[k++]=arr[i];
		}
		
			rear=new_size-1;
			front =0;
			delete[] tmp;
			arr=arr_new;
			length=new_size;
	}
	
	}
	else if(length==0)
	{
		length=1;
	front=0;
	rear=0;
	arr=new T(1);
        arr[0]=item;
	}
	else 
	{
	if(empty())
	{
		rear=0;
		front=0;
	}
	if(front==0)
	{
		front=length-1;
	}
	else
		front=front-1;
	arr[front]=item;
	}
}

void pop_front()
{
	if(empty())
	{
		cout<<"Deque is currently empty,use push_back/push_front option to fill it";
	}
	else if(front==length-1 )
	{
		front=0;
	}
	else if(front==rear)
	{
		front=-1;
		rear=-1;
	}
	else
		front=front+1;
	  
}

T on_front()
{
	if(!empty())
	{
		return arr[front];
	}
	else{
		cout<< "Queue is empty,returning default output ";
		return arr[0];
	}
	
}

T back()
{
	if(!empty())
	{
		return arr[rear];
	}
	else{
		cout<< "Queue is empty,returning default output ";
		return arr[0];
	}
}

bool empty()
{
	if (rear==-1 and front==-1)
		return true;
	else
		return false;
}

bool is_full()
{
	if((front==0 && rear==length-1) || (front==rear+1))
		return true;
	else
		return false;
}

void output()
{
    cout<<rear<<" "<<front<<endl;
    
    	for (int i = 0; i < length; i++) {
       cout <<arr[i]<< " ";
    }
    cout<<endl;
}
int size()
{
	if(empty())
		return 0;
	else if(is_full())
		return length;
	else if(rear>=front)
		return (rear-front+1);
	else
		return(length-front+rear+1);
}
void display()
{
	if(empty())
		cout<< "Queue is empty "<<endl;
	else if(rear>=front)
	{
		for(int i =front;i<=rear;i++)
		{
			cout<<arr[i]<<" ";
		}
		cout<<endl;
		
	}
	else
	{
		for(int i=front;i<length;i++)
		{
			cout<<arr[i]<<" ";
		}
		for(int i=0;i<=rear;i++)
		{
			cout<<arr[i]<<" ";
		}
		cout<<endl;
	}
	
}

void resize(int new_size, T item )
{
	if(new_size <= length)
	{
		
		if(new_size<size())
		{
			int t=size()-new_size;
			for(int i=1;i<= t;i++)
			{
				pop_back();
			}
		}
		else if(new_size>size())
		{
			int t=new_size -size();
			for(int i=1;i<= t;i++)
			{
				push_back(item);
			}
		}
			
	}
	
	else if (new_size >length) {
	T *arr_new, *tmp;
	tmp=arr;
	arr_new =new T(new_size);
	int k=0;
	if(length==0){
	    length=new_size;
	front=0;
	rear=new_size-1;
	arr=new T(new_size);
        for(int i=0;i< new_size;i++)
			{
				arr[i]=item;
			}
	}
	else if(empty())
	{
			for(int i=0;i< new_size;i++)
			{
				arr_new[i]=item;
			}
			delete[] tmp;
			arr= arr_new;
			length=new_size;
	}
	else if(rear>=front)
	{
		for(int i =front;i<=rear;i++)
		{
			arr_new[k]=arr[i];
			k++;
		}
		for(int i=k;i< new_size;i++)
			{
				arr_new[i]=item;
			}
		rear=new_size-1;
		front=0;
		delete[] tmp;
		arr=arr_new;
		length=new_size;
		
	}
	else
	{
		for(int i=front;i<length;i++)
		{
			arr_new[k++]=arr[i];
		}
		for(int i=0;i<=rear;i++)
		{
			arr_new[k++]=arr[i];
		}
		for(int i=k;i< new_size;i++)
			{
				arr_new[i]=item;
			}
			rear=new_size-1;
			front =0;
			delete[] tmp;
			arr=arr_new;
			length=new_size;
	}
	
	}
}

void clear()
{
	
	rear=-1;
	front=-1;
	length=0;
	T *tmp;
	tmp=arr;
	arr=nullptr;

}

void D(int n)
{
	if(n>length)
		cout<<"Exceeding deque length"<<endl;
	else
	{
		 if(rear>=front)
	{
		cout<<arr[front+n-1];
		cout<<endl;
	}
	else
	{
		if(n<=length-front)
			cout<<arr[front+n-1];
		else
		{
			n=n-(length-front);
			cout<<arr[n-1];
		}
		cout<<endl;
	}
	
	}
		
}

};


int main()
{
    deque<int> st(4,7);
int n,q;
int val;
int d_size,b_val;
cin >>n;
for(int i=1;i<=n;i++)
{
	cin>>q;
	switch(q){
		case 1:
			 cin>>val;
			 st.push_front(val);
			 st.display();
			 break;
		case 2:
			st.pop_front();
			st.display();
			break;
		case 3:
			cin>>val;
			st.push_back(val);
			st.display();
			break;
		case 4:
			st.pop_back();
			st.display();
			break;
		/*case 5:
			st.display();
			break;
		case 6:
			cin>>d_size;
			cin>>val;
			deque<int> st(d_size,val);
			st.display();
			break;*/
		case 7:
			cout<<st.on_front()<<endl;
			break;
		case 8:
			cout<<st.back()<<endl;
			break;
		case 9:
		    b_val= st.empty();
		    if (b_val==0)
			    cout<<"False"<<endl;
			 else
			    cout<<"True"<<endl;
			break;
		case 10:
			cout<<st.size()<<endl;
			break;
		case 11:
			cin>>d_size;
			cin>>val;
			st.resize(d_size,val);
			st.display();
			break;
		case 12:
			st.clear();
			st.display();
			break;
		case 13:
			cin>>d_size;
			st.D(d_size);
			break;
		case 14:
			st.display();
			break;
	}	
	}   

return 0;
}
