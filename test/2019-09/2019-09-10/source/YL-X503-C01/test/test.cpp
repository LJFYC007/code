#include<bits/stdc++.h>
using namespace std;
template<typename T>inline T read(){
	T x=0,f=0;char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return f?-x:x;
}
namespace run{
	typedef long double ld;
	const int N=111;
        const int M=500005;
	const ld eps=1e-15;
	int n,m,k,x[M],y[M],z[M],c[M],s[M],a[M],bit[1<<12];
	ld ans=0.0;
	#define pf(p) ((p)*(p))
	void solve(){
		int tim=0;
		for(int i=1;i<=k;i++){
			ld ide=y[s[i]];
			if(tim) ide*=((ld)1-(ld)c[i-tim]/100);
			ld ret=(ld)1-pf(max((ld)0,(ld)1-(ld)ide/z[i]));
			ans+=a[i]*ret;
			if(ret<0.64-eps) tim=i;
		}
		printf("%.2Lf",ans);
	}
	ld dp[N][N][1<<10];
	#define lowbit(m) ((m)&-(m))
	ld dfs(int pos,int sta,int tim){
		if(pos==k+1) return 0.0;
		if(dp[pos][tim][sta]>eps) return dp[pos][tim][sta];
		ld tmp=0.0,ide=y[s[pos]];
		if(tim) ide*=((ld)1-(ld)c[pos-tim]/100);
		for(int st=sta;st!=-1;st=(!st)?-1:(sta&(st-1))){
			ld iden=ide;
			for(int i=st,j=lowbit(i);i;i-=j,j=lowbit(i))
				iden*=((ld)1+(ld)x[bit[j]]/100);
			ld ret=(ld)1-pf(max((ld)0,(ld)1-iden/z[pos]));
			if(ret<0.64) tmp=max(ret*a[pos]+dfs(pos+1,sta-st,pos),tmp);
			else tmp=max(ret*a[pos]+dfs(pos+1,sta-st,tim),tmp);
		}
		return dp[pos][tim][sta]=tmp;
	}
	int main(){
		n=read<int>(),m=read<int>(),k=read<int>();
		for(int i=1;i<=n;i++) x[i]=read<int>();
		for(int i=1;i<=m;i++) y[i]=read<int>();
		for(int i=1;i<k;i++) c[i]=read<int>();
		for(int i=1;i<=k;i++){
			a[i]=read<int>();
			s[i]=read<int>();
			z[i]=read<int>();
		}
		
		if(n<=0) solve(),exit(0);
		for(int i=0;i<=11;i++) bit[1<<i]=i+1;
		printf("%.2Lf\n",dfs(1,(1<<n)-1,0));
		return 0;
	}
}
int main(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	return run::main();
}
