#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
using namespace std;
const int maxn = 2e5+10;

int read(){
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+c-48;c=getchar();}
	return x*f;
}

int to[maxn<<1],net[maxn<<1],h[maxn],e=1;
inline void add(int x,int y){
	to[++e]=y;net[e]=h[x];h[x]=e;
}

int k,m,n,color[maxn];
vector<int> a[maxn];
int dep[maxn],fa[maxn],son[maxn],siz[maxn];
void dfs(int x){
	dep[x]=dep[fa[x]]+1;siz[x]=1;
	for(register int i=h[x];i;i=net[i]){
		int y=to[i];
		if(y==fa[x])continue;
		fa[y]=x;
		dfs(y);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]])son[x]=y;
	}
	return;
}

int top[maxn];
void dfs(int x,int p){
	top[x]=p;
	if(!son[x])return;
	dfs(son[x],p);
	for(register int i=h[x];i;i=net[i]){
		int y=to[i];
		if(y==fa[x] || y==son[x])continue;
		dfs(y,y);
	}
	return;
}

int LCA(int x,int y){
//	cout<<x<<" "<<y<<endl;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
//	cout<<x<<" "<<y<<" "<<top[x]<<" "<<top[y]<<endl;
	if(dep[x]<dep[y])return x;
	return y;
}

vector<int> hlca[maxn],To[maxn];
int toplca[maxn],check[maxn];
int solve(int root,int x,int colo){
	//cout<<"::"<<x<<" "<<color[x]<<" "<<toplca[color[x]]<<endl;
	//if(check[colo])return true;
	int flag=0;
	if(color[x]==colo)flag=1;
	for(register int i=h[x];i;i=net[i]){
		int y=to[i];
		if(y==fa[x])continue;
		if(solve(root,y,colo))flag=1;
	}
	if(flag){
		//if(dep[toplca[color[x]]]<dep[root])check[colo]=1;
		To[colo].push_back(color[x]);
		return true;
	}
	return false;
}

int ans=10000000;
queue<int> q;
vector<int> w;
int vis[maxn];
inline void work(int x){
	w.clear();
	q.push(x);vis[x]=1;w.push_back(x);
	int anss=0;
	while(!q.empty()){
		int x=q.front();q.pop();anss++;
		int len=To[x].size();
		for(register int i=0;i<len;i++){
			int y=To[x][i];
			if(vis[y])continue;
			vis[y]=1;
			w.push_back(y);
			q.push(y);
		}
	}
	ans=min(ans,anss-1);
	for(register int i=0;i<w.size();i++)vis[w[i]]=0;
	return;
}

int main(){
	n=read();k=read();
	for(register int i=1;i<n;i++){
		int x=read(),y=read();
		add(x,y);add(y,x);
	}
	for(register int i=1;i<=n;i++){color[i]=read();a[color[i]].push_back(i);}
	for(register int i=1;i<=k;i++){
		if(a[i].size()==1){puts("0");return 0;}
	}
	dfs(1);
	dfs(1,1);
	for(register int i=1;i<=k;i++){
		int len=a[i].size(),lca=LCA(a[i][0],a[i][1]);
		for(register int j=2;j<len;j++){
			lca=LCA(lca,a[i][j]);
		}
		hlca[lca].push_back(i);toplca[i]=lca;
		//cout<<i<<" "<<lca<<" "<<a[i][0]<<" "<<a[i][1]<<endl;
		//cout<<i<<" "<<lca<<endl;
	}
	for(register int i=1;i<=n;i++){
		int len=hlca[i].size();
		for(register int j=0;j<len;j++){
			solve(i,i,hlca[i][j]);
			sort(To[hlca[i][j]].begin(),To[hlca[i][j]].end());
			vector<int>::iterator iter = unique(To[hlca[i][j]].begin(),To[hlca[i][j]].end());
			To[hlca[i][j]].erase(iter,To[hlca[i][j]].end());
			//cout<<" "<<" "<<hlca[i][j]<<" "<<check[hlca[i][j]]<<endl;
			//for(register int u=0;u<To[hlca[i][j]].size();u++)cout<<To[hlca[i][j]][u]<<" ";puts("");
		}
	}
	for(register int i=1;i<=k;i++)work(i);
	printf("%d\n",ans);
	return 0;
}
