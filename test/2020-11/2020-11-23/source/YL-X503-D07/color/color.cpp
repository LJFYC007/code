/***************************************************************
	File name: color.cpp
	Author: ljfcnyali
	Create time: 2020年11月23日 星期一 09时41分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, num, ans[210][10010], a[210];
bool vis[210];
vector<pii> p[210];

int main()
{
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    scanf("%d%d", &n, &m);
    if ( m > n * (2 * n - 1) ) { puts("-1"); return 0; }
    REP(i, 0, 2 * n - 2) 
    {
        mem(vis);
        REP(j, 0, 2 * n - 2) 
        {
            int x = i - j;
            if ( x < 0  ) x += 2 * n - 1;
            if ( j < x ) { vis[j] = vis[x] = true; p[i].push_back(pii(j, x)); }
        }
        REP(j, 0, 2 * n - 2) if ( !vis[j] ) p[i].push_back(pii(j, 2 * n - 1));

        REP(x, 1, n)
        {
            ++ num; if ( num > m ) goto Next ;
            for ( auto it : p[i] ) 
            {
                ans[it.first + 1][num] = ans[it.second + 1][num] = x;
                ++ x; if ( x > n ) x -= n;
            }
        }
    }

Next : ;
    REP(i, 1, n + n) { REP(j, 1, m) printf("%d ", ans[i][j]); puts(""); }
    return 0;
}
