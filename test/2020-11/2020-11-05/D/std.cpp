#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,r,l) for(int i=(r);i>=(l);--i)
using namespace std;
const int N=210,P=998244353;
int n,m,e[N][N],a[N],p[N],u,v,id[N],s[N],f[N];
inline int ksm(int a,int b){
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%P) if(b&1) ans=1ll*ans*a%P;
    return ans;
}
inline void upd(int &x,int y){((x+=y)>=P)&&(x-=P);}
int gauss(){
    int ans=1;
    rep(i,1,n){
        int r=i;
        if(a[i]==1){
            rep(j,i,n) if((e[j][i]+p[j])%P&&a[j]==1){r=j;break;}
        }
        if(!(1ll*e[r][i]*a[i]+p[r])%P) return 0;
        if(r!=i){rep(j,1,n) swap(e[i][j],e[r][j]);swap(p[i],p[r]);ans=P-ans;}
        ans=1ll*ans*ksm(p[i],a[i]-1)%P*(1ll*e[i][i]*a[i]%P+p[i])%P;
        int inv=ksm((1ll*e[i][i]*a[i]+p[i])%P,P-2);
        rep(j,i+1,n){
            int x=1ll*inv*e[j][i]%P;
            rep(k,i,n) upd(e[j][k],P-1ll*x*e[i][k]%P*a[i]%P);
        }
    }
    return ans;
}
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
    scanf("%d%d",&n,&m);
    rep(i,1,n) scanf("%d",s+i),id[i]=i;
    sort(id+1,id+n+1,[&](int x,int y){return s[x]<s[y];});
    rep(i,1,n) a[i]=s[id[i]],f[id[i]]=i;
    rep(i,1,m){
        scanf("%d%d",&u,&v);u=f[u],v=f[v];
        upd(e[u][v],P-1);upd(e[v][u],P-1);
        upd(p[u],a[v]);upd(p[v],a[u]);
    }
    if(a[n]==1) --n;
    else if(a[n]==2){    
        rep(j,1,n) if(a[j]==2){--a[j];break;}
    }
    else --a[n];
    printf("%d\n",gauss());
    return 0;
}
