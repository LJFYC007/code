#include<cstdio>
#include<vector>
#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
#include<cstdlib>
using namespace std;
const long long INF=1e18;
struct Edge{
	int from,to;
	long long cap,flow,cost;
	Edge(int u,int v,long long c,long long f,long long w):from(u),to(v),cap(c),flow(f),cost(w){}
};
int n,s,t,aaa[100002],bbb[100002],dd[100002];
vector<Edge>edges;
vector<int>g[100005];
int p[100005];
long long d[100005],a[100005];
bool fl[100005];
bool cmp(int aa,int bb){
	return (aaa[aa]<aaa[bb] || aaa[aa]==aaa[bb] && bbb[aa]<bbb[bb]);
}
void add(int from,int to,long long cap,long long cost){
	edges.push_back(Edge(from,to,cap,0,cost));
	edges.push_back(Edge(to,from,0,0,-cost));
	g[from].push_back(edges.size()-2);
	g[to].push_back(edges.size()-1); 
}
void spfa(int s,int t,long long& flow,long long& cost){
	for (int i=1;i<=t;i++){d[i]=-INF;fl[i]=0;}
	d[s]=0;fl[s]=1;a[s]=INF;
	queue<int>q;q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		fl[u]=0;
		for (int i=g[u].size()-1;i>=0;i--)
		{
			Edge e=edges[g[u][i]];
			if (e.cap>e.flow && d[u]+e.cost>d[e.to])
			{
				d[e.to]=d[u]+e.cost;
				p[e.to]=g[u][i];
				a[e.to]=min(a[u],e.cap-e.flow);
				if (!fl[e.to]){q.push(e.to);fl[e.to]=1;}
			}
		}
	}
	flow+=a[t];cost+=d[t]*a[t];
	for (int u=t;u!=s;u=edges[p[u]].from)
	{
		edges[p[u]].flow+=a[t];edges[p[u]^1].flow-=a[t];
	}
}
void mcmf(int s,int t){
	long long flow=0,cost=0,last=0;
	for (int i=1;i<=n/2;i++)
	{
	    last=cost;
		spfa(s,t,flow,cost);
		printf("%lld\n",cost);
		if (last==cost)
		{
			for (int j=i+1;j<=n/2;j++)printf("%lld\n",cost);
			break;
		}
	}
}
bool pd(){
	for (int i=2;i<=n;i++)if (aaa[i]!=aaa[i-1])return false;
	return true;
}
int main()
{
	freopen("sky.in","r",stdin);
	freopen("sky.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;i++){scanf("%d%d",&aaa[i],&bbb[i]);dd[i]=i;}
	if (pd())
	{
		sort(dd+1,dd+n+1,cmp);
		int l=1,r=n;long long sum=0;
		for (int i=1;i<=n/2;i++)
		{
			sum+=bbb[dd[r]]-bbb[dd[l]];
			l++;r--;
			printf("%lld\n",sum);
		}
		return 0;
	}
	sort(dd+1,dd+n+1,cmp);s=n+1;t=n+2;
	for (int i=1;i<=n;i++)
	{
		add(s,i,1,bbb[dd[i]]);add(i,t,1,-bbb[dd[i]]);
	}
	for (int i=2;i<=n;i++)add(i,i-1,INF,0);
	mcmf(s,t);
	return 0;
}
