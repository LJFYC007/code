#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#define P puts("lala")
#define cp cerr<<"lala"<<endl
#define ln putchar('\n')
#define pb push_back
#define fi first
#define se second
#define mkp make_pair
using namespace std;
inline int read()
{
    char ch=getchar();int g=1,re=0;
    while(ch<'0'||ch>'9') {if(ch=='-')g=-1;ch=getchar();}
    while(ch<='9'&&ch>='0') re=(re<<1)+(re<<3)+(ch^48),ch=getchar();
    return re*g;
}
typedef long long ll;
typedef pair<int,int> pii;

const int N=700009;
int head[N],cnt=0;
struct node
{
	int to,next,w;
}e[N<<1];
inline void add(int x,int y,int w)
{
	e[++cnt]=(node){y,head[x],w}; head[x]=cnt;
	e[++cnt]=(node){x,head[y],w}; head[y]=cnt;
}

int n,q;

const int inf=0x3f3f3f3f;
struct ASK
{
	int id,x,k,ans;
}ask[N];
bool operator < (ASK a,ASK b)
{
	return a.k<b.k;
}


int dep[N],dis[N],dfn[N],efn[N],tot=0,is[N];
void dfs(int u,int fa,int dp,int ds)
{
	dep[u]=dp; dis[u]=ds; dfn[u]=++tot; is[tot]=u;
	for(int i=head[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u,dp+1,ds+e[i].w);
	}
	efn[u]=tot;
}

pii p[N]; // (ds,dp)
vector<int>Q[N<<2];
void hang(int o,int l,int r,int x,int y,int i)
{
	if(x<=l&&r<=y) {Q[o].pb(i); return ;}
	int mid=l+r>>1;
	if(x<=mid) hang(o<<1,l,mid,x,y,i);
	if(y>mid) hang(o<<1|1,mid+1,r,x,y,i);
}
pii tmp[N];
int sufmin[N];
void solve(int o,int l,int r)
{
	if(l==r)
	{
		for(int i=0,sz=Q[o].size();i<sz;++i)
		{
			int u=Q[o][i];
			if(p[l].fi>=ask[u].k) 
				ask[u].ans=min(ask[u].ans,p[l].se);
		}
		return ;
	}
	int mid=l+r>>1;
	solve(o<<1,l,mid); solve(o<<1|1,mid+1,r);
	int i=l,j=mid+1,k=l;
	while(i<=mid&&j<=r)
		if(p[i]<p[j]) tmp[k]=p[i],i++,k++;
		else tmp[k]=p[j],j++,k++;
	while(i<=mid) tmp[k]=p[i],i++,k++;
	while(j<=r) tmp[k]=p[j],j++,k++;
	for(i=l;i<=r;++i) p[i]=tmp[i];
	
	sufmin[r]=p[r].se;
	for(i=r-1;i>=l;--i) sufmin[i]=min(sufmin[i+1],p[i].se);
	
	int p1=l,p2=0,sz=Q[o].size();
	for(;p2<sz;++p2)
	{
		int u=Q[o][p2];
		while(p1<=r&&p[p1].fi<ask[u].k) p1++;
		if(p1<=r) ask[u].ans=min(ask[u].ans,sufmin[p1]);
		else break;
	}
}

int Ans[N];

void wj()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
}
int main()
{
	wj();
	int id=read();
	n=read();
	for(int i=1;i<n;++i)
	{
		int x=read(),y=read(),w=read();
		add(x,y,w);
	}
	dfs(1,0,0,0);
	q=read();
	for(int i=1;i<=q;++i)
	{
		ask[i].id=i;
		ask[i].x=read(); ask[i].k=read();
		ask[i].ans=inf;
		ask[i].k+=dis[ask[i].x];
	}
	sort(ask+1,ask+q+1);
	for(int i=1;i<=q;++i) 
		hang(1,1,n,dfn[ask[i].x],efn[ask[i].x],i);
	for(int i=1;i<=n;++i) p[i]=pii(dis[is[i]],dep[is[i]]);
	solve(1,1,n);
	for(int i=1;i<=q;++i) 
	{
		if(ask[i].ans==inf) Ans[ask[i].id]=-1;
		else Ans[ask[i].id]=ask[i].ans-dep[ask[i].x];
	}
	for(int i=1;i<=q;++i) printf("%d\n",Ans[i]);
	return 0;
}
