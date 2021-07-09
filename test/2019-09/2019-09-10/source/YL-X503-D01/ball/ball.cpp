#include<bits/stdc++.h>
using namespace std;
int f[10000005];
int chkmax(int &a,int b){return a<b?a=b,1:0;}
const int p=998244353;
int mxm[10000005];
typedef pair<int,int> pii;
vector<pii> ask[10000005];
#define x first
#define y second
int ans[100005];
int main(){
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	int t;
	scanf("%d",&t);
	int n,m,mxn=0;
	for(int i=1;i<=t;++i){
		scanf("%d%d",&n,&m);
		chkmax(mxm[n],m);
		chkmax(mxn,n);
		ask[n].push_back(make_pair(m,i));
	}
	for(int i=mxn;i;--i)chkmax(mxm[i-1],mxm[i]);
	f[0]=1;
	for(int i=1;i<=mxn;++i){
		for(int j=min(mxm[i],i);j;--j)f[j]=(f[j]+(long long)f[j-1]*(i*2-j))%p;
		//for(int j=1;j<=mxm[i];++j)printf("%d%c",f[j],j==mxm[i]?'\n':' ');
		for(vector<pii>::iterator it=ask[i].begin();it!=ask[i].end();++it)ans[it->y]=f[it->x];
	}
	for(int i=1;i<=t;++i)printf("%d\n",ans[i]);
	
	return 0;
}
