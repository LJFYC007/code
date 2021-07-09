/***************************************************************
	File name: flow.cpp
	Author: huhao
	Create time: Sat 10 Aug 2019 10:39:43 AM CST
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
	const int N=10010;
	int ans,begin[N],next[N],to[N],e,n,m,d[N];
	void add(int u,int v)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
	}
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	namespace calc1
	{
		int vis[N];
		int dfs(int u)
		{
			int r=1;
			vis[u]=1;
			fo(i,u)
				if(!vis[to[i]])
					r+=dfs(to[i]);
			return r;
		}
		void unset(int u)
		{
			vis[u]=0;
			fo(i,u)
				if(vis[to[i]])
					unset(to[i]);
		}
		int main(int u)
		{
			int ans=dfs(u)-1;
			unset(u);
			return ans;
		}
	}
	namespace calc2
	{
		int m[N],ans,a,b,f[N],F[N],is[N];
		void mark(int u,int v)
		{
			is[u]=1;
			fo(i,u)
				if(to[i]!=f[u])
				{
					if(F[u]==F[to[i]])
					{
						if(!is[to[i]])
							mark(to[i],v);
					}
					else
					{
						if(v>0)
							m[to[i]]|=v;
						else
							m[to[i]]=0;
					}
				}
			is[u]=0;
		}
		int calc(int u)
		{
			int k=m[u];
			ans++;
			fo(i,u)
				if(f[to[i]]==u)
					k|=calc(to[i]);
			ans+=k;
			return k;
		}
		void unset(int u)
		{
			f[u]=F[u]=0;
			fo(i,u)
				if(f[to[i]])
					unset(to[i]);
		}
		void getf(int u)
		{
			fo(i,u)
				if(!f[to[i]]&&f[u]!=to[i])
				{
					f[to[i]]=u;
					F[to[i]]=F[u];
					getf(to[i]);
				}
		}
		int main(int u)
		{
			ans=0;
			a=to[begin[u]];
			b=to[next[begin[u]]];
			unset(u);
			f[a]=u;
			F[a]=a;
			f[b]=u;
			F[b]=b;
			getf(a);
			getf(b);
			fr(i,1,n)
				fprintf(stderr,"    %d %d\n",f[i],F[i]);
			mark(a,1);
			calc(b);
			mark(a,-1);
			mark(b,1);
			calc(a);
			mark(b,-1);
			return ans;
		}
	}
	namespace calc3
	{
		int m[N],ans,a,b,c,f[N],F[N],is[N];
		void mark(int u,int v)
		{
			is[to[u]]=1;
			fo(i,u)
				if(to[i]!=f[u])
				{
					if(F[u]==F[to[i]])
					{
						if(!is[to[i]])
							mark(to[i],v);
					}
					else
					{
						if(v>0)
							m[to[i]]|=v;
						else
							m[to[i]]=0;
					}
				}
			is[to[u]]=0;
		}
		int calc(int u)
		{
			int k=m[u];
			ans++;
			fo(i,u)
				if(f[to[i]]==u)
				{
					int x=calc(to[i]);
					switch(x)
					{
						case 0:
							break;
						case 1:
						{
							if(k==2||k==4)
								k=3;
							else if(k==0)
								k=1;
							break;
						}
						case 2:
						{
							if(k==1||k==4)
								k=3;
							else if(k==0)
								k=2;
							break;
						}
						case 3:
						case 4:
						{
							if(k)
								k=3;
							else 
								k=4;
						}
					}
				}
			if(k!=0)
				ans++;
			if(k==3)
				ans++;
			return k;
		}
		void unset(int u)
		{
			f[u]=F[u]=0;
			fo(i,u)
				if(f[to[i]])
					unset(to[i]);
		}
		void getf(int u)
		{
			fo(i,u)
				if(!f[to[i]]&&f[u]!=to[i])
				{
					f[to[i]]=u;
					F[to[i]]=F[u];
					getf(to[i]);
				}
		}
		int main(int u)
		{
			ans=0;
			a=to[begin[u]];
			b=to[next[begin[u]]];
			c=to[next[next[begin[u]]]];
			unset(u);
			f[a]=u;
			F[a]=a;
			f[b]=u;
			F[b]=b;
			f[c]=u;
			F[c]=c;
			getf(a);
			getf(b);
			getf(c);
			fr(i,1,n)
				fprintf(stderr,"    %d %d\n",f[i],F[i]);
			mark(a,1);
			mark(b,2);
			calc(c);
			mark(a,-1);
			mark(b,-2);
			mark(a,1);
			mark(c,2);
			calc(b);
			mark(a,-1);
			mark(c,-2);
			mark(b,1);
			mark(c,2);
			calc(a);
			mark(b,-1);
			mark(c,-2);
			return ans;
		}
	}
	int main()
	{
		n=read();
		m=read();
		read();
		fr(i,1,m)
		{
			int u=read(),v=read();
			d[u]++;
			d[v]++;
			add(u,v);
			add(v,u);
		}
		fr(i,1,n)
			if(d[i]==1)
			{
				ans+=calc1::main(i);
				fprintf(stderr,"%d %d\n",i,calc1::main(i));
			}
			else if(d[i]==2)
			{
				ans+=calc2::main(i);
				fprintf(stderr," %d %d\n",i,calc2::main(i));
			}
			else 
			{
				ans+=calc3::main(i);
				fprintf(stderr,"  %d %d\n",i,calc3::main(i));
			}
		printf("%d\n",ans);
		return 0;
	}
}
int main()
{
	freopen("flow.in","r",stdin);
	freopen("flow.out","w",stdout);
	return run::main();
}
