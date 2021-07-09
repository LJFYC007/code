#include<cstdio>
using namespace std;
#define rep(i,n) for(int i=1;i<=n;i++)
const int N=6e5+10;
const int P1=31,D1=1000173169;
const int P2=37,D2=998244353;
int mypow(int x,int n,int MOD){int ans=1;for(;n;n>>=1,x=1ll*x*x%MOD)if(n&1)ans=1ll*ans*x%MOD;return ans;}
struct HashValue
{
    int h1,h2;
    friend HashValue operator*(const HashValue&a,int b){return {(int)(1ll*a.h1*b%D1),(int)(1ll*a.h2*b%D2)};}
    friend HashValue operator*(const HashValue&a,const HashValue&b){return {(int)(1ll*a.h1*b.h1%D1),(int)(1ll*a.h2*b.h2%D2)};}
    friend HashValue operator+(const HashValue&a,const HashValue&b){return {(a.h1+b.h1)%D1,(a.h2+b.h2)%D2};}
    friend HashValue operator-(const HashValue&a,const HashValue&b){return {(a.h1-b.h1+D1)%D1,(a.h2-b.h2+D2)%D2};}
    friend bool operator==(const HashValue&a,const HashValue&b){return a.h1==b.h1&&a.h2==b.h2;}
}pw[N],inv[N],f[N];
int ans[N],a[N],n,m;
bool ban[N];
HashValue get(int l,int r){return (f[r]-f[l-1])*inv[l];}
int main()
{
	freopen("reverse.in", "r", stdin);
	freopen("reverse.out", "w", stdout);
    HashValue base={P1,P2},inv_base={mypow(P1,D1-2,D1),mypow(P2,D2-2,D2)};
    pw[0]={1,1};inv[0]={1,1};
    rep(i,N-1)pw[i]=pw[i-1]*base,inv[i]=inv[i-1]*inv_base;
    int T;scanf("%d",&T);
    rep(Cas,T)
    {
        scanf("%d%d",&n,&m);
        rep(i,n)scanf("%d",&a[i]),ban[i]=0;
        rep(i,m){int x;scanf("%d",&x);ban[x]=1;}
        int l=n+1,r=n,lastl=n+1,lastr=r;
        rep(i,2*n+1)f[i-1]={0,0};
        rep(i,n)
        {
            r++;ans[r]=a[i];
            f[r]=f[r-1]+pw[r]*a[i];
            l--;ans[l]=a[i];
            f[l-1]=f[l]-pw[l]*a[i];
            if(!ban[i])
            {
                int L=0,R=r-lastl+2;
                for(;L<R-1;)
                {
                    int mid=(L+R)>>1;
                    if(get(l,l+mid-1)==get(lastl,lastl+mid-1))L=mid;else R=mid;
                }
                if(L==r-lastl+1||ans[l+L]<ans[lastl+L])r=lastr;else l=lastl;
                lastl=l;lastr=r;
            }
        }
        l=lastl;
        int bs=1,ANS=0;
        for(int i=l;i<=r;i++)ANS=(ANS+1ll*ans[i]*bs)%998244353,bs=1ll*bs*37%998244353;
        printf("%d\n", ANS);
    }
    return 0;
}
