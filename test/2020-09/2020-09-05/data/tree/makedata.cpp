#include <cstdio>
#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <cstring>
#define PB push_back
#define FIR first
#define SEC second
#define MP make_pair
#define PII pair<int,int>
#define ll long long
using namespace std;

namespace MY_STD {
	const int N=2e5+10;
	const int M=11;
	const int mod=998244353;
	inline int Pow(int x,int y) { int res=1; for(;y;y>>=1,x=1ll*x*x%mod) if(y&1) res=1ll*res*x%mod; return res; }
	inline void Add(int &x,int y) { x+=y; if(x>=mod) x-=mod; }
	inline void Add(ll &x,ll y) { x+=y; if(x>=mod) x-=mod; }
	inline void Dec(int &x,int y) { x-=y; if(x<0) x+=mod; }
	inline void Dec(ll &x,ll y) { x-=y; if(x<0) x+=mod; }
	inline int ADD(int x) { return x>=mod?x-mod:x; }
	inline int SUB(int x) { return x<0?x+mod:x; } 
	vector<int> son[N];
	int dep[N],n;
	int seq[N],val[N],ncnt,cur_mi;
	int check_data;
	void dfs(int u) {
		check_data++;
		if(!son[u].size()) {
			seq[++ncnt]=u;
			val[ncnt]=cur_mi;
			cur_mi=1e9;
		}
		cur_mi=min(cur_mi,dep[u]);
		for(int i=0;i<son[u].size();++i) {
			int v=son[u][i];
			dep[v]=dep[u]+1;
			dfs(son[u][i]);
			cur_mi=min(cur_mi,dep[u]);
		}
	}
	int sum[M][N];
	int C[M][M];
} 
	namespace TREE {
		using namespace MY_STD;
		const int N=2e5+10;
		int Lg[N],rmq[18][N];
		inline int rmq_getmin(int x,int y) { return val[x]<val[y] ? x : y; }
		void init_rmq() {
			for(int i=2;i<=n;++i) Lg[i]=Lg[i>>1]+1,rmq[0][i]=i;
			for(int j=1;j<=17;++j)
				for(int i=2;i+(1<<j)-1<=n;++i)
					rmq[j][i]=rmq_getmin(rmq[j-1][i],rmq[j-1][i+(1<<j-1)]);
		}
		int Qmin(int l,int r) {
			int L=Lg[r-l+1];
			return rmq_getmin(rmq[L][l],rmq[L][r-(1<<L)+1]);
		}	
		int ch[N][2],pre[N],suf[N];
		int s[N][M],a[N][M][M][2],b[N][M][M][2];
		int sub[N][M],subl[N][M],subr[N][M];
		int al[N][M][M][2],br[N][M][M][2];
		void build(int l,int r,int &i) {
			if(l>r) return (void)(i=0);
			i=Qmin(l,r);
			pre[i]=l-1,suf[i]=r+1;
			for(int t=0;t<M;++t)
				for(int j=0;j<=t;++j) {
					Add(s[i][t],1ll*val[i]*C[t][j]%mod*(sum[t-j][suf[i]-2]-sum[t-j][i-2]+mod)%mod*(sum[j][i-1]-sum[j][pre[i]-1]+mod)%mod*(j&1 ? mod-1 : 1)%mod);
					Add(a[i][t][j][0],1ll*val[i]*C[t][j]%mod*(sum[t-j][suf[i]-2]-sum[t-j][i-2]+mod)%mod*sum[j][i-1]%mod*(j&1 ? mod-1 : 1)%mod);
					Add(a[i][t][j][1],1ll*val[i]*C[t][j]%mod*(sum[t-j][suf[i]-2]-sum[t-j][i-2]+mod)%mod*(j&1 ? 1 : mod-1)%mod);
					Add(b[i][t][j][0],1ll*val[i]*C[t][j]%mod*(sum[t-j][i-1]-sum[t-j][pre[i]-1]+mod)%mod*(t-j&1 ? mod-1 : 1)%mod*(mod-sum[j][i-2])%mod);
					Add(b[i][t][j][1],1ll*val[i]*C[t][j]%mod*(sum[t-j][i-1]-sum[t-j][pre[i]-1]+mod)%mod*(t-j&1 ? mod-1 : 1)%mod);
				}
			build(l,i-1,ch[i][0]);
			build(i+1,r,ch[i][1]);
			for(int t=0;t<M;++t)
				sub[i][t]=((ll)s[i][t]+sub[ch[i][0]][t]+sub[ch[i][1]][t])%mod;
		}
	//	void dfs0(int u) {
	//		if(!u) return;
	//		dfs0(ch[u][0]),dfs0(ch[u][1]);
	//		for(int t=0;t<M;++t)
	//			sub[u][t]=((ll)s[u][t]+sub[ch[u][0]][t]+sub[ch[u][1]][t])%mod;
	//	}
		void dfs1(int u) {
			for(int t=0;t<=M-1;++t) {
				Add(subl[u][t],s[u][t]),
				Add(subr[u][t],s[u][t]);
			}
			if(ch[u][0]) {
				for(int t=0;t<M;++t) {
					subl[ch[u][0]][t]=subl[u][t],
					subr[ch[u][0]][t]=subr[u][t];
					for(int j=0;j<=t;++j)
						al[ch[u][0]][t][j][0]=ADD(al[u][t][j][0]+a[u][t][j][0]),
						al[ch[u][0]][t][j][1]=ADD(al[u][t][j][1]+a[u][t][j][1]),
						br[ch[u][0]][t][j][0]=br[u][t][j][0],
						br[ch[u][0]][t][j][1]=br[u][t][j][1];
				}
				for(int t=0;t<M;++t)
					Add(subr[ch[u][0]][t],sub[ch[u][1]][t]);
				dfs1(ch[u][0]);
			}
			if(ch[u][1]) {
				for(int t=0;t<M;++t) {
					subl[ch[u][1]][t]=subl[u][t],
					subr[ch[u][1]][t]=subr[u][t];
					for(int j=0;j<=t;++j)
						al[ch[u][1]][t][j][0]=al[u][t][j][0],
						al[ch[u][1]][t][j][1]=al[u][t][j][1],
						br[ch[u][1]][t][j][0]=ADD(br[u][t][j][0]+b[u][t][j][0]),
						br[ch[u][1]][t][j][1]=ADD(br[u][t][j][1]+b[u][t][j][1]);
				}
				for(int t=0;t<M;++t)
					Add(subl[ch[u][1]][t],sub[ch[u][0]][t]);
				dfs1(ch[u][1]);
			}
		}
		int rt;
		void init() {
			rt=0;
			memset(ch,0,sizeof(ch));
			memset(s,0,sizeof(s));
			memset(a,0,sizeof(a));
			memset(b,0,sizeof(b));
			memset(sub,0,sizeof(sub));
			memset(subl,0,sizeof(subl));
			memset(subr,0,sizeof(subr));
			memset(al,0,sizeof(al));
			memset(br,0,sizeof(br));
			
			init_rmq();
			build(2,ncnt,rt);
	//		dfs0(rt);
			dfs1(rt);
		}
		void Qry(int *f,int m,int L,int R) {
			if(L>=R) {
				for(int t=0;t<=m;++t) {
					f[t]=0;
					for(int j=0;j<=t;++j)
						for(int i=L;i<=R;++i) if(val[i])
							Add(f[t],1ll*val[i]*C[t][j]%mod*(sum[t-j][min(suf[i],R+1)-2]-sum[t-j][i-2]+mod)%mod*(sum[j][i-1]-sum[j][max(pre[i],L-1)-1]+mod)%mod*(j&1 ? mod-1 : 1)%mod);
				}
				return;
			}
			int lca=Qmin(L,R);
			for(int t=0;t<=m;++t) {
				f[t]=SUB(sub[lca][t]-s[lca][t]);
				Dec(f[t],SUB(subl[L][t]-subl[lca][t]));
				Dec(f[t],SUB(subr[R][t]-subr[lca][t]));
				if(ch[L][0]) Dec(f[t],sub[ch[L][0]][t]);
				if(ch[R][1]) Dec(f[t],sub[ch[R][1]][t]);
				for(int j=0;j<=t;++j) {
					int tmp_a[2]={SUB(al[L][t][j][0]-al[lca][t][j][0]),(al[L][t][j][1]-al[lca][t][j][1])};
					int tmp_b[2]={SUB(br[R][t][j][0]-br[lca][t][j][0]),(br[R][t][j][1]-br[lca][t][j][1])};
					Dec(tmp_a[0],a[lca][t][j][0]);
					Dec(tmp_a[1],a[lca][t][j][1]);
					Dec(tmp_b[0],b[lca][t][j][0]);
					Dec(tmp_b[1],b[lca][t][j][1]);
					Add(tmp_a[0],a[L][t][j][0]);
					Add(tmp_a[1],a[L][t][j][1]);
					Add(tmp_b[0],b[R][t][j][0]);
					Add(tmp_b[1],b[R][t][j][1]);
					Add(f[t],(tmp_a[0]+1ll*tmp_a[1]*sum[j][(L-1)-1])%mod);
					Add(f[t],(tmp_b[0]+1ll*tmp_b[1]*sum[j][(R+1)-2])%mod);
					Add(f[t],1ll*val[lca]*C[t][j]%mod*(sum[t-j][(R+1)-2]-sum[t-j][lca-2]+mod)%mod*(sum[j][lca-1]-sum[j][(L-1)-1]+mod)%mod*(j&1 ? mod-1 : 1)%mod);
				}
			}
		}
	}
