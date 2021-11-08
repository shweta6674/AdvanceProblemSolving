#include<bits/stdc++.h>
#include <string>

using namespace std;

template <class T,class V>
class Ordmap
{
public:
        struct Node{
        T data;
        V value;
        Node *left;
        Node *right;
        int freq;
        int height;
        };
        Node *root;
int counter;

Ordmap()
{
        root=NULL;
        counter=0;
}

/*T const& get(int index) const;
void set(int index, T const&);*/

V& Ordmap<T,V>::operator[] ( T index){
    //How to check that which is called =>  v[5]=10(setting) or cout<<v[5]/getting)?
   int t=search(root,index);
   if (t==0){
	   cout<<"out of bound";
	   exit(0);
   }
   else {
	   
	   return search_v(root,index);
   }
}

/*void operator[] (T index, V const& val)
{
	
	
}*/


bool search(Node *&origptr, T item)
{
	if(origptr==NULL)
	return false;
	else if(item==origptr->data)
	return true;
	else if(item < origptr->data)
	return search(origptr->left,item);
	else if(item > origptr->data)
        return search(origptr->right, item);
	return false;

}

V search_v(Node *&origptr, T item)
{
	if(origptr==NULL)
		return;
	 if(item==origptr->data)
	return origptr->value;
	else if(item < origptr->data)
	return search_v(origptr->left,item);
	else 
        return search_v(origptr->right, item);
}


/*void search_set(Node *&origptr, T item, V val)
{
	if(origptr==NULL)
		return;
	 if(item==origptr->data)
	 origptr->value;
	else if(item < origptr->data)
	return search_v(origptr->left,item);
	else 
        return search_v(origptr->right, item);
}*/

Node* insert( Node *&origptr, T item, V val)
{
        if(origptr==NULL)
        {
            counter++;
        origptr=create_new( item,val);
        return origptr;
        }

        else if(item==origptr->data)
        {
                origptr->freq=1;
                origptr->value=val;
                return origptr;
        }

        else if(item < origptr->data)
        origptr->left=insert(origptr->left, item,val);

        else if(item > origptr->data)
        origptr->right=insert(origptr->right, item,val);

    origptr->height=1+maximum(sub_height(origptr->left),sub_height(origptr->right));

        int bal_factor= sub_height(origptr->left)-sub_height(origptr->right);
      /*cout<< bal_factor<<" ";*/
        if(bal_factor>1)
        {
                if(item<origptr->left->data)
                {
                        return rotateright(origptr);
                }

                else if(item>origptr->left->data)
                {
                        origptr->left=rotateleft(origptr->left);
                        return rotateright(origptr);
                }

        }
 else if(bal_factor<-1)
        {
                if(item>origptr->right->data)
                {
                        return rotateleft(origptr);
                }

                else if(item<origptr->right->data)
                {
                        origptr->right=rotateright(origptr->right);
                        return rotateleft(origptr);
                }

        }

             
   return origptr;
}

Node* delete_node( Node *&origptr, T item)
{
        if(origptr==NULL)
        {
        return origptr;
        }

        else if(item < origptr->data)
	{
	
        origptr->left=delete_node(origptr->left, item);
         
	}
        else if(item > origptr->data)
	{
	
        origptr->right=delete_node(origptr->right, item);
	}

	else if(item==origptr->data)
        {
	       
                /*if(origptr->freq > 1)
		{
		origptr->freq=origptr->freq-1;
                return origptr ;
		}*/
     
	if((origptr->left == NULL) && (origptr->right == NULL))
	{
         counter--;
		Node *a=origptr;
		origptr=NULL;
		free(a);
		
		return origptr ;	
	}

	else if(origptr->left==NULL && origptr->right !=NULL)
	{
		 counter--;
		 Node* a=origptr->right;
                *origptr=*a;
                free(a);
	}
	else if(origptr->left!=NULL && origptr->right ==NULL)
	{
	
	         counter--;
		 Node* a=origptr->left;
                *origptr=*a;
                free(a);

	}
	else
	{
		
		Node* a = origptr->right;
		 while (a->left != NULL)
   		     a = a->left; 
		origptr->data=a->data;
		origptr->value=a->value;
		origptr->freq=a->freq;
		origptr->right=delete_node(origptr->right,a->data);

	}

     }
    origptr->height=1+maximum(sub_height(origptr->left),sub_height(origptr->right));

        int bal_factor= sub_height(origptr->left)-sub_height(origptr->right);
      
        if(bal_factor>1)
        {
                if(item<origptr->left->data)
                {
                        return rotateright(origptr);
                }

	else if(item>origptr->left->data)
                {
                        origptr->left=rotateleft(origptr->left);
                        return rotateright(origptr);
                }

        }
 	else if(bal_factor<-1)
        {
                if(item>origptr->right->data)
                {
                        return rotateleft(origptr);
                }

                else if(item<origptr->right->data)
                {
                        origptr->right=rotateright(origptr->right);
                        return rotateleft(origptr);
                }

        }


   return origptr;
}



Node * create_new(T item,V val)
{
Node *leaf=NULL;
leaf= new Node;
leaf->data =item;
leaf->value=val;
leaf->left=NULL;
leaf->right=NULL;
leaf->freq=1;
leaf->height=1;
return leaf;

}
int maximum(int l, int r)
{
if(l>r)
return l;
else
return r;

}

Node * rotateleft(Node *origptr)
{
Node *l=NULL;
Node *r=NULL;

r=origptr->right;
l=r->left;

r->left=origptr;
origptr->right=l;

origptr->height=1+maximum(sub_height(origptr->left),sub_height(origptr->right));
r->height=1+maximum(sub_height(r->left),sub_height(r->right));

return r;


}

Node * rotateright(Node *origptr)
{
Node *l=NULL;
Node *r=NULL;

l=origptr->left;
r=l->right;

l->right=origptr;
origptr->left=r;

origptr->height=1+maximum(sub_height(origptr->left),sub_height(origptr->right));
l->height=1+maximum(sub_height(l->left),sub_height(l->right));

return l;


}


int sub_height(Node *origptr)
{
        if(origptr==NULL)
                return 0;
        else
        return (origptr->height);
}



void Inorder(Node *nodeptr)
{
    if(nodeptr != NULL)
    {
      
        Inorder(nodeptr->left);
         cout << nodeptr->data << "=>"<<nodeptr->value<<" "<<"("<<nodeptr->freq<<")"<<" ";
        Inorder(nodeptr->right);
    }
}


void clear(Node *&origptr)
{

	if(origptr!=NULL)
	{
		
		clear(origptr->left);
		clear(origptr->right);
		delete origptr;
	}
	origptr=NULL;
}

};

