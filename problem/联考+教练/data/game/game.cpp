#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	int a=0,fh=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')fh=-1;c=getchar();}
	while('0'<=c&&c<='9'){
		a=a*10+c-48;
		c=getchar();
	}
	return a*fh;
}
#define mn 205
#define pii pair<int,int>
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define vc vector
int n,d,Mod;
int f[mn][mn],sum[mn],C[mn][mn];
signed main(){
	n=read(),d=read(),Mod=read();
	f[1][0]=sum[1]=1;
	C[0][0]=1;
	for(int i=1;i<=n;++i){
		C[i][0]=1;
		for(int j=1;j<=n;++j){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
		}
	}
	for(int i=2;i<=n;++i){
		for(int j=1;j<i&&j<=d;++j)
			for(int k=1;k<i;++k)
				f[i][j]=(f[i][j]+f[i-k][j-1]*C[i-2][k-1]%Mod*sum[k])%Mod;
		for(int j=1;j<d;++j)sum[i]=(sum[i]+f[i][j])%Mod;
	}
	int ans=0;
	for(int i=0;i<n;++i)
		for(int k=0;k<=d;++k)
			if(k!=1)
			for(int j=0;j+k<=d;++j)
				ans=(ans+f[i+1][j]*f[n-i][k])%Mod;
	printf("%lld\n",2ll*n*(n-1)*ans%Mod);
	return 0;
}
