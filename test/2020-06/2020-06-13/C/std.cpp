/***************************************************************
    File name: C.cpp
    Author: huhao
    Create time: Sat 13 Jun 2020 03:04:19 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
int read()
{
    int r=0,t=1,c=getchar();
    while(c<'0'||c>'9')
    {
        t=c=='-'?-1:1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        r=r*10+c-48;
        c=getchar();
    }
    return r*t;
}
const int N=410;
int n,m;
namespace edge
{
    int begin[N],next[N<<1],to[N<<1],e;
    void add(int u,int v){ e++; next[e]=begin[u]; begin[u]=e; to[e]=v; }
}
#define fo(i,a) for(int i=edge::begin[a];i;i=edge::next[i])
#define i64 long long
const int mod=1000000009;
namespace C
{
    i64 c[N][N];
    void init(int n)
    {
        fr(i,0,n) c[i][0]=c[i][i]=1;
        fr(i,1,n) fr(j,1,i-1) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
    }
}
using C::c;
namespace m_mul_2_le_n
{
    using ::edge::to;
    int w[N],f[N],d[N];
    void dfs(int u,int F)
    {
        f[u]=F; w[u]=1;
        fo(i,u) if(to[i]!=F){ dfs(to[i],u); w[u]+=w[to[i]]; }
    }
    i64 solve(int u)
    {
        i64 ans=1; w[u]--;
        fo(i,u) if(to[i]!=f[u])
        {
            ans=ans*c[w[u]][w[to[i]]]%mod; w[u]-=w[to[i]];
            ans=ans*solve(to[i])%mod;
        }
        return ans;
    }
    int main()
    {
        int u=0,v=0;
        fr(i,1,n) fo(j,i){ d[i]++; }
        fr(i,1,n) fr(j,1,i-1)
        {
            dfs(i,0); if(w[j]!=m) continue;
            dfs(j,0); if(w[i]!=m) continue;
            int o=f[i],flag=1;
            while(o!=j)
            {
                if(d[o]!=2) flag=0;
                o=f[o];
            }
            if(flag){ u=i; v=j; break; }
        }
        if(u)
        {
            i64 ans=2;
            dfs(u,0); ans*=solve(v);
            dfs(v,0); ans*=solve(u);
            printf("%lld\n",ans%mod);
        }
        else printf("0\n");
        return 0;
    }
}
namespace m_mul_2_gt_n
{
    using ::edge::to;
    int w[N],dfn[N],Dfn,mw[N],id[N];
    i64 g[N];
    int f[N][N/2][N/2];
    void dfs(int u,int F)
    {
        w[u]=1; mw[u]=0; id[dfn[u]=Dfn=(Dfn==n?1:Dfn+1)]=u;
        fo(i,u) if(to[i]!=F){ dfs(to[i],u); w[u]+=w[to[i]]; mw[u]=std::max(mw[u],w[to[i]]); }
        mw[u]=std::max(mw[u],n-w[u]);
    }
    i64 solve(int u,int F)
    {
        i64 &ans=g[u]=1; w[u]--;
        fo(i,u) if(to[i]!=F)
        {
            ans=ans*c[w[u]][w[to[i]]]%mod; w[u]-=w[to[i]];
            ans=ans*solve(to[i],u)%mod;
        }
        return ans;
    }
    inline int Mod(int a){ return a>=mod?a-mod:a; }
    inline int &Add(int &a,int b){ return a=Mod(a+b); }
    int main()
    {
        dfs(1,0);
        int r=1;
        fr(i,2,n) if(mw[i]<mw[r]) r=i;
        dfs(r,0); solve(r,0); dfs(r,0); f[2][0][0]=1;
        fr(i,2,n) fr(j,0,n-m) fr(k,0,n-m) if(f[i][j][k])
        {
            i64 F=f[i][j][k];
            Add(f[i+1][j][k],F);
            if(j+w[id[i]]<=n-m) Add(f[i+w[id[i]]][j+w[id[i]]][k],F*c[j+w[id[i]]][j]%mod*g[id[i]]%mod);
            if(k+w[id[i]]<=n-m) Add(f[i+w[id[i]]][j][k+w[id[i]]],F*c[k+w[id[i]]][k]%mod*g[id[i]]%mod);
        }
        i64 ans=f[n+1][n-m][n-m];
        fr(i,1,n-(n-m)-(n-m)) ans=ans*i%mod;
        printf("%lld\n",ans);
        return 0;
    }
}
int main()
{
    freopen("C.in", "r", stdin);
    freopen("C1.out", "w", stdout);
    using edge::add;
    n=read(); m=read(); C::init(n);
    fr(i,1,n-1){ int u=read(),v=read(); add(u,v); add(v,u); }
    if(m+m<=n) return m_mul_2_le_n::main();
    return m_mul_2_gt_n::main();
}
