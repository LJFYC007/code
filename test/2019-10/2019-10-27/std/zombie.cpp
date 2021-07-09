#include<bits/stdc++.h>
#define M 2005
#define LL long long
using namespace std;

const LL mod=998244353;

inline void Rd(int &x){
	char c;x=0;
	while((c=getchar())<48);
	do x=(x<<3)+(x<<1)+(c^48);
	while((c=getchar())>47);
}

LL Pow(LL x,int n){
	LL res=1;
	while(n){
		if(n&1)res=res*x%mod;
		x=x*x%mod;
		n>>=1;
	}
	return res;
}

int n,m;

struct edge{
	int to,fr,l,r;
}E[M<<1];
int lst[M],tote;
void addedge(int a,int b,int l,int r){
	E[++tote]=(edge){b,lst[a],l,r};
	lst[a]=tote;
}

struct Zombie{
	int pos,h;
	bool operator <(const Zombie &_)const{
		return h<_.h;
	}
}A[M];
int dp[M][M];
LL tmp[M];
bool hav[M][M];

void Add(int &x,int y){
	x+=y;
	if(x>=mod)x-=mod;
}

void dfs(int u,int f){
	int id=1;
	for(int i=1;i<=m;i++)
		if(A[i].pos==u){
			hav[u][i]=1;
			id=i;
		}else hav[u][i]=0;
	for(int i=1;i<=m;i++)dp[u][i]=i>=id;
	for(int i=lst[u];i;i=E[i].fr){
		int v=E[i].to;
		int l=E[i].l,r=E[i].r,len=r-l+1;
		if(v==f)continue;
		dfs(v,u);
		for(int j=1;j<=m;j++)tmp[j]=dp[u][j],dp[u][j]=0;
		int sum=0;
		for(int j=1;j<=m;j++){
			LL x=max(0,min(A[j].h,r+1)-l),y=len-x;
			Add(dp[u][j],x*tmp[j]%mod*dp[v][j]%mod);
			if(hav[v][j])Add(sum,dp[v][j]);
			else Add(dp[u][j],y*sum%mod*tmp[j]%mod);
		}
		sum=0;
		for(int j=m;j;j--){
			LL x=max(0,min(A[j].h,r+1)-l),y=len-x;
			if(hav[v][j])Add(sum,y*dp[v][j]%mod);
			else Add(dp[u][j],tmp[j]*sum%mod);
			hav[u][j]|=hav[v][j];
		}
	}
}

void reset(){
	for(int i=1;i<=n;i++)lst[i]=0;
	tote=0;
}

int main(){
	freopen("zombie.in","r",stdin);
	freopen("zombie.out","w",stdout);
	for(int _=(Rd(_),_);_;_--){
		Rd(n),Rd(m);
		reset();
		LL all=1;
		for(int i=1,a,b,l,r;i<n;i++){
			Rd(a),Rd(b),Rd(l),Rd(r);
			all=all*(r-l+1)%mod;
			addedge(a,b,l,r);
			addedge(b,a,l,r);
		}
		for(int i=1;i<=m;i++)Rd(A[i].pos),Rd(A[i].h);
		sort(A+1,A+m+1);
		dfs(1,0);
		int ans=0;
		for(int i=1;i<=m;i++)Add(ans,dp[1][i]);
		ans=(all-ans+mod)%mod;
		printf("%lld\n",Pow(all,mod-2)*ans%mod);
	}
	return 0;
}
