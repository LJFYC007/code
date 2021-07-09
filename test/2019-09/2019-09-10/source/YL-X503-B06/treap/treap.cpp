#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
namespace gc
{
	char s[1<<20|10],*a,*b;
	int getchar()
	{
		if(a==b)
		{
			fread(s,1,1<<20,stdin);
			a=s;
			b=s+(1<<20);
		}
		return *(a++);
	}
}
//495548796
int read()
{
	int r=0,t=1,c=gc::getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=gc::getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=r*10+c-48;
		c=gc::getchar();
	}
	return r*t;
}
#define i64 long long
namespace run
{
	const int N=2000010;
	const i64 mod=998244353;
	int n,begin[N],next[N],to[N],w[N],e;
	i64 ans[N],p,A;
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void add(int u,int v)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
	}
	i64 power(i64 a,i64 b,i64 p)
	{
		i64 r=1;
		a%=p;
		while(b)
		{
			if(b&1)
				r=r*a%p;
			a=a*a%p;
			b>>=1;
		}
		return r;
	}
	i64 inv(i64 a)
	{
		return power(a,mod-2,mod);
	}
	void dfs1(int u,int f)
	{
		int v;
		w[u]=1;
		fo(i,u)
			if((v=to[i])!=f)
			{
				dfs1(v,u);
				w[u]+=w[v];
			}
	}
	i64 W[N],I1[N],I2[N];
	void dfs2(int u,int f)
	{
		int v;
		fo(i,u)
			if((v=to[i])!=f)
			{
				int wu=w[u],wv=w[v],Wu=W[u],Wv=W[v];
				w[u]=n-w[v];
				w[v]=n;
				ans[v]=ans[u]*I2[wu]%mod*I2[wv]%mod;
				W[u]=((w[u]-1)+p)*I1[w[u]]%mod;
				W[v]=((w[v]-1)+p)*I1[w[v]]%mod;
				ans[v]=ans[v]*W[u]%mod*W[v]%mod;
				A=(A+ans[v])%mod;
				dfs2(v,u);
				w[u]=wu;
				w[v]=wv;
				W[u]=Wu;
				W[v]=Wv;
			}
	}
	int main()
	{
		n=read();
		p=read();
		fr(i,1,n-1)
		{
			int u=read(),v=read();
			add(u,v);
			add(v,u);
		}
		dfs1(1,0);
		ans[1]=1;
		fr(i,1,n)
			I1[i]=power(i,mod-2,mod);
		fr(i,1,n)
			I2[i]=power((i-1+p)*I1[i]%mod,mod-2,mod);
		fr(i,1,n)
		{
			W[i]=(w[i]-1+p)*I1[w[i]]%mod;
			ans[1]=ans[1]*W[i]%mod;
		}
		A=(A+ans[1])%mod;
		dfs2(1,0);
		printf("%lld\n",A*I1[n]%mod);
		return 0;
	}
}
int main()
{
	freopen("treap.in","r",stdin);
	freopen("treap.out","w",stdout);
	return run::main();
}
