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
const int N=1000010;
int f[N];
int getf(int x)
{
	return x==f[x]?x:f[x]=getf(f[x]);
}
int Rand()
{
	return (rand()<<10)+rand();
}
int main()
{
	freopen("treap.in","w",stdout);
	srand((unsigned long long)new char);
	int n=1000000,p=Rand()%998244353;
	printf("%d %d\n",n,p);
	fr(i,1,n)
		f[i]=i;
	fr(i,1,n-1)
	{
		int u=Rand()%n+1,v=Rand()%n+1;
		while(getf(u)==getf(v))
		{
			u=Rand()%n+1;
			v=Rand()%n+1;
		}
		f[getf(u)]=getf(v);
		printf("%d %d\n",u,v);
	}
	return 0;
}
