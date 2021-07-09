/*
@Date    : 2020-10-29 10:35:25
@Author  : Adscn (adscn@qq.com)
@Link    : https://www.cnblogs.com/LLCSBlog
*/
#include<bits/stdc++.h>
using namespace std;
#define int ll
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
const int N=4e5+7,inf=1e18;
#define lg2(x) (31-__builtin_clz(x))
ll w[N];
struct triple{
	ll ans;
	int x,y;
	bool operator > (const triple&b)const{return ans>b.ans;}
	bool operator < (const triple&b)const{return ans<b.ans;}
	bool operator == (const triple&b)const{return ans==b.ans&&x==b.x&&y==b.y;}
	triple(){}
	triple(int a,int b,int c):ans(a),x(b),y(c){}
};
typedef priority_queue<triple,vector<triple>,greater<triple> > _heap;
class _multiset{
	public:
	_heap now,del;
	int siz;
	inline void insert(triple val){now.push(val);++siz;}
	inline void erase(triple val){del.push(val);--siz;}
	inline void flush(){while(del.size()&&now.top()==del.top())now.pop(),del.pop();}
	inline bool empty(){return siz==0;}
	inline int size(){return siz;}
	inline triple top(){return flush(),siz?now.top():triple{inf,0,0};}
	_multiset(){siz=0;}
};
typedef _multiset Ms;
typedef pair<ll,int> pii;
struct piii{
	pii x,y;
	piii rev(){return piii(y,x);} 
	bool operator > (const piii&b)const{return make_pair(x,y)>make_pair(b.x,b.y);}
	bool operator == (const piii&b)const{return x==b.x&&y==b.y;}
	piii(){}
	piii(pii _x,pii _y):x(_x),y(_y){}
};
typedef priority_queue<piii,vector<piii>,greater<piii> > _heapii;
class _multisetii{//0 WHITE,BLACK, 1 BLACK,WHITE
	public:
	_heapii now[2],del[2];
	int siz;
	int id;
	inline void insert(piii val){now[0].push(val),now[1].push(val.rev());++siz;}
	inline void erase(piii val){del[0].push(val),del[1].push(val.rev());--siz;}
	inline void flush(){
		while(del[0].size()&&now[0].top()==del[0].top())now[0].pop(),del[0].pop();
		while(del[1].size()&&now[1].top()==del[1].top())now[1].pop(),del[1].pop();
	}
	inline bool empty(){return siz==0;}
	inline int size(){return siz;}
	inline piii top(int i){return flush(),siz?now[i].top():piii(pii(inf,0),pii(inf,0));}
	inline piii top(){return piii(top(0).x,top(1).x);}
	inline triple entire(){
		if(siz<2)return triple(inf,0,0);
		piii x=top(0);erase(x);
		piii y=top(1);insert(x);
		triple x1=triple(x.x.first+y.x.first-2*w[id],x.x.second,y.x.second);
		x=top(1);erase(x);
		y=top(0);insert(x);
		triple x2=triple(x.x.first+y.x.first-2*w[id],x.x.second,y.x.second);
		return min(x1,x2);
	}
	_multisetii(){siz=0;}
};
typedef _multisetii Msii;
int lg2[N*2];
Msii diswb[N],subtr[N];
Ms ans;
struct edge{
	int v,nxt,w;
}e[N<<1];
int head[N],cnt;
inline void init(){memset(head,cnt=-1,sizeof head);}
inline void add(int u,int v,int w){e[++cnt]=(edge){v,head[u],w},head[u]=cnt;}
#define For_tree(x) for(int i=head[x],v=e[i].v;~i;i=e[i].nxt,v=e[i].v)
int first[N],dis[N],vis[N],dfn,f[23][N<<1],ver[N<<1],depth_ver[N<<1];
int siz[N],hson[N],Hrt,par[N],total;
int stk[N],top,color[N];
inline void dfs(int x,int dep=0,int _dis=0)
{
	vis[x]=1,first[x]=++dfn,ver[dfn]=x,depth_ver[dfn]=dep;
	dis[x]=_dis;
    for(int i=head[x],v=e[i].v;~i;i=e[i].nxt,v=e[i].v)
		if(!vis[v])
			dfs(v,dep+1,_dis+e[i].w),ver[++dfn]=x,depth_ver[dfn]=dep;
}
inline void STinit(int k)
{
	int len=lg2(k);
	for(int i=1;i<=k;i++)f[0][i]=i;
	for(int i=1;i<=len;i++)
		for(int j=1;j+(1<<i)-1<=k;j++)
			f[i][j]=(depth_ver[f[i-1][j]]<=depth_ver[f[i-1][j+(1<<(i-1))]])?f[i-1][j]:f[i-1][j+(1<<(i-1))];
}
inline int STQuery(int l,int r)
{
	if(l>r)swap(l,r);
	int k=lg2(r-l+1);
	return depth_ver[f[k][l]]<=depth_ver[f[k][r-(1<<k)+1]]?f[k][l]:f[k][r-(1<<k)+1];
}
inline int LCAQuery(int u,int v){return ver[STQuery(first[u],first[v])];}
inline int Dis(int u,int v){return w[u]+w[v]+dis[u]+dis[v]-2*dis[LCAQuery(u,v)];}
inline void grt(int x,int fa=0)
{
	siz[x]=1,hson[x]=0,stk[++top]=x;
	For_tree(x)
		if(!vis[v]&&v^fa)
			grt(v,x),siz[x]+=siz[v],chkmax(hson[x],siz[v]);
	chkmax(hson[x],total-siz[x]);
	if(hson[x]<hson[Hrt])Hrt=x;
}
inline void presolve(int x,int fa=0)
{
	vis[x]=1,par[x]=fa;
	subtr[x].insert(piii(pii(2*w[x],x),pii(inf,x)));
	if(fa)for(int i=1;i<=top;++i)diswb[x].insert(piii(pii(Dis(stk[i],fa),stk[i]),pii(inf,stk[i])));
	For_tree(x)
		if(!vis[v]){
			top=Hrt=0,total=siz[v],grt(v,x);
			int Base=Hrt;
//			cout<<"Hrt"<<Hrt<<endl;
			presolve(Hrt,x);
//			cout<<x<<" "<<Base<<" "<<diswb[Base].top().x.first<<" "<<diswb[Base].top().y.first<<endl;
			subtr[x].insert(diswb[Base].top());
		}
	ans.insert(subtr[x].entire());
}
inline void modify(int x,int col)
{
	triple ori=subtr[x].entire();
	if(col)subtr[x].erase(piii(pii(2*w[x],x),pii(inf,x))),subtr[x].insert(piii(pii(inf,x),pii(2*w[x],x)));
	else   subtr[x].erase(piii(pii(inf,x),pii(2*w[x],x))),subtr[x].insert(piii(pii(2*w[x],x),pii(inf,x)));
	triple nw=subtr[x].entire();
	if(!(ori==nw))ans.erase(ori),ans.insert(nw);
	for(int p=par[x],u=x;p;p=par[u=p])
	{
		piii _ori=diswb[u].top();
		if(col)diswb[u].erase(piii(pii(Dis(p,x),x),pii(inf,x))),diswb[u].insert(piii(pii(inf,x),pii(Dis(p,x),x)));
		else   diswb[u].erase(piii(pii(inf,x),pii(Dis(p,x),x))),diswb[u].insert(piii(pii(Dis(p,x),x),pii(inf,x)));
		piii _nw=diswb[u].top();
		if(_ori==_nw)continue;	
		ori=subtr[p].entire();
		if(!(_ori==piii(pii(inf,0),pii(inf,0))))subtr[p].erase(_ori);
		if(!(_nw==piii(pii(inf,0),pii(inf,0)))) subtr[p].insert(_nw);
		nw=subtr[p].entire();
		if(!(ori==nw))ans.erase(ori),ans.insert(nw);
	}
}
signed main(void)
{
	#ifndef ONLINE_JUDGE
	File("justice");
	#endif
	int n=gi;
	init();
	for(int i=1;i<=n;++i)w[i]=gi,subtr[i].id=i;
	for(int i=1,u,v,w;i<n;++i)u=gi,v=gi,w=gi,add(u,v,w),add(v,u,w);
	dfs(1),STinit(dfn);
	memset(vis,0,sizeof vis);
	hson[Hrt=0]=total=n;
	grt(1);
//	cout<<"Hrt"<<Hrt<<endl;
	presolve(Hrt);
	modify(1,color[1]^=1);
	ll res=0;
	for(int i=1;i<n;++i){
		triple t=ans.top();
//		cout<<t.ans<<" "<<t.x<<" "<<t.y<<endl;
		res+=t.ans;
		if(color[t.x]==1)swap(t.x,t.y);
//		cout<<"Modify"<<t.x<<endl;
		modify(t.x,color[t.x]^=1);
	}
	pi(res);
	return 0;
}
