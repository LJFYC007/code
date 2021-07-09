/***************************************************************
	File name: std.cpp
	Author: huhao
	Create time: Sat 15 Jun 2019 02:40:31 PM CST
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
	const int N=1000010;
	int n,begin[N],next[N],to[N],w[N],e,F[N];
	double f[N],g[N],ans;
	void add(int u,int v,int _w)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
		w[e]=_w;
	}
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void dfs1(int u)
	{
		int v;
		f[u]=1;
		fo(i,u)
			if((v=to[i])!=F[u])
			{
				F[v]=u;
				dfs1(v);
				f[u]+=f[v]/2;
				ans+=f[v]*2*w[i];
			}
	}
	void dfs2(int u)
	{
		int v;
		fo(i,u)
			if((v=to[i])!=F[u])
			{
				g[v]=(g[u]-f[v]/2)/2+f[v];
				ans+=(g[u]-f[v]/2)*2*w[i];
				dfs2(v);
			}
	}
	int main()
	{
		n=read();
		fr(i,1,n-1)
		{
			int u=read(),v=read(),w=read();
			add(u,v,w);
			add(v,u,w);
		}
		dfs1(1);
		g[1]=f[1];
		dfs2(1);
		printf("%.5lf\n",ans/n);
		return 0;
	}
}
int main()
{
	return run::main();
}
