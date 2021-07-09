/***************************************************************
	File name: landmine.cpp
	Author: ljfcnyali
	Create time: 2020年11月26日 星期四 10时35分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int n, p[maxn], q[maxn], r[maxn], s[maxn], f[1 << 20];
int a[maxn];

inline int sqr(int x) { return x * x; }

namespace Subtask1
{
    int f[maxn][maxn];

    inline int get(int x, int y, int z)
    {
        int val = sqr(p[x] - q[y]) + sqr(p[y] - r[z]) + sqr(p[z]);
        return val;
    }

    inline int main()
    {
        REP(i, 1, n) f[i][i] = get(i - 1, i, i + 1);
        REP(len, 2, n) REP(i, 1, n - len + 1)
        {
            int j = i + len - 1;
            f[i][j] = max(f[i][j], f[i][j - 1] + get(i - 1, j, j + 1));
            f[i][j] = max(f[i][j], f[i + 1][j] + get(i - 1, i, j + 1));
            REP(k, i, j - 2) f[i][j] = max(f[i][j], f[i][k] + f[k + 2][j] + get(i - 1, k + 1, j + 1));
        }
        printf("%d\n", f[1][n]);
        return 0;
    }
}

namespace Subtask2
{
    const int maxn = 80;
    int f[maxn][maxn][maxn][maxn];

    inline int get(int x, int y, int z, int t)
    {
        int val = sqr(p[x] - q[y]) + sqr(p[y] - r[z]) + sqr(p[z] - s[t]);
        return val;
    }

    inline int main()
    {
        // REP(i, 1, n) REP(j, i + 2, n + 2) f[i][i][j][i] = get(i - 1, i, i + 1, j);
        REP(len, 1, n) REP(i, 1, n - len + 1) 
        {
            int j = i + len - 1;
            REP(t, j + 1, n + 1) REP(u, i, j) REP(k, u, j) REP(v, k + 1, j + 1)
                f[i][j][t][u] = max(f[i][j][t][u], f[i][k - 1][v][k==u?i:u] + f[k + 1][j][t][v==j+1?k+1:v] + get(i - 1, k, j + 1, t));
        }
        int ans = 0; REP(i, 1, n) ans = max(ans, f[1][n][n + 1][i]);
        printf("%d\n", ans);
        return 0;
    }
}

int main()
{
    freopen("landmine.in", "r", stdin);
    freopen("landmine.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &p[i]);
    REP(i, 1, n) scanf("%d", &q[i]);
    REP(i, 1, n) scanf("%d", &r[i]);
    bool flag = true;
    REP(i, 1, n) { scanf("%d", &s[i]); if ( s[i] != 0 ) flag = false; }
    if ( flag ) return Subtask1 :: main();
    return Subtask2 :: main();
    // if ( n > 20 ) return Subtask2 :: main();
    REP(i, 0, (1 << n) - 1)
    {
        int m = 0;
        REP(j, 1, n) if ( !((i >> j - 1) & 1) ) a[++ m] = j;
        a[0] = a[m + 1] = a[m + 2] = 0;

        REP(j, 1, m)
        {
            int val = 0;
            val += sqr(p[a[j - 1]] - q[a[j]]);
            val += sqr(p[a[j]] - r[a[j + 1]]);
            val += sqr(p[a[j + 1]] - s[a[j + 2]]);
            f[i | (1 << a[j] - 1)] = max(f[i | (1 << a[j] - 1)], f[i] + val);
        }
    }
    printf("%d\n", f[(1 << n) - 1]);
    return 0;
}
