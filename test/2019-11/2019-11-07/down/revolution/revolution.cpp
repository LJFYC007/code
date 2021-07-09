#pragma GCC optimize(2)
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e3+10;
const int mod=998244353;
int n,p[N][4],w[4][4],pre[N][N],suf[N][N],ans[N];
int main(){
	freopen("revolution.in","r",stdin);
    freopen("revolution.out","w",stdout);
	scanf("%d",&n);
    for(int i=1;i<=n;i++)
    for(int j=0;j<4;j++)
    scanf("%d",&p[i][j]);
    for(int i=0;i<4;i++)
    for(int j=0;j<4;j++)
    scanf("%d",&w[i][j]);
    pre[0][0]=suf[n+1][0]=1;
    for(int mx=0;mx<4;mx++){
        for(int i=1;i<=n;i++)
        for(int j=0;j<=i;j++){
            pre[i][j]=1ll*pre[i-1][j]*(1-p[i][mx]+mod)%mod;
            if(j)pre[i][j]=(pre[i][j]+1ll*p[i][mx]*pre[i-1][j-1]%mod)%mod;
        }
        for(int i=n;i;i--)
        for(int j=0;j<=n-i+1;j++){
            suf[i][j]=1ll*suf[i+1][j]*(1-p[i][mx]+mod)%mod;
            if(j)suf[i][j]=(suf[i][j]+1ll*p[i][mx]*suf[i+1][j-1]%mod)%mod;
        }
        for(int i=1;i<=n;i++)
        for(int j=n-i;~j;j--)
        suf[i][j]=(suf[i][j]+suf[i][j+1])%mod;
        for(int i=1;i<=n;i++)
        for(int j=0;j<i;j++)
        for(int k=0;k<4;k++)
        ans[i]=(ans[i]+1ll*pre[i-1][j]*p[i][k]%mod*w[mx][k]%mod*suf[i+1][max(0,n/2+1-j-(mx==k))]%mod)%mod;
    }
    for(int i=1;i<=n;i++)
    printf("%d\n",ans[i]);
    return 0;
}
