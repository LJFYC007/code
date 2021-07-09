#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define REP(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define DREP(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
#define EREP(i,u) for(int i=start[u];i;i=e[i].next)
#define fi first
#define se second
#define mkr(a,b) make_pair(a,b)
#define SZ(A) ((int)A.size())
template<class T>inline void chkmax(T &a,T b){ if(a<b)a=b;}
template<class T>inline void chkmin(T &a,T b){ if(a>b)a=b;}
inline int read()
{
    int s=0,f=1; char ch=getchar();
    while(!isdigit(ch) && ch!='-')ch=getchar();
    if(ch=='-')ch=getchar(),f=-1;
    while(isdigit(ch))s=s*10+ch-'0',ch=getchar();
    return ~f?s:-s;
}

const int maxn=2e5+20;
const int mod=998244353;

int n,m,a[1020];
int inv[maxn];

inline void init()
{
    inv[1]=1;
    REP(i,2,2e5)inv[i]=(ll)(mod-mod/i)*inv[mod%i]%mod;
    
    n=read();
    REP(i,1,n)a[i]=read(),m+=a[i];
}

int dp[maxn],g[maxn];
inline void pls(int &a,int b){ a+=b; a-=a>=mod?mod:0;}

inline void doing()
{
    dp[0]=1;
    REP(i,1,n)DREP(j,m,0)if(j>=a[i])
 	pls(dp[j],(ll)(mod-dp[j-a[i]])%mod);
    int ans=0;
    REP(i,1,n)
    {
	int x=a[i];
	REP(j,0,m)g[j]=(dp[j]+(j>=x?(ll)g[j-x]%mod:0))%mod;
	int t=1;
	REP(j,1,n)if(i!=j)t=(ll)t*inv[a[j]]%mod;
	REP(j,0,m)if(g[j])
	{
	    int xs=(ll)inv[j+a[i]]*g[j]%mod*t%mod*a[i]%mod;
	    ans=(ans+xs)%mod;
	}
    }
    ans=(ans+mod)%mod;
    printf("%d\n",ans);
}

int main()
{	freopen("restaurant.in","r",stdin);
	freopen("restaurant.out","w",stdout);
    init();
    doing();
    return 0;
}
