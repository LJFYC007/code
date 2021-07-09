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
	f[0]=1;
	for(int i=1;i<=100;++i){
		for(int j=i;j;--j)f[j]=(f[j]+(long long)f[j-1]*(i*2-j))%p;
		for(int j=1;j<=i;++j)printf("%d%c",f[j],j==i?'\n':' ');
	}
	
	return 0;
}
