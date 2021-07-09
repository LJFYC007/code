/**************************************************************
	File name: gen.cpp
	Author: huhao
	Create time: Sat 15 Jun 2019 03:56:49 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
#include<stdlib.h>
const int N=500010;
int n,d[N];
int main()
{
	srand((unsigned long long)new char);
	n=10;
	printf("%d\n",n);
	fr(i,2,n)
	{
		int f=rand()%(i-1)+1;
//		while(d[f]==2)
//			f=rand()%(i-1)+1;
//		d[f]++;
		printf("%d %d %d\n",f,i,rand()%100+1);
	}
	return 0;
}
