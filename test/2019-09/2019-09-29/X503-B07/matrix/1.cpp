/**************************************************************
	File name: matrix.cpp
	Author: ljfcnyali
	Create time: 2019年09月29日 星期日 09时16分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 20;

int T, a[maxn][maxn], sum[maxn][maxn];
int n, m, k1, k2, k3, ans;

namespace Subtask1 
{
    int _In(int x, int y, int xx, int yy, int X, int Y)
    {
	    return x <= X && X <= xx && y <= Y && Y <= yy;
    }

    int In(int x, int y, int X, int Y, int k, int K)
    {
	    return _In(x - k + 1, y - k + 1, x, y, X, Y) || 
            _In(x - k + 1, y - k + 1, x, y, X - K + 1, Y) ||
            _In(x - k + 1, y - k + 1, x, y, X, Y - K + 1) ||
            _In(x - k + 1, y - k + 1, x, y, X - K + 1, Y - K + 1);
    } 

    int S(int X, int Y, int k)
    {
	    return sum[X][Y] - sum[X - k][Y] - sum[X][Y - k] + sum[X - k][Y - k];
    }

    inline void Solve()
    {
        REP(i1, k1, n)
            REP(j1, k1, m)
                REP(i2, k2, n)
                    REP(j2, k2, m)
						if ( !In(i1, j1, i2, j2, k1, k2) && !In(i2, j2, i1, j1, k2, k1) )
                            REP(i3, k3, n)
                                REP(j3, k3, m)
									if ( !In(i1, j1, i3, j3, k1, k3) && !In(i3, j3, i1, j1, k3, k1) &&
                                         !In(i2, j2, i3, j3, k2, k3) && !In(i3, j3, i2, j2, k3, k2) )
										ans = max(ans, S(i1, j1, k1) + S(i2, j2, k2) + S(i3, j3, k3));
        printf("%lld\n", ans);
    }
}

signed main()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    int T; scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld%lld%lld%lld", &n, &m, &k1, &k2, &k3);
        mem(a); mem(sum);
        ans = -INF;
        REP(i, 1, n) REP(j, 1, m) 
        {
            scanf("%lld", &a[i][j]);
            sum[i][j] = a[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
        Subtask1 :: Solve();
    }
    return 0;
}
