#include<cstdio>
using namespace std;
const int maxn=1001000;
const long long md=998244353,inv2=(md+1)/2;
long long powd(long long x,int y){
	long long res=1;
	while(y){
		if(y&1) res=res*x%md;
		x=x*x%md;
		y>>=1;
	}
	return res;
}
int readl(){
	char ch=getchar();
	int x=0;
	
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x;
}
int beg[maxn],nex[maxn<<1],tto[maxn<<1],e;
void putin(int s,int t){
	tto[++e]=t;
	nex[e]=beg[s];
	beg[s]=e;
}
long long f[maxn],g[maxn];
void dfs(int u,int fa){
	f[u]=g[u]=1;
	for(int i=beg[u];i;i=nex[i]){
		if(tto[i]==fa) continue;
		dfs(tto[i],u);
		f[u]=(f[u]*g[tto[i]]+g[u]*f[tto[i]])%md;
		g[u]=g[u]*g[tto[i]]%md;
	}
	g[u]=(g[u]+f[u])%md;
}
int main(){
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	int n,s,t;
	n=readl();
	for(int i=2;i<=n;i++){
		s=readl(),t=readl();
		putin(s,t);
		putin(t,s);
	}
	dfs(1,0);
	printf("%lld\n",f[1]*powd(inv2,n-1)%md);
	return 0;
}
