/**************************************************************
    Problem: 3919
    User: 2016gdgzoi635
    Language: C++
    Result: Accepted
    Time:740 ms
    Memory:85560 kb
****************************************************************/
 
 
#include<bits/stdc++.h>
using namespace std;
const int Mod=998244353;
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
typedef long long ll;
typedef pair<int,int> pii;
int n;
#define Maxn 500010
#define cout cerr
#define FR first
#define SE second
int head[Maxn],v[Maxn<<1],w[Maxn<<1],nxt[Maxn<<1],tot=0;
int deg[Maxn];
 
namespace modular{
    int add(int a,int b){return a+b>=Mod?a+b-Mod:a+b;}
    int dec(int a,int b){return a-b<0?a-b+Mod:a-b;}
    int mul(int a,int b){return 1ll*a*b%Mod;}
    inline int Fast_Pow(int a,int b){
        int res=1;
        while(b){
            if(b&1)res=1ll*res*a%Mod;
            a=1ll*a*a%Mod;
            b>>=1;
        }
        return res;
    }
}using namespace modular;
 
void add_edge(int s,int e,int t){
    deg[s]++;deg[e]++;
    tot++;v[tot]=e;w[tot]=t;nxt[tot]=head[s];head[s]=tot;
    tot++;v[tot]=s;w[tot]=t;nxt[tot]=head[e];head[e]=tot;
}
 
ll D[Maxn];int Ans=0;
void dfs(int u,int f){
    D[u]=1ll*deg[u]*(deg[u]-1)/2;
    for(int i=head[u];i;i=nxt[i])
        if(v[i]^f){
            dfs(v[i],u);
            D[u]+=D[v[i]];
        }
    for(int i=head[u];i;i=nxt[i])Ans=add(Ans,mul(deg[u]-1,w[i]));
}
pii Add(pii a,pii b){return pii(add(a.FR,b.FR),add(a.SE,b.SE));}
pii Dec(pii a,pii b){return pii(dec(a.FR,b.FR),dec(a.SE,b.SE));}
int merge(pii a,pii b){return add(mul(a.FR,b.SE),mul(a.SE,b.FR));}
pii F[Maxn];
pii seq[Maxn];int rk[Maxn<<1];int sum[Maxn];
pii val[Maxn];
int cnt;
void calc(int u){
    cnt=0;
    for(int i=head[u];i;i=nxt[i])seq[++cnt]=pii(w[i],i);
    sort(seq+1,seq+cnt+1);
    rep(i,1,cnt){
        rk[seq[i].SE]=i;
        sum[i]=add(sum[i-1],seq[i].FR%Mod);
        val[u].SE=add(val[u].SE,mul(seq[i].FR,cnt-i));
    }
    val[u].FR=1ll*deg[u]*(deg[u]-1)/2%Mod;
    Ans=add(Ans,mul(dec(val[u].FR,1),val[u].SE));
    int tmp=0;
    rep(i,1,cnt){
        int cur=add(tmp,mul(cnt-i,seq[i].FR));
        if(cnt>2){
            Ans=dec(Ans,mul(cur,cnt-2));
        }
        tmp=add(tmp,seq[i].FR%Mod); 
    } 
}
void gao(int u,int f){
    for(int i=head[u];i;i=nxt[i])
        if(v[i]^f){
            ll x=D[1]-D[v[i]],y=D[v[i]];
            x-=(deg[u]-1);y-=(deg[v[i]]-1);
            x%=Mod;y%=Mod;
            Ans=add(Ans,mul(mul(x,y),2*w[i]%Mod));
            gao(v[i],u);
        }
    calc(u); 
    pii tmp=val[u];
    for(int i=head[u];i;i=nxt[i]){
        if(v[i]^f){
            Ans=dec(Ans,mul(mul(deg[u]-1,deg[v[i]]-1),2*w[i]%Mod));
            pii cur=Add(Dec(val[u],pii(deg[u]-1,add(sum[rk[i]-1],mul(cnt-rk[i],w[i])))),pii(deg[u]-1,mul(deg[u]-1,w[i])));
            cur=Add(cur,F[u]);
            Ans=add(Ans,merge(cur,F[v[i]]));
            F[u]=Add(F[u],F[v[i]]);
        }else{
            pii cur=Add(Dec(val[u],pii(deg[u]-1,add(sum[rk[i]-1],mul(cnt-rk[i],w[i])))),pii(deg[u]-1,mul(deg[u]-1,w[i])));
            tmp=cur;
        }
    }
    F[u]=Add(F[u],tmp);
}
 
 
inline void rd(int &x){
    x=0;char ch=getchar();int f=1;
    while(ch<'0'||ch>'9'){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    x*=f;
}
 
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
    rd(n);
    int s,e,t;
    rep(i,1,n-1){
        rd(s);rd(e);rd(t);
        add_edge(s,e,t);
    }
    dfs(1,0);
    if(D[1])Ans=mul(Ans,(D[1]-1)%Mod);int pre=Ans;
    gao(1,0);
    Ans=dec(Ans,pre);Ans=mul(Ans,2);Ans=add(Ans,pre);
    printf("%d\n",Ans);
    return 0;
}
