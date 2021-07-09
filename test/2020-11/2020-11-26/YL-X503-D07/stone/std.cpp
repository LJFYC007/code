#include <bits/stdc++.h>
#define ll long long
#define Mid ((L+R)>>1)
using namespace std;
typedef pair<int,int> pii;
inline int read(){
	char c;int x=0;int b=1;do{c=getchar();if(c==45)b=-1;}while(c>57||c<48);
	do x=x*10+c-48,c=getchar();while(c<=57&&c>=48);x*=b;return x;
}
const int maxn=300010;
struct edge{
	int next,to;
}a[maxn*2],e[maxn*2];
int head[maxn],head2[maxn],len,len2;
void add(int x,int y){
	a[++len]={head[x],y};
	head[x]=len;
}
void add2(int x,int y){
	//cout<<" "<<x<<' '<<y<<endl;
	e[++len2]={head2[x],y};
	head2[x]=len2;
	e[++len2]={head2[y],x};
	head2[y]=len2;
}
int i,j,k,n,m,F[maxn][21],size[maxn],dfn[maxn],deep[maxn],D,mmax[maxn],Top[maxn],mt[maxn];
int U[maxn*2][21],DEEP[maxn*2][21],S[maxn],LL,Log[maxn*4];
int ROOT[maxn];
namespace ST{
	struct line{
		int k,b;
		int calc(int x){return k*x+b;}
	};
	struct LC{
		int son[2];
		line l;
	}tree[maxn*10];int cnt;
	#define ls(root) tree[root].son[0]
	#define rs(root) tree[root].son[1]
	void INSERT(int &root,int L,int R,int l,int r,line g){
		if(!root)root=++cnt,tree[root].l={1,100000000};
		//cout<<"INSERT "<<root<<' '<<L<<' '<<R<<' '<<l<<' '<<r<<endl;
		if(L==R){
			if(g.calc(Mid)<tree[root].l.calc(Mid))
				swap(tree[root].l,g);
			return;
		}
		if(L==l && R==r){
			if(g.calc(Mid)<tree[root].l.calc(Mid))
				swap(tree[root].l,g);
			if(tree[root].l.k>g.k)INSERT(rs(root),Mid+1,R,Mid+1,r,g);
			else if(tree[root].l.k<g.k)INSERT(ls(root),L,Mid,l,Mid,g);
		}else{
			if(r<=Mid)INSERT(ls(root),L,Mid,l,r,g);
			else if(l>Mid)INSERT(rs(root),Mid+1,R,l,r,g);
			else INSERT(ls(root),L,Mid,l,Mid,g),INSERT(rs(root),Mid+1,R,Mid+1,r,g);
		}
	}
	int FIND(int root,int L,int R,int x){
		if(!root)return 1e8;
		int ans;
		if(x<=Mid)ans=FIND(ls(root),L,Mid,x);
		else ans=FIND(rs(root),Mid+1,R,x);
		return min(ans,tree[root].l.calc(x));
	}
}using namespace ST;
void dfs(int now,int fa){
	size[now]=1;
	F[now][0]=fa;dfn[now]=++D;
	deep[now]=deep[fa]+1;
	for(int i=head[now];i;i=a[i].next){
		int u=a[i].to;
		if(u==fa)continue;
		dfs(u,now);
		size[now]+=size[u];
		if(size[mmax[now]]<size[u])
			mmax[now]=u;
	}
}
void DFS(int now,int fa,int top=1){
	Top[now]=top;mt[Top[now]]=max(mt[Top[now]],deep[now]);
	U[++LL][0]=now;DEEP[LL][0]=deep[now];S[now]=LL;
	if(mmax[now]){
		DFS(mmax[now],now,top);
		U[++LL][0]=now;
		DEEP[LL][0]=deep[now];
	}
	for(int i=head[now];i;i=a[i].next){
		int u=a[i].to;
		if(u==fa || u==mmax[now])continue;
		DFS(u,now,u);
		U[++LL][0]=now;
		DEEP[LL][0]=deep[now];
	}
}
void LCA(){
	for(int j=1;j<=19;j++)
		for(int i=1;i<=n;i++)
			F[i][j]=F[F[i][j-1]][j-1];
	for(int j=1;j<=19;j++)
		for(int i=1;i<=LL-(1<<j-1);i++){
			if(DEEP[i][j-1]<DEEP[i+(1<<j-1)][j-1])U[i][j]=U[i][j-1];
			else U[i][j]=U[i+(1<<j-1)][j-1];
			DEEP[i][j]=min(DEEP[i][j-1],DEEP[i+(1<<j-1)][j-1]);
		}
}
bool cmp(int a,int b){
	return dfn[a]<dfn[b];
}
/*
int lca(int x,int y){
	if(deep[x]<deep[y])swap(x,y);
	for(int i=20;i>=0;i--)
		if(deep[F[x][i]]>=deep[y])x=F[x][i];
	if(x==y)return x;
	for(int i=20;i>=0;i--)
		if(F[x][i]!=F[y][i])x=F[x][i],y=F[y][i];
	return F[x][0];
}
*/
int lca(int x,int y){
	int X=S[x],Y=S[y];
	if(X>Y)swap(X,Y);
	int A=DEEP[X][Log[Y-X+1]],B=DEEP[Y-(1<<Log[Y-X+1])+1][Log[Y-X+1]];
	if(A<B)return U[X][Log[Y-X+1]];
	else return U[Y-(1<<Log[Y-X+1])+1][Log[Y-X+1]];
}
int dist(int x,int y){
	if(!x || !y)return 0;
	int z=lca(x,y);
	//cout<<"---"<<x<<' '<<y<<' '<<z<<endl;
	return deep[x]+deep[y]-2*deep[z];
}
int Q[maxn],top,is[maxn],id,dis[maxn],Max1,Max2,root1,root2,h[maxn];
void dfs2(int now,int fa){	
	dis[now]=dis[fa]+dist(now,fa);
	if(is[now]==id && dis[now]>Max1){Max1=dis[now];Max2=now;}
	for(int i=head2[now];i;i=e[i].next){
		int u=e[i].to;
		if(u==fa)continue;
		dfs2(u,now);
	}
}
int dp[maxn];
void dfs3(int now,int fa){
	for(int i=head[now];i;i=a[i].next){
		int u=a[i].to;
		if(u==fa)continue;
		dp[u]=min(dp[now]+1,dp[u]);
		dfs3(u,now);
	}
}
void insert(int x,int y,int B,int K){
	if(deep[x]>deep[y])return;
	while(Top[x]!=Top[y]){
		INSERT(ROOT[Top[y]],deep[Top[y]],mt[Top[y]],deep[Top[y]],deep[y],(line){K,B});
		y=F[Top[y]][0];
	}if(deep[x]<deep[y])swap(x,y);
	INSERT(ROOT[Top[x]],deep[Top[y]],mt[Top[y]],deep[y],deep[x],(line){K,B});
}
void cl(int now,int fa){
	for(int i=head2[now];i;i=e[i].next){
		int u=e[i].to;
		if(u==fa)continue;
		cl(u,now);
	}head2[now]=0;
}
int run(int x,int l){
	for(int i=19;i>=0;i--)
		if(l>=(1<<i))l-=(1<<i),x=F[x][i];
	return x;
}
int main() {
	freopen("stone.in","r",stdin);
	freopen("stone1.out","w",stdout);
	Log[0]=-1;
	for(i=1;i<maxn*8;i++)Log[i]=Log[i/2]+1;
	cin>>n;
	for(i=2;i<=n;i++){
		int f=read();
		add(f,i);add(i,f);
	}dfs(1,0);DFS(1,0);LCA();
	cin>>m;
	memset(dp,0x3f,sizeof(dp));
	for(i=1;i<=m;i++){
		k=read();++id;
		for(j=1;j<=k;j++)is[h[j]=read()]=id;
		sort(h+1,h+1+k,cmp);
		Q[top=1]=1;
		for(j=1;j<=k;j++){
			if(h[j]==1)continue;
			//cout<<"j="<<j<<' '<<h[j]<<endl;
			while(top>1 && deep[lca(h[j],Q[top])]<=deep[Q[top-1]]){
				add2(Q[top-1],Q[top]);
				top--;
			}
			if(lca(h[j],Q[top])!=Q[top]){
				add2(lca(h[j],Q[top]),Q[top]);
				Q[top]=lca(h[j],Q[top]);
			}if(h[j]!=Q[top])Q[++top]=h[j];
		}while(top!=1)add2(Q[top-1],Q[top]),--top;
		dis[0]=0;
		Max1=Max2=-1;
		dfs2(1,0);
		root1=Max2;
		Max1=Max2=-1;
		dis[0]=0;
		//cout<<root1<<' '<<root2<<endl;
		dfs2(root1,0);
		root2=Max2;
		//cout<<root1<<' '<<root2<<' '<<Max1<<endl;
		int len=dist(root1,root2),z=lca(root1,root2),S=max(dist(1,root1),dist(1,root2));
		dp[1]=min(dp[1],S);
		dp[root1]=min(dp[root1],len);
		dp[root2]=min(dp[root2],len);
		if(deep[root1]<deep[root2])swap(root1,root2);
		int D=run(root1,(len+1)/2-1);
		insert(D,root1,len-deep[root1],1);
		insert(z,F[D][0],dist(root1,z)+deep[z],-1);
		insert(z,root2,len-deep[root2],1);
		insert(1,z,S+1,-1);
		cl(1,0);len2=0;
	}
	//cout<<"DP"<<dp[1]<<endl;
	for(i=1;i<=n;i++){
		//cout<<"get "<<i<<endl;
		dp[i]=min(dp[i],FIND(ROOT[Top[i]],deep[Top[i]],mt[Top[i]],deep[i]));
	}
	dfs3(1,0);
	for(i=1;i<=n;i++)printf("%d\n",dp[i]);
	cerr << 1.0*clock()/CLOCKS_PER_SEC << endl;
	return 0;
}
