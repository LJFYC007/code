 
#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a);i<=(b);i++)
#define fd(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int maxn=2e6+5;
const int mod=998244353,inv2=mod+1>>1;
inline int upd(int x){
    if(x<0)return x+mod;
    if(x>=mod)return x-mod;
    return x;
}
void add(int &x,const int &y){
    x=upd(x+y); 
}
inline int ksm(int x,int k){
    int ans=1;
    while(k){
        if(k&1)ans=1ll*ans*x%mod;
        x=1ll*x*x%mod;
        k>>=1;
    }
    return ans;
}
int g[maxn][21],s1[maxn][21],s2[maxn][21];
inline void F(int f[maxn][21],int t,int n,int h){
    for(int p=1;p<n;p<<=1)
        for(int k=0;k<n;k+=(p<<1))
            for(int i=k;i<k+p;i++){
                f[i+p][t]=upd(h*f[i][t]+f[i+p][t]); 
            }
}
int a[100][100];
int cnt[maxn];
int inv[21];
int n,m;
void ln(int *b){
    static int a[21];
    fr(i,0,n)a[i]=0;
    fr(i,1,n){
        int ans=0;
        fr(j,1,i-1)add(ans,1ll*j*a[j]%mod*b[i-j]%mod);
        a[i]=upd(b[i]-1ll*ans*inv[i]%mod);  
    }
    fr(i,0,n)b[i]=a[i];
}
void exp(int *a){
    static int b[21];
    fr(i,0,n)b[i]=0;
    b[0]=1;
    fr(i,1,n){
        int ans=0;
        fr(j,1,i)add(ans,1ll*j*a[j]%mod*b[i-j]%mod);
        b[i]=1ll*ans*inv[i]%mod;    
    }
    fr(i,0,n)a[i]=b[i];
}
void mul(int *c,int *a,int *b){
    fr(i,0,n)fr(j,0,n)add(c[i+j],1ll*a[i]*b[j]%mod);
}
void solve(int x){
    fr(i,0,(1<<n)-1){
        if((i>>x)&1)continue;
        fr(j,0,n-1)g[i^(1<<x)][j]=upd(g[i^(1<<x)][j+1]-g[i][j+1]);
        ln(g[i^(1<<x)]);
        fd(j,n,1)g[i^(1<<x)][j]=upd(g[i^(1<<x)][j-1]+g[i][j]);
    }
}
void work(int x){
    static int a[21],b[21],c[21],d[21],e[21];
    fr(i,0,n)a[i]=b[i]=c[i]=d[i]=0;
    fr(i,0,(1<<n)-1){
        if((i>>x)&1)continue;
        fr(j,0,n-1)a[j]=upd(g[i^(1<<x)][j+1]-g[i][j+1]);
        a[0]=0;
        exp(a);
        fr(j,1,n)g[i^(1<<x)][j]=upd(a[j-1]+g[i][j]);
        fr(j,0,n-1)b[j]=upd(s1[i^(1<<x)][j+1]-s1[i][j+1]);
        b[0]=0;
        fr(j,0,n)c[j]=e[j]=0;
        mul(c,a,b);
        fr(j,1,n)s1[i^(1<<x)][j]=upd(c[j-1]+s1[i][j]);
        fr(j,0,n-1)d[j]=upd(s2[i^(1<<x)][j+1]-s2[i][j+1]);
        d[0]=0;
        mul(e,a,d);mul(e,b,c);
        fr(j,1,n)s2[i^(1<<x)][j]=upd(e[j-1]+s2[i][j]);
    }
}
void clear(){
    fr(i,1,n)fr(j,1,n)a[i][j]=0;
    fr(i,0,(1<<n)-1)fr(j,0,n)g[i][j]=s1[i][j]=s2[i][j]=0;
}
int main(){
    freopen("B.in","r",stdin);
    freopen("B.out","w",stdout);
    int T;cin>>T;
    inv[0]=1;
    fr(i,1,20)inv[i]=ksm(i,mod-2);
    fr(i,1,(1<<17)-1)cnt[i]=cnt[i>>1]+(i&1);
    while(T--){
        scanf("%d%d",&n,&m);
        clear();
        fr(i,1,m){
            int x,y;scanf("%d%d",&x,&y);
            a[x][y]=a[y][x]=1;
        }
        if(n==1){
            cout<<0<<'\n';
            continue;
        }
        fr(i,1,(1<<n)-1){
            g[i][cnt[i]]=1;
            fr(j,1,n)if((i>>j-1)&1){
                fr(k,j+1,n)if(((i>>k-1)&1)&&a[j][k]){
                    g[i][cnt[i]]=1ll*g[i][cnt[i]]*2%mod;
                }
            }
        }
        fr(i,1,n)F(g,i,1<<n,1);
        fr(i,1,(1<<n)-1){
            ln(g[i]);
        }
        fr(i,0,n-1)solve(i);
        fr(i,0,(1<<n)-1)fr(j,0,n)s1[i][j]=g[i][j];
 
        fd(i,n-1,0)work(i);
 
        F(s1,n,1<<n,-1);
        F(s2,n,1<<n,-1);
        fr(i, 0, (1 << n) - 1) printf("%d ", (s1[i][n] + mod) % mod); puts("");
        fr(i, 0, (1 << n) - 1) printf("%d ", (s2[i][n] + mod) % mod); puts("");
        cout<<upd(s1[(1<<n)-1][n]+1ll*s2[(1<<n)-1][n]*inv2%mod)<<'\n';
    }
    return 0;
}
