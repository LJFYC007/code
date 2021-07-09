/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年08月14日 星期五 14时35分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, m, a[maxn], num[maxn], g[110][maxn];
bool vis[maxn], use[110][maxn];
double f[110][maxn];
vector<int> p, q, b[110];

inline void DFS(int x, int sum)
{
    if ( x == p.size() ) { vis[sum] = true; return ; }
    DFS(x + 1, sum); DFS(x + 1, sum * p[x]);
}

inline void Solve(int i, int j)
{
    if ( g[i][j] != -1 ) return ;
    if ( !(i & 1) ) 
    {
        bool flag = false;
        if ( num[j] - i > 0 ) { Solve(i + 1, j); flag |= g[i + 1][j]; }
        REP(k, 1, n) if ( a[k] % j != 0 ) 
        { Solve(i + 1, __gcd(a[k], j)); flag |= g[i + 1][__gcd(a[k], j)]; }
        g[i][j] = flag;
    }
    else
    {
        bool flag = true;
        if ( num[j] - i > 0 ) { Solve(i + 1, j); flag &= g[i + 1][j]; }
        REP(k, 1, n) if ( a[k] % j != 0 ) 
        { Solve(i + 1, __gcd(a[k], j)); flag &= g[i + 1][__gcd(a[k], j)]; }
        g[i][j] = flag;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        REP(i, 1, n) { f[i][1] = 0; for ( auto j : q ) f[i][j] = 0; }
        scanf("%d", &n); m = 0; q.clear();
        REP(i, 1, n) { scanf("%d", &a[i]); m = max(m, a[i]); }
        REP(i, 1, m) vis[i] = 0;
        REP(i, 1, n)
        {
            p.clear(); int x = a[i];
            for ( int j = 2; j * j <= x; ++ j ) 
            {
                if ( x % j != 0 ) continue ;
                p.push_back(j); while ( x % j == 0 ) x /= j;
            }
            if ( x > 1 ) p.push_back(x);
            DFS(0, 1); a[i] = 1; for ( auto j : p ) a[i] *= j;
        }
        REP(i, 2, m) if ( vis[i] ) q.push_back(i);
        for ( auto i : q ) { num[i] = 0; REP(j, 1, n) num[i] += (a[j] % i == 0); } 

        REP(i, 1, n) { b[i].clear(); REP(j, 1, m) { use[i][j] = false; g[i][j] = -1; } }
        REP(i, 1, n) if ( i & 1 ) g[i][1] = 0; else g[i][1] = 1;
        for ( auto i : q ) g[n][i] = (n & 1) ? 1 : 0;
        REP(i, 1, n) f[1][a[i]] += 1.0 / n;

        REP(i, 1, n) if ( !use[1][a[i]] ) { use[1][a[i]] = true; b[1].push_back(a[i]); }
        REP(i, 1, n) Solve(1, a[i]);

        REP(i, 1, n - 1) for ( auto j : b[i] )
        {
            if ( num[j] - i > 0 ) 
            {
                if ( !use[i + 1][j] ) { use[i + 1][j] = true; b[i + 1].push_back(j); }
                f[i + 1][j] += f[i][j] * (num[j] - i) / (n - i);
            }
            REP(k, 1, n)
            {
                if ( a[k] % j == 0 ) continue ;
                int x = __gcd(a[k], j);
                if ( !use[i + 1][x] && x != 1 ) { use[i + 1][x] = true; b[i + 1].push_back(x); }
                f[i + 1][x] += f[i][j] / (n - i);
            }
        }

        bool flag = false; REP(i, 1, n) flag |= g[1][a[i]];
        printf("%d ", flag);
        double ans = 0;
        for ( int i = 2; i <= n; i += 2 ) ans += f[i][1];
        if ( n & 1 ) for ( auto i : q ) ans += f[n][i];
        printf("%.4lf\n", ans);
    }
    return 0;
}
