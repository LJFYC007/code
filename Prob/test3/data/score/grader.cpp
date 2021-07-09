/***************************************************************
	File name: grader.cpp
	Author: huhao
	Create time: Sat 15 Jun 2019 09:55:03 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include"score.h"
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
namespace _query
{
	const int N=1010;
	int n,l,a[N],f[N],cnt,t;
	int query(int *b,int l)
	{
		fr(i,1,l)
			if(b[i]!=0&&b[i]!=1)
			{
				printf("19260817\n-2 -2\n");
				exit(0);
			}
		t=0;
		cnt++;
		int k=0;
		fr(i,2,l)
		{
			while(k&&b[i]!=b[k+1])
				k=f[k];
			if(b[i]==b[k+1])
				k++;
			f[i]=k;
		}
		k=0;
		fr(i,1,n)
		{
			while(k&&a[i]!=b[k+1])
				k=f[k];
			if(a[i]==b[k+1])
				k++;
			if(k==l)
			{
				if(l==n)
					t=1;
				return 1;
			}
		}
		return 0;
	}
	int main()
	{
		n=read();
		l=read();
		fr(i,1,n)
			a[i]=read();
		run(n);
		if(t)
			printf("19260817\n%d %d\n",l,cnt);
		else
			printf("19260817\n-1 -1\n");
		return 0;
	}
}
int query(int *b,int l){return _query::query(b,l);}
int main(){return _query::main();}
