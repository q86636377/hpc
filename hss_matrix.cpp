#include<iostream>
#include<stdlib.h>
using namespace std;
#define m 8000000   //row
#define n 8  //col
#define p 4
#define num_threads p
struct v
{
	int* tuble;
	int** array1;
	int* result;
	int left;
	int right;
};

void* get_result(void* data)
{
	struct v* v=(struct v*)data;
 	for(int i=v->left;i<=v->right;i++)
 	{
 		for(int j=0;j<n;j++)
 		{
 		 	v->result[i]+=v->array1[i][j]*v->tuble[j];
 		 }
	}
 	pthread_exit(0);
}


int main()
{
	int** a=(int**)malloc(sizeof(int*)*m);
	for(int i=0;i<m;i++)
	{
		a[i]=(int*)malloc(sizeof(int)*n);
	}
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			a[i][j]=i*n+j;
		}
	}

	int* b=(int*)malloc(sizeof(int)*n);
	for(int i=0;i<n;i++)
	b[i]=i;

	int* c=(int*)malloc(sizeof(int)*m);
	for(int i=0;i<m;i++)
	c[i]=0;

	pthread_t tid[num_threads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	for(int i=0;i<p;i++)
	{
        struct v* data=(struct v*)malloc(sizeof(struct v));
		data->left=i*(m/p);
		data->right=data->left+(m/p-1);
		data->tuble=b;
		data->array1=a;
		data->result=c;
		pthread_create(&tid[i],&attr,get_result,(void *)data);
	}
	for(int i=0;i<num_threads;i++ )
		pthread_join(tid[i],NULL);
	/*for (int i=0;i<m;i++ )
	{
		cout<<c[i]<<" ";
	}*/

	for(int i=0;i<m;i++)
        free(a[i]);
	free(a);
	free(b);
}

