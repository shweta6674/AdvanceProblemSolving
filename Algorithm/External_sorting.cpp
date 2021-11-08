#include <bits/stdc++.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include<sstream>
using namespace std;

struct item{

        long long val;
        long long file_no;

};

void minheapify(vector<item> &a, long long i,long long n);
void merge_arr(long long *arr, long long l, long long m, long long r);
void merge_sort(long long *arr, long long p, long long q);
void buildminheap(vector<item> &a,long long n);


void merge_sort(long long *arr, long long p, long long q)
{
    if (p < q)
    {

        long long middle = (p+q)/2;


        merge_sort(arr, p, middle);
        merge_sort(arr, middle+1, q);

        merge_arr(arr, p, middle,q);
    }
}

void merge_arr(long long *arr, long long l, long long m, long long r)
{

    long long i,j,k;
    long long sub1 = m - l + 1;
    long long sub2 =  r - m;


    long long First[sub1];

    long long Second[sub2];


    for (long long i = 0; i < sub1; i++)
        First[i] = arr[l+ i];
    for (long long j = 0; j < sub2; j++)
        Second[j] = arr[m + 1+ j];


    i = 0;
    j = 0;
    k = l;
    while (i < sub1 && j < sub2)
    {
        if (First[i] <= Second[j])
        {
            arr[k++] = First[i++];

        }
        else
        {
            arr[k++] = Second[j++];

        }

    }
    while (i < sub1)
    {
        arr[k++] = First[i++];

    }
    while (j < sub2)
    {
        arr[k++] = Second[j++];
    }
}



void buildminheap(vector<item> &a,long long n)
{	
    	
    long long j;
    for (j = n/2; j >= 0; j--) {
        /*maxheapify(a, j,n);*/
	    minheapify(a,j,n);
    }
   
}


void minheapify(vector<item> &a, long long i,long long n)
{
    long long  left, right, smallest;
    item temp;
    smallest=i;
    left = (2*i+1);
    right = ((2*i)+2);
    if (left >=n)
        return;
    else {
        if (left < n && a[left].val < a[i].val) 
            smallest = left;
        else
            smallest = i;
        if (right < n  && a[right].val < a[smallest].val)  
            smallest = right;
        if (smallest != i) {
            temp = a[i];
            a[i] = a[smallest];
            a[smallest] = temp;
            minheapify(a, smallest,n);
        }
    }
}


int main(int argc, char* argv[])
{

string input,output;
input=argv[1];
output=argv[2];



int chunk =1000*1000; /*1024*1024*2;*/
/*long long ar[chunk]={0};*/

long long k=0;
/*long long row[chunk];*/
char infile[50];
strcpy(infile,argv[1]);
FILE* ptr =fopen(infile,"r");
long long buf;

long long k_files=0;
vector<string> filenames;

while(true){

long long k=0;
/*long long row[chunk]={0};*/
long long *row = new long long[chunk];
while(k<chunk && fscanf(ptr,"%lld,",&buf)==1)
{

/*prlong longf("%d\n",buf);*/
row[k++]=buf;

}

if(k==0)
break;

merge_sort(row,0,k-1);
k_files+=1;

char ch[50];
string fname=to_string(k_files)+"in.txt";
/*cout<<fname<<" ";*/
strcpy(ch,fname.c_str());

filenames.push_back(ch);
		FILE* fw = fopen(ch,"w");
		for(long long j=0;j<k;j++)
		{
			fprintf(fw,"%lld,", row[j]);
		}
		fclose(fw);
delete[] row;	

/*   for(long long i=0;i<k;i++)
	   cout<<row[i]<<"\n";*/
}
fclose(ptr);

/*cout<<k_files<<" ";*/

char outfile[50];
strcpy(outfile,argv[2]);

FILE* foutput = fopen(outfile,"w");
FILE* fd_files[k_files];
vector<item> pri_que;

/*cout<<k_files<<" ";*/
for(long long i=0;i<k_files;i++)
{
	char file[20];
	strcpy(file,filenames[i].c_str());
	fd_files[i]=fopen(file,"r");
	if(fscanf(fd_files[i],"%lld,",&buf)==1);
	{
	/*	cout<<buf<<"\t";*/
		item st;
		st.val=buf;
		st.file_no=i;
		pri_que.push_back(st);
		
	}

		/*cout<<pri_que[i].val<<"\t";*/
/*	fclose(fd_files[i]);*/
}

buildminheap(pri_que,k_files);
/*cout<<pri_que[0].val;*/
long long count=k_files;

while(count!=0)
{
	
	long long cfi=pri_que[0].file_no;
	fprintf(foutput,"%lld,",pri_que[0].val);
	if(fscanf(fd_files[cfi],"%lld,",&buf)==1)
	/*long long length=0;
	if((getline(&buf, &length, fd_files[cfi]))>0)*/
	{	/*fprlong longf(foutput,"%c",',');*/
		pri_que[0].val=buf;
		/*cout<<"befor-"<<buf;*/
		minheapify(pri_que,0,count);
		/*cout<<"aftermin- "<<pri_que[0].val;*/

	}
	else{
		count--;
		fclose(fd_files[cfi]);
		char file[20];
       		strcpy(file,filenames[cfi].c_str());
		remove(file);
		if(count==0)
		{
			break;
		}

            	pri_que[0] = pri_que[count];
		minheapify(pri_que,0,count);
	}


}

fclose(foutput);





return 0;








}