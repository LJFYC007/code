#include<bits/stdc++.h>
#define int long long
using namespace std;
const int ha=998244353;
int n,p;
vector<int> to[1000005];
int inv[1000005];
int fpm(int a,int b){
//	fprintf(stderr,"%d^%d\n",a,b);
	int c=1;
	for(;b;b>>=1,a=a*a%ha)if(b&1)c=c*a%ha;
	return c;
}
int siz[1000005];
int w,ans;
void dfs(int x,int f){
	siz[x]=1;
	for(vector<int>::iterator i=to[x].begin();i!=to[x].end();++i)if(*i!=f){
		dfs(*i,x);
		siz[x]+=siz[*i];
	}
	w=w*(inv[siz[x]]*p%ha+1)%ha;
}
void DFS(int x,int f){
//	fprintf(stderr,"%d\n",x);
	ans=(ans+w)%ha;
	int ow=w;
//	fprintf(stderr,"%d\n",x);
	for(vector<int>::iterator i=to[x].begin();i!=to[x].end();++i)if(*i!=f){
		
		w=w*(inv[n-siz[*i]]*p%ha+1)%ha*fpm((inv[siz[*i]]*p%ha+1),ha-2)%ha;
		
		DFS(*i,x);
		w=ow;
	}
	
}
signed main(){
	freopen("treap.in","r",stdin);
	freopen("treap.out","w",stdout);
	scanf("%lld%lld",&n,&p);
	--p;
	inv[1]=1;
	for(int i=2;i<=n;++i)inv[i]=(ha-ha/i)*inv[ha%i]%ha;
	int u,v;
	for(int i=1;i<n;++i){
		scanf("%lld%lld",&u,&v);
		to[u].push_back(v);
		to[v].push_back(u);
	}
	
	w=1;
	dfs(1,0);
	DFS(1,0);
	printf("%lld\n",ans*inv[n]%ha);
	return 0;
}
