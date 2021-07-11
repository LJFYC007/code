#include<bits/stdc++.h>
using namespace std;
template<typename T>inline T read(){
	T x=0,f=0;char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return f?-x:x;
}
namespace run{
	typedef pair<int,int> P;
	const int N=2e5+9;
	int n,m,head[N],nex[N<<1],to[N<<1],cnt;
	inline void add(int u,int v){
		nex[++cnt]=head[u],head[u]=cnt,to[cnt]=v;
		nex[++cnt]=head[v],head[v]=cnt,to[cnt]=u;
	}

	namespace dl{
		int st[N],tp,dist[N],pre[N];
		P ed[N];queue<int> q;
		inline int bfs(int s){
			for(int i=1;i<=n;i++) dist[i]=0,pre[i]=0;
			q.push(s),dist[s]=1;

			while(!q.empty()){
				int u=q.front();q.pop();
				for(int i=head[u];i;i=nex[i]) if(!dist[to[i]])
					dist[to[i]]=dist[u]+1,q.push(to[i]),pre[to[i]]=u;
			}
			int t=1;
			for(int i=2;i<=n;i++) if(dist[i]>dist[t]) t=i;
			return t;
		}
	}using namespace dl;

	int f[N][2],siz[N],son[N],fa[N],dep[N];
	inline void dfs1(int u,int _f){
		siz[u]=1,fa[u]=_f,dep[u]=dep[_f]+1;
		for(int i=head[u];i;i=nex[i]) if(to[i]^_f){
			dfs1(to[i],u),siz[u]+=siz[to[i]];
			if(siz[to[i]]>siz[son[u]]) son[u]=to[i];
			f[u][1]=max(f[u][1],f[to[i]][1]+1);
		}
	}
	int dfn[N],num,dwn[N],top[N],rak[N];
	inline void dfs2(int u,int _top){
		rak[dfn[u]=++num]=u,top[u]=_top;
		if(son[u]) dfs2(son[u],_top);
		
		for(int i=head[u];i;i=nex[i]) 
			if(!dfn[to[i]]) dfs2(to[i],to[i]);
		dwn[u]=num;
	}

	namespace Seg{
		#define ls (k<<1)
		#define rs (k<<1|1)
		#define mid ((l+r)>>1)

		inline P operator ^(const P &A,const P &B){return P(A.first^B.first,A.second^B.second);}
		P g[N<<2],sum[N<<2];bool tag[N<<2];
		inline void pushup(int k){sum[k]=sum[ls]^sum[rs];}
		inline void pushtag(int k){tag[k]^=1,sum[k]=sum[k]^g[k];}
		inline void pushdown(int k){if(tag[k]) pushtag(ls),pushtag(rs),tag[k]=0;}
		inline void build(int k,int l,int r){
			if(l==r) return sum[k]=g[k]=P(f[rak[l]][0],f[rak[l]][1]),void();
			build(ls,l,mid),build(rs,mid+1,r),g[k]=g[ls]^g[rs],pushup(k);
		}
		inline void modify(int k,int l,int r,int _l,int _r){
			if(_l<=l && r<=_r) return pushtag(k);
			pushdown(k);
			if(_l<=mid) modify(ls,l,mid,_l,_r);
			if(mid<_r) modify(rs,mid+1,r,_l,_r);
			pushup(k);
		}
		inline P query(int k,int l,int r,int _l,int _r){
			if(_l<=l && r<=_r) return sum[k];
			pushdown(k);
			if(_r<=mid) return query(ls,l,mid,_l,_r);
			if(mid<_l) return query(rs,mid+1,r,_l,_r);
			return query(ls,l,mid,_l,_r)^query(rs,mid+1,r,_l,_r);
		}
	}

	inline void modify(int u,int v){
		while(top[u]^top[v]){
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			Seg::modify(1,1,n,dfn[top[u]],dfn[u]),u=fa[top[u]];
		}
		if(dep[u]<dep[v]) swap(u,v);
		Seg::modify(1,1,n,dfn[v],dfn[u]);
	}
	inline int up(int x,int y){
		int z=0;
		while(dep[top[x]]>dep[y]) z=top[x],x=fa[z];
		return x==y?z:son[y];
	}
	inline int query(int x){
		int ret=0;
		while(x){
			P tmp=Seg::query(1,1,n,dfn[top[x]],dfn[x]);
			ret^=tmp.first^tmp.second,x=fa[top[x]];
		}
		return ret;
	}

	int main(){
		n=read<int>(),m=read<int>();
		for(int i=1;i<n;i++){
			int u=read<int>(),v=read<int>();
			add(u,v),ed[i]=P(u,v);
		}

		int s=bfs(1),t=bfs(s),rt=1,peg=0;
		while(t) st[++tp]=t,t=pre[t];t=st[1];
		if(~dist[t]&1){
			peg=1,rt=n+1,s=st[tp>>1],t=st[tp+2>>1];
			if(s>t) swap(s,t);
			for(int i=1;i<=n;i++) head[i]=0;cnt=0;
			for(int i=1;i<n;i++){
				int u=ed[i].first,v=ed[i].second;
				if(u>v) swap(u,v);
				if(!(u==s && t==v)) add(u,v);
			}
			n++,add(n,s),add(n,t),s=st[1],t=st[tp];
		}else rt=st[tp+1>>1];

		bfs(s);
		for(int i=1;i<=n;i++) f[i][0]=max(f[i][0],dist[i]-1);
		bfs(t);
		for(int i=1;i<=n;i++) f[i][0]=max(f[i][0],dist[i]-1);

		dfs1(rt,0),dfs2(rt,rt);
		if(peg && rt==n){
			f[rt][0]=f[rt][1]=0;
			for(int i=1;i<n;i++) f[i][0]--;
		}
		
		Seg::build(1,1,n);
		int x=1;
		while(m--){
			int opt=read<int>();
			if(opt==1){
				int u=read<int>(),v=read<int>();
				modify(u,v);
			}else{
				int u=read<int>();
				if(u==x) Seg::modify(1,1,n,1,n);
				else if(dfn[u]<=dfn[x] && dfn[x]<=dwn[u]){
					int y=up(x,u);
					if(1<dfn[y]) Seg::modify(1,1,n,1,dfn[y]-1);
					if(dwn[y]<n) Seg::modify(1,1,n,dwn[y]+1,n);
				}else Seg::modify(1,1,n,dfn[u],dwn[u]);
			}
			printf("%d\n",(Seg::sum[1].second^query(x=read<int>())));
		}
		return 0;
	}
}
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	return run::main();
}
