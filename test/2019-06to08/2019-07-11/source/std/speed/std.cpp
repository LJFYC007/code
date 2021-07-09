# pragma GCC optimize ("Ofast")
//# pragma comment(linker, "/STACK:1024000000,1024000000")
#include<bits/stdc++.h>
#define lb(x) ((x)&(-x))
#define out(i,a,now) for(int i=a.be[now],to=a.v[i];~i;i=a.ne[i],to=a.v[i])
#define fo(i,a,b) for(i=(a);i<=(LL)(b);++i)
#define fd(i,a,b) for(i=(a);i>=(b);--i)
#define mid ((l+r)>>1)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?b:a)
#define mp(a,b) make_pair(a,b)
#define qk(x) memset(x,0,sizeof(x))
#define RG register
#define SF scanf
#define PF printf
#define FP freopen
#define FI first
#define SE second
#define cpy(a,b) memcpy(a,b,sizeof(a))//b to a
#define pi 3.1415926535897932384626433832
#ifdef Mogician
#endif
using namespace std;
typedef long long LL;
typedef double DB;
typedef pair<LL,LL> Pair;
template <class T> void cmax(T &a,T b){
    a=max(a,b);
}
template <class T> void cmin(T &a,T b){
    a=min(a,b);
}
const LL maxn=70100;
struct edge{
	LL x,y,l,r;
}a[maxn];
struct ST_table{
	LL a[maxn<<1][20];
	LL LG2[maxn<<1];
	void build(LL *b,LL n){
		LL i,j;
		LG2[1]=0;
		fo(i,2,n) LG2[i]=LG2[i>>1]+1;
		fo(i,1,n) a[i][0]=b[i];
		for(j=1;1<<j<=n;++j) fo(i,1,n-(1<<j)+1) a[i][j]=min(a[i][j-1],a[i+(1<<(j-1))][j-1]);
	}
	LL ask(LL l,LL r){
		return min(a[l][LG2[r-l+1]],a[r-(1<<LG2[r-l+1])+1][LG2[r-l+1]]);
	}
}st;
LL path[maxn][2],n,m,ans[maxn],f[maxn],ma,into[maxn],b[maxn<<1],clo,sz[maxn],outof[maxn];
vector<LL>qj[maxn];
struct data{
	LL *a,val;
	data(){
		a=NULL; val=0;
	}
	data(LL& x){
		a=&x; val=x;
	}
};
vector<data>temp[20];
inline LL dis(LL x,LL y){
	if (into[x]>into[y]) swap(x,y);
	return b[into[x]]+b[into[y]]-2*st.ask(into[x],outof[y]);
}
LL gf(LL x){
	while (f[x]) x=f[x];
	return x;
}
void merge(LL x,LL y,LL dp){
	x=gf(x); y=gf(y);
#define ins(x) (temp[dp].push_back(data(x)))
	if (sz[x]<sz[y]){
		ins(f[x]); f[x]=y; ins(sz[y]); cmax(sz[y],sz[x]+1);
	}
	else{
		ins(f[y]); f[y]=x; ins(sz[x]); cmax(sz[x],sz[y]+1);
	}
	if (f[x]==y) swap(x,y);
	ins(path[x][0]); ins(path[x][1]);
	LL TEMP[2]={path[x][0],path[x][1]},res=dis(path[x][0],path[x][1]);
	if (dis(path[y][0],path[y][1])>res){
		TEMP[0]=path[y][0]; TEMP[1]=path[y][1]; res=dis(path[y][0],path[y][1]);
	}
	LL i,j;
	fo(i,0,1) fo(j,0,1)
	if (dis(path[x][i],path[y][j])>res){
		TEMP[0]=path[x][i]; TEMP[1]=path[y][j]; res=dis(path[x][i],path[y][j]);
	}
	path[x][0]=TEMP[0]; path[x][1]=TEMP[1];
	cmax(ma,dis(path[x][0],path[x][1]));
}
void solve(LL l,LL r,LL dp){
//	if (l==r && r==3){
//		LL mogician=1;
//	}
	temp[dp].clear(); ins(ma);
	LL j;
	fo(j,0,qj[dp].size()-1)
		if (a[qj[dp][j]].l<=l && a[qj[dp][j]].r>=r) merge(a[qj[dp][j]].x,a[qj[dp][j]].y,dp);
	if (l==r){
		ans[l]=ma;
	}
	else
	{
	qj[dp+1].clear();
	fo(j,0,qj[dp].size()-1)
	if (a[qj[dp][j]].l<=mid && (a[qj[dp][j]].l>l || a[qj[dp][j]].r<r) && a[qj[dp][j]].r>=l){
		qj[dp+1].push_back(qj[dp][j]);
//		cerr<<a[qj[dp][j]].l<<' '<<a[qj[dp][j]].r<<endl;
	}
	solve(l,mid,dp+1);
	
	qj[dp+1].clear();
	fo(j,0,qj[dp].size()-1)
	if (a[qj[dp][j]].r>mid && (a[qj[dp][j]].l>l || a[qj[dp][j]].r<r) && a[qj[dp][j]].l<=r){
		qj[dp+1].push_back(qj[dp][j]);
//		cerr<<a[qj[dp][j]].l<<' '<<a[qj[dp][j]].r<<endl;
	}
	solve(mid+1,r,dp+1);
	}
/*	while (!temp[dp].empty()){
		*(temp[dp].back().a)=temp[dp].back().val;
		temp[dp].pop_back();
	}*/
	fd(j,temp[dp].size()-1,0) *(temp[dp][j].a)=temp[dp][j].val;
}
struct adj_list{
	LL be[maxn],ne[maxn<<1],v[maxn<<1],cnt;
	adj_list(){
		memset(be,-1,sizeof(be)); cnt=0;
	}
	void add(LL x,LL y){
		ne[cnt]=be[x];
		be[x]=cnt;
		v[cnt]=y;
		++cnt;
	}
}v;
void dfs(LL now,LL fa,LL dp){ // now, fa, dp -> dis?
	outof[now]=into[now]=++clo; b[clo]=dp; // clo时间戳?
	out(i,v,now) // 遍历吧
	if (to!=fa){
		dfs(to,now,dp+1); // dis + 1 
		outof[now]=++clo; // into, outo应该是初始时间戳和截止时间戳，要建树
        b[clo]=dp; // b应该就是dis数组了吧...
	}
}
int main(){
	SF("%lld%lld",&n,&m);
	LL i,x;
	fo(i,1,n-1){
		SF("%lld%lld%lld%lld",&a[i].x,&a[i].y,&a[i].l,&a[i].r);
		v.add(a[i].x,a[i].y); v.add(a[i].y,a[i].x); // 加边
		qj[1].push_back(i); // 应该是线段树的区间...
	}
	fo(i,1,n) path[i][0]=path[i][1]=i; // 不懂
	fo(i,1,n) sz[i]=1; // size = 1 ? 
	dfs(1,0,1); // ...
	st.build(b,clo);
	solve(1,n,1);
	fo(i,1,m){
		SF("%lld",&x);
		PF("%lld\n",ans[x]);
	}
	return 0;
}
