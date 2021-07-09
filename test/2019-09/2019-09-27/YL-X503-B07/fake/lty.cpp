#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int a=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while('0'<=c&&c<='9'){
		a=a*10+c-'0';
		c=getchar();
	}
	return a;
}
#define MN 600005
#define mn 600005
using namespace std;
int Q[mn],fa[mn],dep[mn],a[mn],N,cnt,top[mn],val[mn],w[mn],id[mn],Min[MN],add[MN],siz[mn],n,m,R,P;
vector<int>edge[mn];
struct data{
	int u,v;
}Que[MN];
void dfs1(int x){
	siz[x]=1;
	for(int i=0;i<edge[x].size();++i){
		if(fa[x]!=edge[x][i]){
			dep[edge[x][i]]=dep[x]+1;
			fa[edge[x][i]]=x;
			dfs1(edge[x][i]);
			siz[x]+=siz[edge[x][i]];
			if(siz[w[x]]<siz[edge[x][i]])w[x]=edge[x][i];
		}
	}
}
void dfs2(int x){
	val[++cnt]=a[x];
	id[x]=cnt;
	if(w[x]){top[w[x]]=top[x];dfs2(w[x]);}
	for(int i=0;i<edge[x].size();++i)
		if(fa[x]!=edge[x][i]&&w[x]!=edge[x][i]){
			top[edge[x][i]]=edge[x][i];
			dfs2(edge[x][i]);
		}
}
void build(int nod,int l,int r){
	if(l==r) {Min[nod]=val[l];return;}
	int mid=(l+r)>>1;
	build(nod<<1,l,mid);
	build(nod<<1|1,mid+1,r);
	Min[nod]=min(Min[nod<<1],Min[nod<<1|1]);
} 
void down(int nod,int l,int r){
	int ll=nod<<1,rr=nod<<1|1,mid=(l+r)>>1;
	add[ll]+=add[nod];
	Min[ll]+=add[nod];
	add[rr]+=add[nod];
	Min[rr]+=add[nod];
	add[nod]=0;
}
void plusline(int nod,int l,int r,int b,int e,int v){
	if(l>e||r<b) return;
	if(b<=l&&r<=e) {Min[nod]+=v;add[nod]+=v;return;}
	int mid=(l+r)>>1;
	down(nod,l,r);
	plusline(nod<<1,l,mid,b,e,v);
	plusline(nod<<1|1,mid+1,r,b,e,v);
	Min[nod]=min(Min[nod<<1],Min[nod<<1|1]);
}
void plusroad(int x,int y,int v){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		plusline(1,1,n,id[top[y]],id[y],v);
		y=fa[top[y]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	plusline(1,1,n,id[x],id[y],v);
}
int askline(int nod,int l,int r,int b,int e){
	if(l>e||r<b) return 1e9;
	if(b<=l&&r<=e) {return Min[nod];}
	down(nod,l,r);
	int mid=(l+r)>>1;
	return min(askline(nod<<1,l,mid,b,e),askline(nod<<1|1,mid+1,r,b,e));
}
int askroad(int x,int y){
	int res=1e9;
	while(top[x]!=top[y]&&res>0){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res=min(res,askline(1,1,n,id[top[y]],id[y]));
		y=fa[top[y]];
	}
	if(dep[x]>dep[y]) swap(x,y);
	return min(res,askline(1,1,n,id[x],id[y]));
}
bool cmp(data a,data b){
	return dep[a.u]>dep[b.u];
}
int main(){
	freopen("fake.in","r",stdin);
	freopen("fake2.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<n;++i){
		int u=read(),v=read();
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	for(int i=1;i<=m;++i){
	
		Que[i].u=read();Que[i].v=read();
	}
	dfs1(1);
	top[1]=1;dfs2(1);
	build(1,1,n);
	for(int i=1;i<=m;++i)if(dep[Que[i].u]>dep[Que[i].v])swap(Que[i].u,Que[i].v);
	sort(Que+1,Que+1+m,cmp);
	int ans=0;
	for(int i=1;i<=m;++i){
		if(askroad(Que[i].u,Que[i].v)>0){
			plusroad(Que[i].u,Que[i].v,-1);
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
