/***************************************************************
    File name: tearssp.cpp
    Author: huhao
    Create time: Fri 02 Apr 2021 10:36:54 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define i64 long long
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
#include<array>
#define pii std::pair<int,int>
const int N=200010,L=18,W=300,M=N/W+2;
int n,q,R, num = 0;
int d[N],f[N][L+2],a[N];
i64 D[N];
std::vector<pii> e[N];
void dfs(int u)
{
    d[u]=d[f[u][0]]+1;
    for(auto v:e[u]) if(v.first!=f[u][0]){ D[v.first]=D[u]+v.second; f[v.first][0]=u; dfs(v.first); }
}
inline void Min(i64 &u,i64 v){ if(u>v) u=v; }
int vis[M][N],t[M]; i64 mi[M];
int id[M][W+10];
int cnt[M];
void update(int i,int u)
{
//  if((++cnt[i])%10000==0) fprintf(stderr,"%d %d\n",i,cnt[i]);
    if(vis[i][u]<=0) return ;
    int v=f[u][0]; int p=vis[i][u]; int q=id[i][0]; vis[i][u]=-1; Min(mi[i],D[v]);
//  if(p<0||q<0||p>q) exit(1);
//  printf("%d %d   %d %d\n",i,u,p,q); fflush(stdout);
    if(!vis[i][v]){ vis[i][v]=p; id[i][p]=v; }
    else
    {
        vis[i][id[i][q]]=(p==q?-1:p); std::swap(id[i][p],id[i][q]); id[i][0]--;
    }
}
int main()
{
 freopen("tearssp.in","r",stdin); freopen("tearssp.out","w",stdout);
    n=read(); q=read(); R=read();
    fr(i,1,n-1){ int u=read(),v=read(),w=read(); e[u].push_back({v,w}); e[v].push_back({u,w}); }
    dfs(R); f[R][0]=R; fr(j,1,L) fr(i,1,n) f[i][j]=f[f[i][j-1]][j-1];
    fr(i,0,n-1) a[i]=read();
    fr(i,0,(n-1)/W)
    {
        int l=i*W,r=std::min((i+1)*W,n)-1; mi[i]=1ll<<60;
        fr(j,l,r)
        {
            if(!vis[i][a[j]]){ id[i][++id[i][0]]=a[j]; vis[i][a[j]]=id[i][0]; }
            Min(mi[i],D[a[j]]);
        }
    }
    while(q--)
    {
        int op=read(),L=read()-1,R=read()-1;
        if(op==1)
        {
            fr(x,L/W,R/W)
            {
                int l=x*W,r=std::min((x+1)*W,n)-1;
                if(L<=l&&r<=R)
                {
                    t[x]++; static int a[N];
                    fr(i,0,id[x][0]) a[i]=id[x][i];
                    fr(i,1,a[0]) update(x,a[i]);
                }
                else
                {
                    for(int i=0;t[x];t[x]>>=1,i++) if(t[x]&1) fr(j,l,r) { a[j]=f[a[j]][i]; ++ num; }
                    fr(i,std::max(l,L),std::min(r,R)){ update(x,a[i]); a[i]=f[a[i]][0]; }
                }
            }
        }
        else
        {
            i64 ans=1ll<<60;
            fr(x,L/W,R/W)
            {
                int l=x*W,r=std::min((x+1)*W,n)-1;
                if(L<=l&&r<=R) Min(ans,mi[x]);
                else
                {
                    for(int i=0;t[x];t[x]>>=1,i++) if(t[x]&1) fr(j,l,r) { a[j]=f[a[j]][i]; ++ num; }
                    fr(i,std::max(l,L),std::min(r,R)) Min(ans,D[a[i]]);
                }
            }
            printf("%lld\n",ans);
        }
    }
	printf("%lld\n", num);
    return 0;
}
