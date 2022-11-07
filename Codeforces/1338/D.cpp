/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2020年04月14日 星期二 20时50分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, f[maxn][2], ans;
vector<int> Edge[maxn];

inline void DFS(int u, int fa)
{
    for ( auto v : Edge[u] )
    {
        if ( v == fa ) continue ;
        DFS(v, u);
        ans = max(ans, f[u][1] + f[v][0] + 1);
        ans = max(ans, f[u][0] + max(f[v][1], f[v][0]) + (int)Edge[u].size() - 2);
        f[u][0] = max(f[u][0], max(f[v][1], f[v][0]));
        f[u][1] = max(f[u][1], f[v][0]);
    }
    ++ f[u][1];
    if ( Edge[u].size() > 1 ) f[u][0] += Edge[u].size() - 2;
    ans = max(ans, max(f[u][0], f[u][1]));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); Edge[u].push_back(v); Edge[v].push_back(u); }
    DFS(1, 0);
    printf("%d\n", ans);
    return 0;
}
