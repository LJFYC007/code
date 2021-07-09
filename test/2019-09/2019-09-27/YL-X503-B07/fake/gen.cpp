/***************************************************************
	File name: gen.cpp
	Author: huhao
	Create time: Fri 27 Sep 2019 08:18:43 PM CST
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
const int N=300010;
int n,f[N],m;
#include<stdlib.h>
int main()
{
	freopen("fake.in","w",stdout);
	srand((unsigned long long)new char);
	n=m=300000;
	printf("%d %d\n",n,m);
	fr(i,1,n)
        printf("1%c",i==n?'\n':' ');
		// printf("%d%c",(int)sqrt(rand()%n+1),i==n?'\n':' ');
	fr(i,2,n)
	{
		f[i]=rand()%(i-1)+1;
		printf("%d %d\n",i,f[i]);
	}
	fr(i,1,m)
	{
		int u=rand()%n+1,v;
		v=u;
		while(f[v]!=0&&rand()%5)
			v=f[v];
		v=1;
		if(rand()%2)
			swap(u,v);
		printf("%d %d\n",u,v);
	}
	return 0;
}
