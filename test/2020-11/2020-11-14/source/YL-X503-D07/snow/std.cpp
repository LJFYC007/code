#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MN 200005
int read(){
	int a=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while('0'<=c&&c<='9'){
		a=a*10+c-48;
		c=getchar();
	}
	return a;
}
#define pii pair<int,int>
#define x first
#define y second
#define mp make_pair
int n,q,w[MN],fw[MN];
pii mx[MN],tmpmx[MN];
int sum[MN],tmpsum[MN],ans[MN],tmpans[MN],ANS;
vector<pii >edge[MN];
void maintain(int x){
	int v=mx[x].x;
	if(v>sum[x]-v){
		ans[x]=(v*2-sum[x])*w[x];
		ANS+=ans[x];
	}
	else if(v%2!=(sum[x]-v)%2){
		ans[x]=w[x];
		ANS+=ans[x];
	}
}
void INS(int x,int y,int z){
	sum[x]+=z;
	mx[x]=max(mx[x],mp(z,y));
}
int fa[MN],dep[MN];
void dfs(int x){
	for(int i=0;i<edge[x].size();++i){
		int v=edge[x][i].x;
		if(fa[x]==v)continue;
		fw[v]=edge[x][i].y;
		fa[v]=x;dep[v]=dep[x]+1;
		dfs(v);
	}
}
vector<int>id;
void upd(int x,int y,int d){
	id.push_back(x);
	int v=(x==fa[y])?fw[y]:fw[x];	
//	if(x==fa[y])fw[y]+=d;
//	else fw[x]+=d;
	ANS-=ans[x];ans[x]=0;
	sum[x]+=d;
	mx[x]=max(mx[x],mp(v,y));	
	maintain(x);
//	cerr<<x<<": "<<ans[x]<<endl;
}
void CLEAR(){
	for(int i=0;i<id.size();++i){
		sum[id[i]]=tmpsum[id[i]];
		mx[id[i]]=tmpmx[id[i]];
		ans[id[i]]=tmpans[id[i]];
	}
}
signed main(){
	freopen("snow.in","r",stdin);
	freopen("snow1.out","w",stdout);
	n=read();q=read();
	for(int i=1;i<=n;++i)w[i]=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read(),z=read();
		edge[x].push_back(mp(y,z));
		edge[y].push_back(mp(x,z));
		INS(x,y,z);
		INS(y,x,z);
	}
	dep[1]=1;dfs(1);
//	return 0;
	for(int i=1;i<=n;++i){
		maintain(i);
		tmpsum[i]=sum[i];
		tmpmx[i]=mx[i];
		tmpans[i]=ans[i];
	}
	printf("%lld\n",ANS);
	int tmp=ANS,cas=0;
	while(q--){
		int u=read(),v=read(),d=read();
		while(u!=v){
			if(dep[u]<dep[v])swap(u,v);
			fw[u]+=d;
			upd(u,fa[u],d);
			upd(fa[u],u,d);
			u=fa[u];
		}
		printf("%lld\n",ANS);
	//	CLEAR();
	//	id.clear();
	//	ANS=tmp;
	}
	return 0;
}
