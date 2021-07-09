/***************************************************************
    File name: color.cpp
    Author: ljfcnyali
    Create time: 2021年04月03日 星期六 08时02分05秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 5010;
 
int n, m, c[maxn][maxn], A, B, C, D, p; LL ans;
vector<pii> a[100010];
bool vis[maxn][maxn];
 
inline void change(int x, int y)
{
    REP(i, 1, n) REP(j, 1, m) if ( x != i && y != j )
    {
        if ( vis[i][y] && vis[x][j] && !vis[i][j] ) { vis[i][j] = true; change(i, j); }
        if ( vis[i][y] && !vis[x][j] && vis[i][j] ) { vis[x][j] = true; change(x, j); }
        if ( !vis[i][y] && vis[x][j] && vis[i][j] ) { vis[i][y] = true; change(i, y); }
    }
}
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
#endif
    scanf("%d%d%d%d%d%d%d", &n, &m, &A, &B, &C, &D, &p);
    REP(i, 1, n) REP(j, 1, m)
    {
        A = (1ll * A * A * B + 1ll * A * C + D) % p;
        c[i][j] = A; a[A].push_back(pii(i, j));
    }
    REP(o, 0, p - 1) for ( auto it : a[o] ) if ( !vis[it.first][it.second] ) 
    {
        vis[it.first][it.second] = true; ans += o;
        change(it.first, it.second);
    }
    printf("%lld\n", ans);
    return 0;
}
