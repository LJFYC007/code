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
int n,m,k,s,c[MN],C[MN];
int F[MN];
int u[MN],v[MN];
int Find(int a){
	if(F[a]==a)return a;
	return F[a]=Find(F[a]);
}
signed main(){
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
	n=read();m=read();k=read();s=read();
	for(int i=1;i<=n;++i)c[i]=read();
	for(int i=1;i<=m;++i){
		u[i]=read(),v[i]=read();
	}
	int ans=1e9;
	for(int i=0;i<(1<<n);++i){
		bool GG=0;
		for(int j=1;j<=n;++j){
			if((i>>j-1)&1){
				C[j]=2;
			}
			else C[j]=1;
		}
		for(int j=1;j<=n;++j)if(c[j]&&C[j]!=c[j])GG=1;
		if(GG)continue;
		for(int i=1;i<=n;++i)F[i]=i;
		for(int i=1;i<=m;++i){
			int x=u[i],y=v[i];
			if(Find(x)!=Find(y)&&C[x]==C[y]){
				F[Find(x)]=Find(y);
			}
		}
		int res=0;
		for(int i=1;i<=n;++i)if(Find(i)==i)res++;
		ans=min(ans,res);
	}
	printf("%lld\n",ans);
	return 0;
}