int main()
{
Ordmap<int,int>* tree;
tree= new Ordmap<int,int>;



tree->root= tree->insert(tree->root,3,5);
tree->root= tree->insert(tree->root,7,6);
tree->root= tree->insert(tree->root,12,12);
tree->root= tree->insert(tree->root,10,10);
tree->root= tree->insert(tree->root,10,56);
tree->root= tree->insert(tree->root,5,8);
tree->Inorder(tree->root);

cout<<tree[5];
/*
tree->root= tree->delete_node(tree->root,3);
tree->root= tree->delete_node(tree->root,7);
tree->Inorder(tree->root);

cout<<tree->search(tree->root,3);
cout<<tree->search(tree->root,7);
cout<<tree->search(tree->root,12);
cout<<tree->search(tree->root,10);
cout<<tree->search(tree->root,5);
tree->Inorder(tree->root);

cout<<"\n"<<tree->counter<<"\n";
tree->clear(tree->root);
tree->counter=0;
tree->Inorder(tree->root);
tree->root= tree->insert(tree->root,3,5);
tree->Inorder(tree->root);
cout<<"\n"<<tree->counter<<"\n";
/*tree->root= tree->delete_node(tree->root,12);
tree->root= tree->delete_node(tree->root,10);
tree->root= tree->delete_node(tree->root,10);
tree->root= tree->delete_node(tree->root,5);
tree->Inorder(tree->root);


/*int p=2,f=0;
tree->klargest(tree->root,p,f);*/

/*tree->root=tree->insert(tree->root,7);
 tree->Inorder(tree->root);*/
/*
int val;
int n,q,p,t,f=0;
cin>>n;
for(int j=1;j<=n;j++)
{
cin>>q;

switch (q){
    case 1:
            cin>>val;
            tree->root= tree->insert(tree->root,val);    
        break;
    case 2:
            cin>>val;
            tree->root= tree->delete_node(tree->root,val); 
        break;

    case 3:
            cin>>val;
           cout<<tree->search(tree->root,val)<<"\n"; 
        break;
    case 4:
         cin>>val;
            cout<<tree->search_count(tree->root,val)<<"\n"; 
        break;
    case 5:
            cin>>val;
            tree->lower(tree->root,val,val); 
        break;
    case 6:
             cin>>val;
           tree->upper(tree->root,val,val); 
        break;
    case 7:
            cin>>val;
            tree->closest(tree->root,val,100000,val); 
        break;
    case 8:
                
                 cin>>p;
                 f=0;
              tree->klargest(tree->root,p,f);
        break;
    case 9:
                cout<<"Range"<<"\n";
        break;
    case 10:
                tree->Inorder(tree->root);
        break;
}

}*/
return 0;
}
