#include<bits/stdc++.h>
using namespace std;
#define RI long long
#define int long long
const int mod=1e9+7,N=2010;
long long xxx,yyy;
int n,m,K,ans,f[N<<1][N][2],s[N];
int qm(int x) {return x>=mod?x-mod:x;}
signed main()
{
	cin>>m>>n>>K>>xxx>>yyy;
	if(xxx==yyy)
	{
		cout<<1;
		return 0;
	}
	f[0][0][0]=1;
	for(RI i=1;i<=max(n,m)*2;++i) {
		s[0]=qm(f[i-1][0][0]+f[i-1][0][1]);
		for(RI j=1;j<=n;++j)
			s[j]=qm(s[j-1]+qm(f[i-1][j][0]+f[i-1][j][1]));
		for(RI j=0;j<=n;++j) {
			f[i][j][0]=qm(s[j]-s[j-1]+mod);
			if(j) f[i][j][1]=qm(s[j-1]-(j-K>=0?s[j-K]:0)+mod);
		}
		for(RI j=0;j<=n;++j)
			if(j%(K-1)==n%(K-1)&&(i*(K-1)-j+1)%(K-1)==m%(K-1)&&i*(K-1)-j+1<=m)
				ans=qm(ans+f[i][j][1]);
	}
	printf("%lld\n",ans);
	return 0;
}