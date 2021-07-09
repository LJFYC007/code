/***************************************************************
	File name: bf.cpp
	Author: huhao
	Create time: Sat 15 Jun 2019 04:29:42 PM CST
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
namespace run
{
	const int N=4010;
	int n,begin[N],next[N],to[N],w[N],e;
	double ans;
	void add(int u,int v,int _w)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
		w[e]=_w;
	}
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	double dfs(int u,int f)
	{
		int v;
		double r=0;
		fo(i,u)
			if((v=to[i])!=f)
				r+=dfs(v,u)/2+w[i];
		return r;
	}
	int main()
	{
		n=read();
		fr(i,2,n)
		{
			int u=read(),v=read(),w=read();
			add(u,v,w);
			add(v,u,w);
		}
		fr(i,1,n)
			ans+=2*dfs(i,0)/n;
		printf("%.5lf\n",ans);
		return 0;
	}
}
int main()
{
	return run::main();
}
