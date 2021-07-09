#include<bits/stdc++.h>
using namespace std;
template<typename T>inline T read(){
	T x=0,f=0;char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return f?-x:x;
}
namespace run{
//	typedef pair<int,int> P;
	const int N=2e6+9,Log=21,mod=998244353;
	inline int _add(int x,int y){return x+y>=mod?x-mod+y:x+y;}
	inline int _sub(int x,int y){return x>=y?x-y:x+mod-y;}
	inline int qpow(int x,int y){
		int ret=1;
		while(y){
			if(y&1) ret=1LL*ret*x%mod;
			x=1LL*x*x%mod;y>>=1;
		}
		return ret;
	}
	inline int inv(int x){return x?qpow(x,mod-2):1;}

	int head[N],nex[N<<1],to[N<<1],f[N][Log],cnt,dep[N];
	inline void add(int u,int v){
		nex[++cnt]=head[u];
		head[u]=cnt;to[cnt]=v;
	}
	int num,dfn[N],dwn[N];
	inline void dfs(int u,int _f){
		dep[u]=dep[_f]+1,f[u][0]=_f,dfn[u]=++num;
		for(int j=1;j<Log;j++) f[u][j]=f[f[u][j-1]][j-1];
		for(int i=head[u];i;i=nex[i])
			if(to[i]^_f) dfs(to[i],u);
		dwn[u]=num;
	}

	struct node{
		int u,l,v,id;
		explicit node(){}
		node(int _u,int _l,int _v,int _i):
			u(_u),l(_l),v(_v),id(_i){}
		bool operator <(const node &B)const{
			if(u^B.u) return u<B.u;
			if(l^B.l) return l<B.l;
			if(v^B.v) return v<B.v;
			return id<B.id;
		}
		bool operator ==(const node &B)const{
			return u==B.u && v==B.v;
		}
	}z[N];

