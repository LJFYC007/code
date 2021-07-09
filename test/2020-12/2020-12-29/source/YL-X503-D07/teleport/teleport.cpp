/***************************************************************
  File name: teleport.cpp
Author: ljfcnyali
Create time: 2020年12月29日 星期二 10时24分28秒
 ***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int INF = 1e18;

int n, k, son[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn], fa[maxn];
int dis[maxn], f[maxn][maxn][22], anc[maxn], tot;

inline void add(int u, int v, int w) { fa[v] = u; To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

inline void DFS(int u)
{
    anc[++ tot] = u; REP(i, 1, tot - 1) REP(j, 0, k) f[u][anc[i]][j] = INF;
    for ( int c = Begin[u]; c; c = Next[c] ) { int v = To[c]; dis[v] = dis[u] + W[c]; DFS(v); }
    REP(i, (u == 1 ? 1 : 2), tot - 1) REP(j, 0, k) for ( int c = Begin[u]; c; c = Next[c] )
    {
        int v1 = To[c];// sum = (j >= 1 ? dis[u] - dis[anc[i]] : 0); 
        int s0=0LL,s1=dis[u]-dis[anc[i]];
        for ( int d = Begin[u]; d; d = Next[d] ) 
        {
            int v = To[d];
            int tmp=(u == 1 ? INF : f[v][anc[i]][j]);
            s0+=tmp;
            if(j){
                tmp=min(tmp,f[v][u][j-1]);
                if ( v == v1 ){
                    s1+=min(tmp,(u == 1 ? INF : f[v][anc[i]][j])-(dis[u]-dis[anc[i]]));
                //  sum += (j >= 1 ? f[v][u][j] : f[v][anc[i]][0]);
                }else{
                    s1+=tmp;
                }
            }
           // else sum += min((j >= 1 ? f[v][u][j - 1] : INF), (u == 1 ? INF : f[v][anc[i]][j]));
        }
        f[u][anc[i]][j] = min(f[u][anc[i]][j], min(s0,j?s1:INF));
        // if ( u == 3 && j == 1 && i == tot - 1 ) cout << sum << " " << v1 << endl;
    }
    if ( !son[u] ) REP(i, 1, tot - 1) REP(j, 0, k) f[u][anc[i]][j] = dis[u] - dis[anc[i]];
    -- tot;
}

signed main()
{
    freopen("teleport.in", "r", stdin);
    freopen("teleport.out", "w", stdout);
    scanf("%lld%lld", &n, &k);
    REP(i, 2, n) { int f, w; scanf("%lld%lld", &f, &w); add(f, i, w); ++ son[f]; }
    anc[++ tot] = n + 1; DFS(1); REP(i, 1, k) printf("%lld\n", f[1][n + 1][i]);
    return 0;
}
