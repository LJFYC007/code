#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e18;
#define MN 200005
int T,n,m,k,d,a[MN],suf[MN];
int calc(int v){
	if(v*suf[1]>d)return -inf;
	int tmp=d;
	int res=v*k+v*m;tmp-=v*suf[1];
	for(int i=1;i<=m;++i){
		if(a[i]*(n-v)<=tmp){
			tmp-=a[i]*(n-v);
			res+=(n-v);
		}
		else {res+=tmp/a[i];break;}
	}
	return res;
}
signed main(){
	freopen("array.in","r",stdin);
	freopen("array.out","w",stdout);
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld%lld%lld",&n,&m,&k,&d);
		for(int i=1;i<=m;++i)scanf("%lld",&a[i]);
		sort(a+1,a+1+m);
		suf[m+1]=0;for(int i=m;i;--i)suf[i]=suf[i+1]+a[i];
		int l=0,r=n;
		while(l+10<=r){
			int ml=l+(r-l)/3,mr=r-(ml-l);
			if(calc(ml)<calc(mr))l=ml;
			else r=mr;
		}
		int ans=0;
		for(int j=l;j<=r;++j)ans=max(ans,calc(j));
		printf("%lld\n",ans);
	}
	return 0;
}
