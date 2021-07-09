/***************************************************************
    File name: P3469.cpp
    Author: ljfcnyali
    Create time: 2019年06月07日 星期五 11时02分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

LL Begin[maxn], Next[maxn], To[maxn], e;
LL dfn[maxn], low[maxn], p[maxn], cut[maxn], size[maxn];
LL n, m, cnt;
vector<LL> s[maxn];

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

inline void Tarjan(int u)
{
    dfn[u] = low[u] = ++ cnt; size[u] = 1; int son = 0, sum = 0;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        if ( !dfn[v] ) 
        {
            Tarjan(v); size[u] += size[v]; ++ son;
            low[u] = min(low[u], low[v]);
            if ( (u == 1 && son > 1) || (u != 1 && dfn[u] <= low[v]) ) 
            {
                cut[u] = 1;
                s[u].push_back(size[v]);
                sum += size[v];
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
    if ( cut[u] == 1 ) s[u].push_back(n - 1 - sum);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    Tarjan(1);
    REP(i, 1, n)
    {
        if ( !cut[i] ) printf("%d\n", (n - 1) * 2);
        else
        {
            LL ans = (n - 1) * 2;
//            REP(j, 0, s[i].size() - 1) printf("%d ", s[i][j]);
            REP(j, 0, s[i].size() - 1) ans += s[i][j] * (n - 1 - s[i][j]);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
