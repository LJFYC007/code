#include<bits/stdc++.h>
const int maxn=100000+10;
const int inf=1<<30;
struct Object { int a,b; } p[maxn];
int n,h[maxn],cnt=1,fr[maxn];long long ans,dis[maxn];bool vis[maxn];
struct edge { int v,nxt,f,c; } e[maxn<<2];
inline void add ( int u,int v,int f,int c )
{
	e[++cnt].nxt=h[u];e[h[u]=cnt].v=v;e[cnt].f=f;e[cnt].c=c;
	e[++cnt].nxt=h[v];e[h[v]=cnt].v=u;e[cnt].f=0;e[cnt].c=-c;
}
signed main()
{
	freopen("sky.in","r",stdin);
	freopen("sky.out","w",stdout);
	scanf("%d",&n);
	for ( int i=1;i<=n;i++ ) scanf("%d%d",&p[i].a,&p[i].b);
	std::sort(p+1,p+n+1,[&](const Object &p1,const Object &p2){return p1.a==p2.a ? p1.b<p2.b : p1.a<p2.a;});
	for ( int i=1;i<=n;i++ ) add(n+1,i,1,p[i].b),add(i,n+2,1,-p[i].b);
	for ( int i=2;i<=n;i++ ) add(i,i-1,inf,0);
	for ( int T=n/2;T--; )
	{
		for ( int i=1;i<=n+2;i++ ) dis[i]=-(1LL<<60);
		std::queue<int> q;dis[n+1]=0;q.push(n+1);vis[n+1]=true;
		while ( !q.empty() )
		{
			int u=q.front();q.pop();vis[u]=false;
			for ( int i=h[u];i;i=e[i].nxt ) if ( e[i].f and dis[e[i].v]<dis[u]+e[i].c )
			{
				dis[e[i].v]=dis[u]+e[i].c;fr[e[i].v]=i;
				if ( !vis[e[i].v] ) q.push(e[i].v),vis[e[i].v]=true;
			}
		}
		ans+=dis[n+2];printf("%lld\n",ans);
		for ( int i=n+2;i!=n+1;i=e[fr[i]^1].v ) e[fr[i]].f--,e[fr[i]^1].f++;
	}
	return 0;
}