	inline int lca(int u,int v){
		if(dep[u]<dep[v]) swap(u,v);
		for(int i=Log-1;~i;i--)
			if(dep[f[u][i]]>=dep[v]) u=f[u][i];
		if(u==v) return u;
		for(int i=Log-1;~i;i--)
			if(f[u][i]^f[v][i]) u=f[u][i],v=f[v][i];
		return f[u][0];
	}
	int n,m,S[N],T[N],P[N],val[N],tot,lim[N],ans[N],ex[N],nnum[N],Lca[N];
	int _u[N],_v[N];
	inline void getmul(int u,int _f){
		for(int i=head[u];i;i=nex[i])
			if(to[i]^_f){
				val[to[i]]=1LL*val[u]*val[to[i]]%mod;
				getmul(to[i],u);
			}
	}
	inline void getsum(int u,int _f){
		for(int i=head[u];i;i=nex[i]){
			if(to[i]^_f){
				getsum(to[i],u);
				ex[u]=1LL*ex[u]*ex[to[i]]%mod;
				nnum[u]=nnum[u]+nnum[to[i]];
			}
		}
	//	cout<<u<<" "<<ex[u]<<endl;
	}
	inline void reget(int u,int _f){
		for(int i=head[u];i;i=nex[i]){
			if(to[i]^_f){
				nnum[to[i]]+=nnum[u];
				reget(to[i],u);
			}
		}
	}
	int main(){
		n=read<int>(),m=read<int>();
		for(int i=1;i<n;i++){
			int u=read<int>(),v=read<int>();
			add(u,v),add(v,u);
		}
		for(int i=1;i<=n;i++) ex[i]=val[i]=1;
		dfs(1,0);

		int sum=0;
		for(int i=1;i<=m;i++){
			S[i]=read<int>(),T[i]=read<int>(),P[i]=read<int>();
			if(S[i]==T[i]) i--,m--;
		}
	//	cout<<sum<<endl;
		for(int i=1;i<=m;i++){
			int L=lca(S[i],T[i]);lim[i]=dep[L];
			int upS=S[i],upT=T[i];Lca[i]=L;
			for(int j=Log-1;~j;j--){
				if(dep[f[upS][j]]>dep[L]) upS=f[upS][j];
				if(dep[f[upT][j]]>dep[L]) upT=f[upT][j];
			}
			ans[i]=1;
			if(P[i] && upS^L && upT^L) z[++tot]=node(min(upS,upT),L,max(upT,upS),i),ans[i]=inv(P[i]);
			if(upS^L){
				if(P[i]) val[upS]=1LL*val[upS]*P[i]%mod;
				_u[i]=upS;
			}
			if(upT^L){
				if(P[i]) val[upT]=1LL*val[upT]*P[i]%mod;
				_v[i]=upT;
			}
			ans[i]=1LL*ans[i]*inv(P[i])%mod;
		}
		getmul(1,0);
		for(int i=1;i<=m;i++){
			int tmp=S[i],ret=1;
			if(P[i]){
			//	if(i==1){
				int y=inv(P[i]);
				if(S[i]^Lca[i]) ex[S[i]]=1LL*ex[S[i]]*P[i]%mod;//,cout<<S[i]<<" "<<P[i]<<endl;
				if(T[i]^Lca[i]) ex[T[i]]=1LL*ex[T[i]]*P[i]%mod;//,cout<<T[i]<<" "<<P[i]<<endl;
				if(_u[i]) ex[_u[i]]=1LL*ex[_u[i]]*y%mod;//,cout<<_u[i]<<" "<<i<<endl;
				if(_v[i]) ex[_v[i]]=1LL*ex[_v[i]]*y%mod;//,cout<<_v[i]<<" "<<i<<endl;
			//	}
			}else{
				nnum[S[i]]++,nnum[Lca[i]]--;
				nnum[T[i]]++,nnum[Lca[i]]--;
			}
			int x=inv(val[Lca[i]]);
			ret=1LL*ret*val[S[i]]%mod*val[T[i]]%mod*x%mod*x%mod;
			ret=1LL*ret*_sub(1,P[i])%mod;
			ans[i]=1LL*ans[i]*ret%mod;
		}
	//	for(int i=1;i<=n;i++) cout<<ex[i]<<" ";
	//	cout<<endl;

		getsum(1,0);
	//	for(int i=1;i<=n;i++) cout<<ex[i]<<" ";
	//	cout<<endl;


	//	for(int i=1;i<=n;i++) cout<<nnum[i]<<" ";
	//	cout<<endl;
		reget(1,0);
		for(int i=1;i<=m;i++){
			int tmp=S[i],c=nnum[S[i]]+nnum[T[i]]-2*nnum[Lca[i]],s=P[i]?0:dep[S[i]]+dep[T[i]]-2*dep[Lca[i]];
			if(c>s) ans[i]=0;
		}
	//	for(int i=1;i<=m;i++) cout<<ans[i]<<" ";
	//	cout<<endl;

		sort(z+1,z+tot+1);
		for(int Beg=1,End;Beg<=tot;Beg=End+1){
			End=Beg;
			while(End+1<=tot && z[Beg]==z[End+1]) End++;
			int mul=1;
			for(int i=Beg;i<=End;i++) mul=1LL*inv(P[z[i].id])*mul%mod;
			for(int i=Beg;i<=End;i++) ans[z[i].id]=1LL*ans[z[i].id]*mul%mod*P[z[i].id]%mod;
		}
	//	cout<<ans[1]<<endl;
	//	for(int i=1;i<=m;i++) cout<<ans[i]<<" ";//<<_sub(1,P[i])<<endl;;
	//	cout<<endl;
//		for(int i=1;i<=n;i++) cout<<ex[i]<<" ";
//		cout<<endl;
	//	cout<<sum<<endl;
		for(int i=1;i<=m;i++){
			if(_u[i]) ans[i]=1LL*ex[_u[i]]*ans[i]%mod;
			if(_v[i]) ans[i]=1LL*ex[_v[i]]*ans[i]%mod;
	//		cout<<ans[i]<<" ";
			sum=_add(sum,ans[i]);
		}
	//	cout<<1LL*2*(mod-3)*4%mod<<endl;
		printf("%d\n",sum);
		return 0;
	}
}
#define my mine
int main(){
	return run::main();
}