namespace MY_STD { 
	int sum_dep[N];
	int coe[M],f[M],g[M],pw2[M];
	int m;
	int Qry(int x,int y,int m) {
		int L=lower_bound(seq+1,seq+ncnt+1,x)-seq;
		int R=upper_bound(seq+1,seq+ncnt+1,y)-seq-1;
		if(R<L) return 0;
		
		TREE::Qry(g,m-2,L+1,R);
		
		for(int j=2;j<=m;++j)
			for(int t=2;t<=j;++t)
				f[j]=(f[j]+1ll*(pw2[t]-2ll+mod)*C[j][t]%mod*g[j-t])%mod;
		
		for(int j=1;j<=m;++j)
			f[j]=(f[j]+(sum_dep[R]-sum_dep[L-1]+mod)%mod)%mod;
		for(int j=1;j<=m-1;++j)
			for(int k=0;k<=j;++k)
				Add(coe[k+(m-j)],1ll*C[m][j]*C[j][k]%mod*Pow(R-L+1,j-k)%mod*(k&1 ? mod-1 : 1)%mod);
		int ans=0;
		for(int j=1;j<=m;++j) ans=(ans+1ll*f[j]*coe[j]%mod)%mod;
		ans=1ll*ans*Pow(R-L+1,1ll*m*(mod-2)%(mod-1))%mod; 
		for(int j=1;j<=m;++j) f[j]=0,coe[j]=0;
		return ans;
	}
	void my_main(int _n,int *fa) {
		n=_n;
		ncnt=0;
		check_data=0; 
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		memset(coe,0,sizeof(coe));
		memset(sum,0,sizeof(sum));
		for(int i=1;i<=n;++i) son[i].clear();
		for(int i=0;i<=M-1;++i) for(int j=0;j<=i;++j) C[i][j]=j ? (C[i-1][j-1]+C[i-1][j])%mod : 1;
		pw2[0]=1; for(int i=1;i<=M-1;++i) pw2[i]=pw2[i-1]*2ll%mod;
		for(int j=0;j<=M-1;++j) {
			sum[j][0]=j==0;
			for(int i=1;i<=n;++i) sum[j][i]=(sum[j][i-1]+Pow(i,j))%mod;
		}
		
		for(int i=2;i<=n;++i) son[fa[i]].PB(i);
		dfs(1);
		TREE::init();
		
		cerr<<check_data<<' '<<ncnt<<endl;
		
		for(int i=1;i<=ncnt;++i) sum_dep[i]=(sum_dep[i-1]+dep[seq[i]])%mod;
	}
}

