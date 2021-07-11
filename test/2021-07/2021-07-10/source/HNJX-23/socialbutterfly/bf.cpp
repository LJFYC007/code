#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>

const int maxn = 21;

int n, m, lim, a[maxn][maxn];

int main()
{
    freopen("socialbutterfly.in", "r", stdin);
    freopen("socialbutterfly1.out", "w", stdout);
    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        memset(a, 0, sizeof(a));
    scanf("%d%d%d", &n, &m, &lim);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); ++ a[u][v]; ++ a[v][u]; }
    REP(i, 1, (1 << n) - 1) 
    {
        int ret = lim;
        REP(j, 1, n) if ( (i >> j - 1) & 1 )
        {
            REP(k, j + 1, n) if ( (i >> k - 1) & 1 )
                ret += a[j][k];
            ret -= lim;
        }
        if ( ret > 0 ) { puts("Yes"); goto Finish; }
    }
    puts("No");
Finish : ;
    }
    return 0;
}