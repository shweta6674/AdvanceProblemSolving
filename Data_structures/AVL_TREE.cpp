#include<bits/stdc++.h>
#include <string>

using namespace std;

template <class T>
class Avltree
{
public:
        struct Node{
        T data;
        Node *left;
        Node *right;
        int freq;
        int height;
        };
        Node *root;

Avltree()
{
        root=NULL;
}

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


int search_count(Node *&origptr, T item)
{
        if(origptr==NULL)
        return 0;
        else if(item==origptr->data)
	{

		return origptr->freq;
	}
        else if(item < origptr->data)
        return search_count(origptr->left,item);
        else if(item > origptr->data)
        return search_count(origptr->right, item);
        return 0;

}

Node* insert( Node *&origptr, T item)
{
        if(origptr==NULL)
        {
        origptr=create_new( item);
        return origptr;
        }

        else if(item==origptr->data)
        {
                origptr->freq=origptr->freq+1;
                return origptr;
        }

        else if(item < origptr->data)
        origptr->left=insert(origptr->left, item);

        else if(item > origptr->data)
        origptr->right=insert(origptr->right, item);

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
	
                if(origptr->freq > 1)
		{
		origptr->freq=origptr->freq-1;
                return origptr ;
		}
     
	if((origptr->left == NULL) && (origptr->right == NULL))
	{

		Node *a=origptr;
		origptr=NULL;
		free(a);
		return origptr ;	
	}

	else if(origptr->left==NULL && origptr->right !=NULL)
	{
		
		 Node* a=origptr->right;
                *origptr=*a;
                free(a);
	}
	else if(origptr->left!=NULL && origptr->right ==NULL)
	{
	
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



Node * create_new(T item)
{
Node *leaf=NULL;
leaf= new Node;
leaf->data =item;
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

void preOrder(Node *nodeptr)
{
    if(nodeptr != NULL)
    {
        cout << nodeptr->data << " "<<"("<<nodeptr->freq<<")";
        preOrder(nodeptr->left);
        preOrder(nodeptr->right);
    }
}

void Inorder(Node *nodeptr)
{
    if(nodeptr != NULL)
    {
      
        Inorder(nodeptr->left);
         cout << nodeptr->data << " "<<"("<<nodeptr->freq<<")";
        Inorder(nodeptr->right);
    }
}


void closest(Node *origptr,T item,T diff,T cl)
{
	if(origptr==NULL)
        cout<<cl<<" ";

	else if(item==origptr->data)
	cout<<item<<"\n";

        else if(item < origptr->data)
	{
		if(diff> (origptr->data-item))
		{
		diff=origptr->data-item;
		cl=origptr->data;
		}
		else if(diff == (origptr->data-item))
		{
			if(cl>origptr->data)
			cl=origptr->data;

		}
        	closest(origptr->left,item,diff,cl);
        
	}

	else if(item > origptr->data)
	{
		if(diff> (item-origptr->data))
        	{
        	diff=item-origptr->data;
        	cl=origptr->data;
        	}
		 else if(diff == (item-origptr->data))
                {
                        if(cl>origptr->data)
                        cl=origptr->data;

                }


        	closest(origptr->right, item,diff,cl);

	}


}

void lower(Node *origptr,T item,T cl)
{
	if(origptr==NULL)
        cout<<cl<<" ";

	else if(item==origptr->data)
	cout<<item<<"\n";

        else if(item < origptr->data)
	{
			if(cl> (origptr->data) || cl == item )
		cl=origptr->data;
        	lower(origptr->left,item,cl);
        
	}

	else if(item > origptr->data)
	{

        	lower(origptr->right, item,cl);

	}

}

void upper(Node *origptr,T item,T cl)
{
	if(origptr==NULL)
        cout<<cl<<" ";

        else if(item < origptr->data)
	{
			if(cl> (origptr->data) || cl == item )
		cl=origptr->data;
        	upper(origptr->left,item,cl);
        
	}

	else if(item >= origptr->data)
	{

        	upper(origptr->right, item,cl);

	}

}

void klargest(Node *nodeptr,int &p,int &f)
{
   
     if(nodeptr != NULL && p>0)
    {
       /*cout<<nodeptr->data<<" ";
       cout<<p<<" ";*/
        klargest(nodeptr->right,p,f);
         if(p>0)
            p=p-nodeptr->freq;
              if(p<=0 && nodeptr != NULL && f==0)
    {
        cout<<nodeptr->data<<" ";
       f=1;
    
    }
         
        klargest(nodeptr->left,p,f);
    }
    
}


int count_range(Node *nodeptr,T low,T high)
{
    if(nodeptr == NULL)
		return 0;
    if(nodeptr->data == low &&  nodeptr->data == high )
		return nodeptr->freq;
	if( nodeptr->data >= low && nodeptr->data <= high )
		return  nodeptr->freq+(count_range(nodeptr->left,low,high)+count_range(nodeptr->right,low,high));
	else if(nodeptr->data< low)
		count_range(nodeptr->right,low,high);
	else if(nodeptr->data > high)
		count_range(nodeptr->left,low,high);

	}

};

int main()
{
Avltree<int>* tree;
tree= new Avltree<int>;


tree->root= tree->insert(tree->root,3);
tree->root= tree->insert(tree->root,7);
tree->root= tree->insert(tree->root,12);
tree->root= tree->insert(tree->root,10);
tree->root= tree->insert(tree->root,10);
tree->root= tree->insert(tree->root,5);
 tree->Inorder(tree->root);
cout<<tree->count_range(tree->root,3,8);
/*int p=2,f=0;
tree->klargest(tree->root,p,f);*/

/*tree->root=tree->insert(tree->root,7);
 tree->Inorder(tree->root);*/

/*int val,val1;
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
                cin>>val;
                cin>>val1;
                cout<<count_range(tree->root,val,val1)<<"\n";
        break;
    case 10:
                tree->Inorder(tree->root);
        break;
}

}*/
return 0;
}
