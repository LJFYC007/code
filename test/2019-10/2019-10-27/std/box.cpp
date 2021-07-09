#include<bits/stdc++.h>
#define M 1000005
#define LL long long
#define rint register int
using namespace std;
const int mod=998244353;
int n,m,ed;
char s[M];
int Pw2[M];
LL fac[M],inv[M];
int Pow(LL x,int y){
	LL res=1;
	for(;y;y>>=1,x=x*x%mod)if(y&1)res=res*x%mod;
	return res;
}
LL Com(int x,int y){
	return fac[x]*inv[y]%mod*inv[x-y]%mod;
}
int main(){
	freopen("box.in","r",stdin);
	freopen("box.out","w",stdout);
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	ed=n;n=0;
	for(rint i=1;i<=ed;i++)n+=s[i]=='B';
	scanf("%s",s+1);
	ed=m;m=0;
	for(rint i=1;i<=ed;i++)m+=s[i]=='B';
	if(!n&&!m)printf("%d\n",1%mod);
	else if(!n||!m)printf("%d\n",0);
	else {
		if(n>m)swap(n,m);
		fac[0]=1;
		for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
		inv[n]=Pow(fac[n],mod-2);
		for(int i=n;i;i--)inv[i-1]=inv[i]*i%mod;
		Pw2[0]=1;
		for(rint i=1;i<=n;i++)Pw2[i]=(Pw2[i-1]<<1)%mod;
		LL ans=0;
		for(rint i=0;i<=n;i++){
			LL f=((n-i)&1)?-1:1;
			(ans+=f*Com(n,i)*Pow(Pw2[i]-1,m))%=mod;
			if(ans<0)ans+=mod;
		}
		cout<<ans<<endl;
	}
	return 0;
}
