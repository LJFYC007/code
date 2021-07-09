#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0;char ch;bool f=0;
	while(!isdigit(ch=getchar()))if(ch=='-')break;
	if(ch=='-')f=1;else x=ch-48;
	while(isdigit(ch=getchar()))x=x*10+ch-48;
	return f ? -x : x;
}
int n;
long long trans;
struct pig
{
	int a,b;
	bool operator < (const pig &y) const{return a==y.a ? b<y.b : a<y.a;}
};
vector<pig>p;
namespace subtask1
{
	inline void work()
	{
		long long trans=0;
		for(int i=1;i<=n/2;i++)
			trans+=p[n-i].b-p[i-1].b,printf("%lld\n",trans);
	}
}
namespace subtask2
{
	inline void work()
	{
		vector<pig>q;
		for(int k=1,flag=1;k<=n/2;k++)
		{
			if(flag)
			{
				q=p;
				int lim=q.size(),minn=q[0].b,ans=0,idnow=0,id1=-1,id2=-1;
				for(int i=1;i<lim;i++)
				{
					if(q[i].b-minn>ans)ans=q[i].b-minn,id1=idnow,id2=i;
					if(q[i].b<minn)minn=q[i].b,idnow=i;
				}
				if(ans)
				{
					trans+=ans,p.clear();
					for(int i=1;i<lim;i++)
						if(i!=id1 && i!=id2)
							p.push_back(q[i]);
				}
				else flag=0;
			}
			printf("%lld\n",trans);
		}
	}
}
namespace subtask3
{
	const int MAXN=1e5+5,MAXM=5e5+5;
	const long long INF=1e18;
	class hhh
	{
		public:
			inline void init(int nn,int ss,int tt)
			{
				s=ss,t=tt,n=nn,tot=1;
				for(register int i=1;i<=n;i++)head[i]=-1;
			}
			inline void add(int u,int v,long long val,long long cost)
			{
				a[++tot].start=u,a[tot].end=v,a[tot].val=val,a[tot].cost=cost,a[tot].next=head[u],head[u]=tot;
				a[++tot].start=v,a[tot].end=u,a[tot].val=0,a[tot].cost=-cost,a[tot].next=head[v],head[v]=tot;
			}
			inline void work(int TT)
			{
				priority_queue<pigpig>q;
				long long lst=-1;
				while(TT--)
				{
					long long fw=0;
					for(register int i=1;i<=n;i++)f[i]=0;
					fw=dfs(s,t,INF);
					if(!fw)TT++;
					max_flow+=fw;
					if(fw)
					{
						if(lst<-min_cost)lst=-min_cost;
						else break;
						printf("%lld\n",lst);
					}
					
					for(register int i=1;i<=n;i++)dist[i]=INF;
					dist[t]=0;
					pigpig now,kkk;
					now.x=t,now.d=dist[t];
					q.push(now);
					while(!q.empty())
					{
						now=q.top(),q.pop();
						if(now.d^dist[now.x])continue;
						for(register int i=head[now.x];i!=-1;i=a[i].next)
							if(a[i^1].val && dist[a[i^1].start]>now.d+a[i^1].cost)
								dist[a[i^1].start]=now.d+a[i^1].cost,kkk.x=a[i^1].start,kkk.d=dist[a[i^1].start],q.push(kkk);
					}
					if(dist[s]==INF)return;
					for(register int i=2;i<=tot;i++)a[i].cost+=dist[a[i].end]-dist[a[i].start];
					price+=dist[s];
				}
				if(TT>0)while(TT--)printf("%lld\n",lst);
			}
		private:
			int s,t,n,head[MAXN],tot;
			long long min_cost,max_flow,price,dist[MAXN];
			bool f[MAXN];
			struct pig
			{
				int start,end,next;
				long long val,cost;
			}a[2*MAXM];
			struct pigpig
			{
				int x;
				long long d;
				friend bool operator < (const pigpig &a,const pigpig &b)
				{
					return a.d>b.d;
				}
			};
			inline long long dfs(int x,int t,long long fff)
			{
				if(x==t){min_cost+=fff*price;return fff;}
				f[x]=1;
				register long long fw=fff;
				for(int i=head[x];i!=-1;i=a[i].next)
					if(!a[i].cost && a[i].val && !f[a[i].end])
					{
						register long long dd=dfs(a[i].end,t,min((long long)fw,a[i].val));
						fw-=dd,a[i].val-=dd,a[i^1].val+=dd;
						if(!fw)return fff;
					}
				return fff-fw;
			}
	}flow;
	inline void work()
	{
		int s=n+1,t=n+2;
		flow.init(n+2,s,t);
		for(int i=1;i<=n;i++)
			flow.add(s,i,1,p[i-1].b),flow.add(i,t,1,-p[i-1].b);
		for(int i=2;i<=n;i++)
			flow.add(i-1,i,n,0);
		flow.work(n/2);
	}
}
int main()
{
	freopen("sky.in","r",stdin);
	freopen("sky.out","w",stdout);
	n=read();
	for(int i=1,a,b;i<=n;i++)
		a=read(),b=read(),p.push_back((pig){a,b});
	sort(p.begin(),p.end());
	if(p[0].a==p[n-1].a){subtask1::work();return 0;}
	else if(n<=5e3){subtask3::work();return 0;}
	else {subtask2::work();return 0;}
	return 0;
}