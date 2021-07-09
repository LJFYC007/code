/***************************************************************
	File name: gen.cpp
	Author: huhao
	Create time: Sat 15 Jun 2019 10:34:01 AM CST
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
int main()
{
	srand((unsigned long long)new char);
	int n=1000,l=1100;
	printf("%d %d\n",n,l);
	fr(i,1,n)
		printf("%d%c",rand()%2,i==n?'\n':' ');
	return 0;
}