const int N=2e5+10;

vector<int> son[N];
int dfn[N],ncnt;
int fa[N];

void dfs(int u,int last) {
	dfn[u]=++ncnt;
	if(last) fa[dfn[u]]=dfn[last];
	for(int v : son[u]) dfs(v,u);
}

int n=200000;
int q=20000;
int m=10;
int flg;
void makedata(int id) {
	if(id==0) {
		for(int i=2;i<=n;++i) son[1].PB(i);
	}
	else if(id==1) {
		vector<PII> item;
		int M=ceil(sqrt(n));
		for(int i=1;i<=n;i+=M) {
			int j=min(i+M-1,n);
			for(int k=i+1;k<=j;++k)
				son[k-1].PB(k);
			item.PB(MP(i,j));
		}
		for(int i=1;i<item.size();++i) son[item[(i+1>>1)+1].SEC].PB(item[i].FIR);
	}
	else if(id==2) {
		int t=n/3;
		for(int i=2;i<=t;++i) son[i-1].PB(i);
		for(int i=t+1;i<=n;++i) son[rand()%t+1].PB(i);
	}
	else {
		for(int i=2;i<=n;++i) son[rand()%(i-1)+1].PB(i);
	}
	ncnt=0,fa[1]=0;
	dfs(1,0);
	cout<<flg<<' '<<n<<' '<<q<<endl;
	for(int i=2;i<=n;++i) cout<<fa[i]<<' '; cout<<endl;
	if(flg==0) {
		for(int t=1;t<=q;++t) {
			int L=rand()%n+1,R=rand()%n+1;
			if(L>R) swap(L,R);
			cout<<L<<' '<<R<<' '<<rand()%(m-2+1)+2<<endl;
		} 
	}
	else {
		MY_STD::my_main(n,fa);
		int lastans=0;
		for(int t=1;t<=q;++t) {
			int L=rand()%n+1,R=rand()%n+1,k=rand()%(m-2+1)+2;
			if(L>R) swap(L,R);
			cout<<(L^lastans)<<' '<<(R^lastans)<<' '<<k<<endl;
//			cerr<<lastans<<endl;
			lastans=MY_STD::Qry(L,R,k);
		}
	}
	for(int i=1;i<=n;++i) son[i].clear(); 
}
#include <ctime>
char In[50],Out[50];
char op[50];
int main() {
	srand((unsigned long long)new char + time(0));
	int id; scanf("%d%d",&id,&flg);
	for(int i=0;i<5;++i) {
		sprintf(In,"%d_%d.in",id,i);
		sprintf(Out,"%d_%d.ans",id,i);
		
		freopen(In,"w",stdout);
		makedata(i);
		fclose(stdout);
		
//		sprintf(op,"rand.exe > %s",In);
//		system(op);
		sprintf(op,"std.exe < %s > %s",In,Out);
		system(op);
//		Sleep(1000);
	}
	return 0;
}

