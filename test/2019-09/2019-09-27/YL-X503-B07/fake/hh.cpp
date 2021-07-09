/***************************************************************
	File name: fake.cpp
	Author: huhao
	Create time: Fri 27 Sep 2019 06:58:06 PM CST
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
#include<vector>
namespace fake
{
	const int N=600010,M=35000010;
	int n,m,begin[N],next[N],to[N],e,d[N],c[N],ans,s[M][2],v[M],r[N],cnt;
	vector<int> F[N];
	void add(int u,int v)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
	}
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void dfs(int u)
	{
		int v;
		fo(i,u)
			if(!d[v=to[i]])
			{
				d[v]=d[u]+1;
				dfs(v);
			}
	}
	int cmp(int a,int b)
	{
		return a>b;
	}
	void update(int k)
	{
		v[k]=v[s[k][0]]+v[s[k][1]];
	}
	void modify(int &k,int l,int r,int p)
	{
		if(!k)
			k=++cnt;
		if(l==r)
		{
			v[k]++;
			return;
		}
		int mid=(l+r)>>1;
		if(p<=mid)
			modify(s[k][0],l,mid,p);
		else
			modify(s[k][1],mid+1,r,p);
		update(k);
	}
	int merge(int a,int b)
	{
		if(!a||!b)
			return a+b;
		v[a]+=v[b];
		s[a][0]=merge(s[a][0],s[b][0]);
		s[a][1]=merge(s[a][1],s[b][1]);
		return a;
	}
	void chkmax(int &k,int l,int r,int V)
	{
		if(!V||!k)
		{
			k=0;
			return;
		}
		if(l==r)
		{
			v[k]=V;
			return;
		}
		int mid=(l+r)>>1;
		if(v[s[k][1]]<=V)
			chkmax(s[k][0],l,mid,V-v[s[k][1]]);
		else
		{
			s[k][0]=0;
			chkmax(s[k][1],mid+1,r,V);
		}
		update(k);
	}
	int query(int k,int l,int r,int p)
	{
		if(!k)
			return 0;
		if(l==r)
		{
//			printf("%d %d %d\n",k,l,v[k]);
			int A=v[k];
			v[k]=0;
			return A;
		}
		int mid=(l+r)>>1,A=0;
		if(p<=mid)
			A=query(s[k][0],l,mid,p);
		else
			A=query(s[k][1],mid+1,r,p);
		update(k);
		return A;
	}
	void print(int u,int l,int r)
	{
		if(!u)
			return;
		if(l==r)
		{
			printf(" %d %d\n",l,v[u]);
			return;
		}
		printf("  %d %d %d\n",l,r,v[u]);
		int mid=(l+r)>>1;
		print(s[u][0],l,mid);
		print(s[u][1],mid+1,r);
	}
	void solve(int u)
	{
		int V;
		fo(i,u)
			if(d[V=to[i]]>d[u])
			{
				solve(V);
				r[u]=merge(r[u],r[V]);
			}
		fr(i,0,F[u].size()-1)
			modify(r[u],1,n,F[u][i]);
//		printf("%d %d\n",u,ans);
//		print(r[u],1,n);
		if(c[u]<v[r[u]])
			chkmax(r[u],1,n,c[u]);
//		printf("%d\n",u);
//		print(r[u],1,n);
		ans+=query(r[u],1,n,d[u]);
//		printf("%d\n",u);
//		print(r[u],1,n);
	}
	int main()
	{
		n=read();
		m=read();
		fr(i,1,n)
			c[i]=read();
		fr(i,1,n-1)
		{
			int u=read(),v=read();
			add(u,v);
			add(v,u);
		}
		d[1]=1;
		dfs(1);
		fr(i,1,m)
		{
			int u=read(),v=read();
			if(d[u]>d[v])
				F[u].push_back(d[v]);
			else
				F[v].push_back(d[u]);
		}
		solve(1);
		printf("%d\n",ans);
		return 0;
	}
}
int main()
{
	freopen("fake.in","r",stdin);
	freopen("fake2.out","w",stdout);
	return fake::main();
}
