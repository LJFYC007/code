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
#define MN 200005
#define pii pair<int,int>
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define vc vector
int n,a[MN],ans=1e6;
map<int,int>vis;
void solve(int x){
	vc<int>td(0);
	for(int i=2;i*i<=x;++i){
		if(x%i==0){td.pb(i);while(x%i==0)x/=i;}
	}
	if(x!=1)td.pb(x);
	for(auto j:td){
		int res=0;
		if(vis.count(j))continue;
		vis[j]=1;
		for(int i=1;i<=n;++i){
			res+=min(a[i]>=j?a[i]%j:j,j-a[i]%j);
		}
		if(ans>=res)cerr<<j<<": "<<res<<endl;
		ans=min(ans,res);
	}
}
signed main(){
//	freopen("gcd1.in","r",stdin);
//	freopen("gcd1.out","w",stdout);
	n=read();
	srand(time(0));
	for(int i=1;i<=n;++i){
		a[i]=read();
		assert(a[i]);
	}
	int ti=20;
	while(ti--){
		int x=(rand())%n+1;
		solve(a[x]);
		if(a[x]!=1)solve(a[x]-1);
		solve(a[x]+1);
	}
	printf("%lld\n",ans);
	return 0;
}
