#include<bits/stdc++.h>
#include<vector>
#include<string>
#define MAX_INT 1000000007
using namespace std;


void  s_factorial(int n)
{
    	int j,carry=0,prod=1;;
			vector<int> fact;


		if(n==0 || n==1)
		{
			cout<< "1";
		}
		else
		{
			fact.push_back(1);

			for(int i=2;i<=n;i++)
			{
                carry=0;
				int l=fact.size();
				for(int j=0;j<l;j++){
					prod=fact[j]*i+carry;
					fact[j]=prod%10;
					carry=prod/10;
				}
				
				while(carry>0)
				{
					fact.push_back(carry%10);
					carry=carry/10;

				}

			}	
		}

	int len=fact.size();
	for(int i=len-1;i>=0;i--)
		cout<<fact[i];
	cout<<endl;

}

unsigned int  calc_modulo(string a,unsigned int k)
{
		int l=a.length();
		unsigned int mod_val;
		char ch;
		for(int i=0;i<l;i++)
		{
			ch=a[i] ;
			mod_val= (mod_val*10 + (int)ch-48)% k;
		}

		return mod_val;
}


unsigned int exponent_val(unsigned int t, unsigned int b)
{	
	unsigned int output =1;
	if (t==0)
		return 0;
	if (b==0)
		return 1;
	if(b==1)
		return t;
	output=exponent_val(t,b>>1);
	if(b%2==0)
		return (output*output)%MAX_INT;
	else
		return (t*output*output)%MAX_INT;
}
		

unsigned int my_gcd ( unsigned int a, unsigned int b )
{
    
    if(b==0)
    {
        return a;
    }
    else
    {
        return my_gcd(b,a%b);
    }
    

}
int main()
{
	
int n,q;
string a,b;
unsigned int c,t,x1,x2;
int x;
cin >>n;
for(int i=1;i<=n;i++)
{
	cin>>q;
	switch(q){
		case 1:
			cin>>a;
			cin>>c;
			t=calc_modulo(a,MAX_INT);
			cout<<exponent_val(t,c)<<endl;
			break;
		case 2:
			 cin>>a;
			 cin>>b;
			 x1=calc_modulo(a,MAX_INT);
			 x2=calc_modulo(b,MAX_INT);
			 cout<<my_gcd(x1,x2)<<endl;
			 break;
		case 3:
			cin>>x;
			s_factorial(x);
			break;
	}
}
return 0;
}
