#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define IL inline
#define RG register
#define gi geti<int>()
#define gl geti<ll>()
#define gc getchar()
#define File(a) freopen(a".in","r",stdin);freopen(a".out","w",stdout)
template<typename T>IL bool chkmax(T &x,const T &y){return x<y?x=y,1:0;}
template<typename T>IL bool chkmin(T &x,const T &y){return x>y?x=y,1:0;}
template<typename T>
IL T geti()
{
	RG T xi=0;
	RG char ch=gc;
	bool f=0;
	while(!isdigit(ch))ch=='-'?f=1:f,ch=gc;
	while(isdigit(ch))xi=xi*10+ch-48,ch=gc;
	return f?-xi:xi;
}
template<typename T>
IL void pi(T k,char ch=0)
{
	if(k<0)k=-k,putchar('-');
	if(k>=10)pi(k/10);
	putchar(k%10+'0');
	if(ch)putchar(ch);
}
const int N=3e5+7,P=1e9+7;
class graph{
private:
	struct edge{
		int v;
		edge *next;
	}e[N*2],*head[N];
	int cnt;
public:
	graph(){cnt=-1;}
	void add(int u,int v){e[++cnt]=((edge){v,head[u]}),head[u]=e+cnt;}
	class iterator{
	public:
		friend class graph;
		iterator(edge* p=NULL):__ptr(p){}
		iterator (const iterator &p):__ptr(p.__ptr){}
		iterator& operator ++()
		{
			__ptr=__ptr->next;
			return *this;
		}
		iterator operator ++(int)
		{
			iterator __tmp=(*this);
			++(*this);
			return __tmp;
		}
		edge* operator ->(){return __ptr;}
		edge& operator * (){return *__ptr;}
		bool operator ==(const iterator &p){return __ptr==p.__ptr;}
		bool operator != (const iterator &p){return __ptr!=p.__ptr;}
	private:
		edge *__ptr;
	};
	iterator begin(int u){return head[u];}
	edge * end(){return NULL;}
}G;
int n,q,w[N];
inline void input()
{
	n=gi,q=gi;
	for(int i=1;i<n;++i)
	{
		int u=gi,v=gi;
		G.add(u,v),G.add(v,u);
	}
	for(int i=1;i<=n;++i)w[i]=gi;
}
namespace STTable{
	int dep[N],Dfn,f[20][N*2],first[N];
	#define lg2(x) (31-__builtin_clz(x))
	inline void dfs(int x,int p=0)
	{
		dep[x]=dep[p]+1,f[0][first[x]=++Dfn]=dep[x];
		for(auto i=G.begin(x);i!=G.end();++i)
			if(i->v^p)
				dfs(i->v,x),f[0][++Dfn]=dep[x];
	}
	inline void init()
	{
		dfs(1);
		int len=lg2(Dfn);
		for(RG int i=1;i<=len;++i)
			for(RG int j=1;j+(1<<i)-1<=Dfn;++j)
				f[i][j]=min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
	}
	inline int STQuery(int l,int r)
	{
		if(l>r)swap(l,r);
		int k=lg2(r-l+1);
		return min(f[k][l],f[k][r-(1<<k)+1]);
	}
}
using namespace STTable;
#define DisQuery(u,v) (dep[u]+dep[v]-(STQuery(first[u],first[v])<<1))
inline int add(int x){return x>P?x-P:x;}
inline int sub(int x){return x<0?x+P:x;}
inline void add(int &x,int y){x+=y;if(x>=P)x-=P;}
inline void sub(int &x,int y){x-=y;if(x<0)x+=P;}
namespace Dynamic_Tree_Division{
	int siz[N],hson[N],total,Hrt,par[N];
	bool vis[N];
	int dis1[N],dis2[N],dis3[N],dis4[N],sumv[N];
	inline void grt(int x,int p=0){
		siz[x]=1,hson[x]=0;
		for(auto i=G.begin(x);i!=G.end();++i)
			if(i->v!=p&&!vis[i->v])
				grt(i->v,x),siz[x]+=siz[i->v],chkmax(hson[x],siz[i->v]);
		chkmax(hson[x],total-siz[x]);
		if(hson[x]<hson[Hrt])Hrt=x;
	}
	inline void presolve(int x,int p=0)
	{
		vis[x]=1,par[x]=p;
		for(auto i=G.begin(x);i!=G.end();++i)
			if(!vis[i->v])
			{
				total=siz[i->v],Hrt=0,grt(i->v);	
				presolve(Hrt,x);
			}
	}
	inline void Modify(int x,int val)
	{
		if(val<0)val+=P;
		add(sumv[x],val);
		for(int i=x;par[i];i=par[i])
		{
			ll dis=DisQuery(x,par[i]),sqrdis=dis*dis%P;
			dis=dis*val%P,sqrdis=sqrdis*val%P;
			add(dis1[par[i]],dis);
			add(dis2[i],dis);
			add(dis3[par[i]],sqrdis);
			add(dis4[i],sqrdis);
			add(sumv[par[i]],val);
		}
	}
	inline int Query(int x)	
	{
		RG int ret=add(dis1[x]+dis3[x]);
		for(int i=x;par[i];i=par[i])
		{
			ll dis=DisQuery(x,par[i]),sqrdis=dis*dis%P;
			add(ret,dis*sub(sumv[par[i]]-sumv[i])%P);
			add(ret,sub(dis1[par[i]]-dis2[i]));
			add(ret,add((dis<<1)*sub(dis1[par[i]]-dis2[i])%P+sqrdis*sub(sumv[par[i]]-sumv[i])%P));
			add(ret,sub(dis3[par[i]]-dis4[i]));
		}
		return (ret*500000004ll)%P;
	}
	inline void init()
	{
		total=hson[Hrt=0]=n;
		grt(1),presolve(Hrt);
		for(int i=1;i<=n;++i)Modify(i,w[i]);
	}
}
using Dynamic_Tree_Division::Modify;
using Dynamic_Tree_Division::Query;
inline void solve()
{
	STTable::init();
	Dynamic_Tree_Division::init();
	while(q--)
	{
		int opt=gi,x=gi;
		if(opt==1)
		{
			int y=gi;
			Modify(x,y-w[x]);
			w[x]=y;
		}
		else pi(Query(x),'\n');
	}
}
signed main(void)
{
	File("formula");
	input();
	solve();
	return 0;
}
