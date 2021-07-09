#include<bits/stdc++.h>
#define ll long long
#define lld long double
using namespace std;
template<typename tn> void read(tn &a){
	tn x=0,f=1; char c=' ';
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	a=x*f;
}
const int N = 1100;
struct edge{
	int v,nxt,f;
	ll w;
}e[2001000];
int head[N],n,a[N][N],in[N],fr[N],tot,Q,t,vis[N];
ll dis[N],h[N],ans[2000010],cost;
void add(int x,int y,int z){
	e[++tot]={y,head[x],1,z};
	head[x]=tot;
	e[++tot]={x,head[y],0,-z};
	head[y]=tot;
}
void spfa(){
	memset(dis,192,sizeof(dis));
	dis[0]=0;
	queue<int> q;q.push(0);
	while(!q.empty()){
		int u=q.front();q.pop();in[u]=0;
		for(int i=head[u];i;i=e[i].nxt)
			if(e[i].f&&dis[e[i].v]<dis[u]+e[i].w){
				dis[e[i].v]=dis[u]+e[i].w;
				if(!in[e[i].v]) q.push(e[i].v),in[e[i].v]=1;
			}
	}
	for(int i=0;i<=t;i++)
		h[i]=dis[i];
}
bool dij(){
	memset(dis,192,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(fr,0,sizeof(fr));
	dis[0]=0;
//	priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > q;
//	q.push(make_pair(0,0));
	for(int tim=0;tim<=t;tim++){
		int u=-1;
		for(int i=0;i<=t;i++)
			if(!vis[i]&&(u==-1||dis[i]>dis[u])) u=i;
		if(u==-1||dis[u]<-1e15) break;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt)
			if(e[i].f&&dis[e[i].v]<dis[u]-h[e[i].v]+h[u]+e[i].w){
				dis[e[i].v]=dis[u]+e[i].w-h[e[i].v]+h[u];
				fr[e[i].v]=i;
			}
	}
	return fr[t];
}
void update(){
/*	for(int i=0;i<=t;i++)
		cerr<<dis[i]<<' ';
	cerr<<'\n';
	for(int i=0;i<=t;i++)
		cerr<<h[i]<<' ';
	cerr<<'\n';
	cerr<<'\n';*/
	int x=t;cost+=h[t]-h[0]+dis[t];
	while(fr[x]){
		e[fr[x]].f--;
		e[fr[x]^1].f++;
		x=e[fr[x]^1].v;
	}
}
void Flow(){
	spfa();
	int tim=0;
	while(dij()){
		update();
		ans[++tim]=cost;
		for(int i=0;i<=t;i++)
			h[i]+=dis[i];
	}
	for(int i=1;i<=n*n;i++) ans[i]=max(ans[i-1],ans[i]);
}
int main(){
	freopen("allocation.in","r",stdin);
	freopen("allocation.out","w",stdout);
	int id;read(id);
	read(n);read(Q);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			read(a[i][j]);
	tot=1;t=2*n+1;
	for(int i=1;i<=n;i++)
		add(0,i,0),add(i+n,t,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			add(i,j+n,a[i][j]);
	Flow();
	while(Q--){
		int x;read(x);
		x=min(x,n*n);
		cout<<ans[x]<<".0\n";
	}
	return 0;
}

