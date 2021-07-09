#include<bits/stdc++.h>
using namespace std;
template<typename T>inline T read(){
	T x=0,f=0;char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return f?-x:x;
}
namespace run{
	const int N=1e5+9;double eps=1e-10;
	int n,m,head[N],nex[N<<1],to[N<<1],cnt;
	inline void add(int u,int v){
		nex[++cnt]=head[u];
		head[u]=cnt,to[cnt]=v;
	}
	int siz[N],son[N],fa[N],dep[N];
	inline void dfs1(int u,int _f){
		siz[u]=1,fa[u]=_f,dep[u]=dep[_f]+1;
		for(int i=head[u];i;i=nex[i]) if(to[i]^_f){
			dfs1(to[i],u),siz[u]+=siz[to[i]];
			if(siz[to[i]]>siz[son[u]]) son[u]=to[i];
		}
	}
	int dfn[N],top[N],num;
	inline void dfs2(int u,int tp){
		dfn[u]=++num,top[u]=tp;
		if(son[u]) dfs2(son[u],tp);

		for(int i=head[u];i;i=nex[i])
			if(!dfn[to[i]]) dfs2(to[i],to[i]);
	}
	typedef pair<double,double> P;
	inline int lca(int u,int v){
		while(top[u]!=top[v]){
			if(dep[top[u]]<dep[top[v]]) swap(u,v);
			u=fa[top[u]];
		}
		if(dep[u]>dep[v]) swap(u,v);
		return u;
	}

	double Time;
	struct node{
		int u;double t,c,ddl;explicit node(){}
		node(int _u,double _t,double _c,double _ddl):u(_u),t(_t),c(_c),ddl(_ddl){}
		bool operator <(const node &A)const{
			double d1=dep[u]+(Time-t)*c;
			double d2=dep[A.u]+(Time-A.t)*A.c;
			return d1<d2;
		}
	};
	vector<node> ev[N];
	inline void modify1(double t,double c,int u,int v){
		while(top[u]!=top[v]){
			double ddl=t+1.*(dep[u]-dep[fa[top[u]]])/c;
			ev[u].push_back(node(u,t,-c,ddl)),ev[u].push_back(node(-u,t,-c,ddl));
			t+=1.*(dep[u]-dep[fa[top[u]]])/c,u=fa[top[u]];
		}
		double ddl=t+1.*(dep[u]-dep[v])/c;
		ev[u].push_back(node(u,t,-c,ddl)),ev[u].push_back(node(-u,t,-c,ddl));
	}inline void modify2(double t,double c,int u,int v){
		while(top[u]!=top[v]){
			double ddl=t;t-=1.*(dep[u]-dep[fa[top[u]]])/c;
			ev[u].push_back(node(fa[top[u]],t,c,ddl)),ev[u].push_back(node(-fa[top[u]],t,c,ddl));
			u=fa[top[u]];
		}
		double ddl=t;
		t-=1.*(dep[u]-dep[v])/c;
		ev[u].push_back(node(v,t,c,ddl)),ev[u].push_back(node(-v,t,c,ddl));
	}

	double ans=1e18;
	int st[N],_top,tot;node q[N<<4];
	inline bool cmp(node A,node B){
		double At=A.t,Bt=B.t;
		if(A.u<0) At=A.ddl;
		if(B.u<0) Bt=B.ddl;
		if(At!=Bt) return At<Bt;
		return A.u>B.u;
	}
	
	multiset<node> Set;
	typedef multiset<node>::iterator iter;
	inline void get(node A,node B){
		double sA=dep[A.u],sB=dep[B.u],t,tim;
		if(A.t<B.t) sA+=A.c*(B.t-A.t);
		if(B.t<A.t) sB+=B.c*(A.t-B.t);
		t=max(A.t,B.t);
		if(fabs(sA-sB)<eps){
			if(t-eps<min(A.ddl,B.ddl)) ans=min(ans,t);
			return;
		}
		tim=(sA-sB)/(B.c-A.c);
		if(tim>eps && t+tim-eps<min(A.ddl,B.ddl)) ans=min(ans,t+tim);
	}
	inline void calc(){
		tot=0,reverse(st+1,st+_top+1);
		for(int i=1;i<=_top;i++)
			for(int j=0;j<ev[st[i]].size();j++) q[++tot]=ev[st[i]][j];
		sort(q+1,q+tot+1,cmp),Set.clear();
		Time=0.;
		for(int i=1;i<=tot && q[i].t<ans;i++){
			if(q[i].u>0){
				Time=q[i].t;
				if(Time>ans) break;
				Set.insert(q[i]);
				iter it=Set.find(q[i]),pre=it,suf=it;
				int peg=0;
				if(pre!=Set.begin()) peg++,pre--,get(*pre,*it);
				if(++suf!=Set.end()) peg++,get(*suf,*it);
				if(peg==2) get(*pre,*suf);
			}else{
				Time=q[i].ddl;
				if(Time>ans) break;
				node _q=q[i];_q.u=-_q.u;
				iter it=Set.find(_q),pre=it,suf=it;
				int peg=0;
				if(pre!=Set.begin()) peg++,pre--,get(*pre,*it);
				if(++suf!=Set.end()) peg++,get(*suf,*it);
				if(peg==2) get(*pre,*suf);
				Set.erase(it);
			}
		}
	}

	inline void solve(int u,int _f){
		st[++_top]=u;
		if(son[u]) solve(son[u],u);
		else return calc();

		for(int i=head[u];i;i=nex[i])
			if(to[i]^_f && to[i]^son[u])
				_top=0,solve(to[i],u);
	}

	int main(){
		n=read<int>(),m=read<int>();
		for(int i=1;i<n;i++){
			int u=read<int>(),v=read<int>();
			add(u,v),add(v,u);
		}
		dfs1(1,0),dfs2(1,1);
		for(int i=1;i<=m;i++){
			double t=read<int>(),c=read<int>();
			int u=read<int>(),v=read<int>(),Lca=lca(u,v);
			if(Lca==u) modify2(1.*t+1.*(dep[v]-dep[u])/c,c,v,u);
			else if(Lca==v) modify1(t,c,u,v);
			else modify1(t,c,u,Lca),modify2(1.*t+1.*(dep[u]+dep[v]-2*dep[Lca])/c+1000*eps,c,v,Lca);
		}
		solve(1,0);
		if(ans>1e17) puts("-1.0000000");
		else printf("%.7lf\n",ans);
		return 0;
	}
}
int main(){
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
	return run::main();
}
