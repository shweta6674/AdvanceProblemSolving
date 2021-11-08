#include<bits/stdc++.h>
#include <string>
using namespace std;

/*linked list*/
template <class T>
class stnode{
public:
        T val;
        stnode<T>* next;
};

/*stack*/
template<class T>
class Stack
{
private:
        stnode<T>* top;
public:
Stack(){
                top=NULL;
        }

void s_push(T item){

        stnode<T>* elem = new stnode<T>;
        elem->val = item;
        elem->next = NULL;

        if(top==NULL)
		{
                top=elem;
                /* cout<< 1st element pushed<<endl;*/
        }
        else

        {
                elem->next=top;
                top=elem;
                /*cout<<Element pushed<<endl;*/
        }


        }

void s_pop()
        {
                if(top==NULL)
                {
                        cout<< "Stack empty"<<endl;
                }

                 else if(top->next == NULL)
                {
                        /*cout<< top->val <<is popped<< endl;*/
                        top=NULL;
                }
                else
                {
                       stnode<T>* ptr = top;
                        top=top->next;
                        /*cout<< ptr->val <<is popped<< endl;*/
                        delete ptr;
                }

        }

T s_peek(){
                return top->val;

        }

bool s_empty()
                {
                        if(top == NULL)
                        return true;
                        else
                        return false;
                }

};

int precedence(char op)
{
        if(op=='+' or op=='-')
               return 1;
        else if(op=='*' or op=='/' or op=='%')
                return 2;
return 0;
}

double calculate(double op1, double op2, char operation)
{
        switch(operation){
                case '+':
                        return (op1+op2);
                        break;
                case '-':
                        return(op1-op2);
                        break;
                case '/':

                        try{ double t=op2;
                                if(op2!=0)
                                return op1/op2;
                                else
                                throw(op2);
                        }

                        catch(double t){cout<<"divide by zero exception ecountered,ignore result :";}

                        break;
                case '*':
                       return(op1*op2);
                        break;

                case '%':
                        try{ double t=op2;
                                if(op2!=0)
                                {
                                if (op1<0)
                                    op1=0-op1;
                                if (op2<0)
                                    op2=0-op2;
                                return ((int)op1%(int)op2);
                                }
                                else
                                throw(op2);
                        }

                        catch(double t){cout<<"modulo by zero exception ecountered,ignore result :";}
                        break;
        }

        return 0;
}

int main()
{
        /*Stack<int> st;
        st.s_push(22);
        st.s_push(32);
        cout<< st.s_peek()<<endl ;
        cout<< st.s_empty()<<endl ;
        st.s_pop();
        st.s_pop();
        st.s_pop();
       cout<< st.s_empty()<<endl;*/

        string expr;

        cin>>expr;
        Stack<char> oper;
        Stack<double> data;

        double op2,op1,res;

        char ch,ck,operation;
        int cc;
        int l = expr.length();
        for(int i=0;i<l;i++)
        {
                ch=expr[i];

                if(ch=='(' || ch==')' || ch=='+' || ch=='-' || ch=='*' || ch =='/' || ch=='%')
                {
                        if(oper.s_empty() || ch=='(' )
                                oper.s_push(ch);
                        else if(ch==')')
                        {
                                while(!(oper.s_empty()) && !(data.s_empty()) && (oper.s_peek()!= '('))
                                {
                                        op2=data.s_peek();
                                        data.s_pop();
                                        op1=data.s_peek();
                                       data.s_pop();
                                        operation=oper.s_peek();
                                        oper.s_pop();
                                        res= calculate(op1,op2,operation);
                                        data.s_push(res);
                                }
                                if(oper.s_peek()== '(')
                                {
                                        oper.s_pop();
                                }

                        }
                        else
                        {
                                while(!(oper.s_empty()) and (precedence(ch)<=precedence(oper.s_peek())))
                                {
                                        op2=data.s_peek();
                                        data.s_pop();
                                        op1=data.s_peek();
                                        data.s_pop();
                                        operation=oper.s_peek();
                                        oper.s_pop();
                                        res= calculate(op1,op2,operation);
                                        data.s_push(res);
                                }

                                oper.s_push(ch);

                        }

                }

                else{
                ck=expr[i];
                cc=(int)ck-48;
                string dd="" ;
                while((ck=='.') || (cc>=0 && cc<=9))
                {
                        dd=dd+ck;
                        i=i+1;
                        if(i<l)
                        {
                                ck=expr[i];
                         cc= (int)ck-48;
                        }
                        else
                        break;
                }

                        data.s_push(stod(dd));
                        i=i-1;
               }
        }

        while(!(oper.s_empty()))
        {
                op2=data.s_peek();
                 data.s_pop();
                op1=data.s_peek();
                  data.s_pop();
                 operation=oper.s_peek();
                   oper.s_pop();
                 res= calculate(op1,op2,operation);
                 data.s_push(res);

        }
        
        
        
        cout<<setprecision(5)<<fixed<< data.s_peek() << endl;
        return 0;


}
