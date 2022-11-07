/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2020年10月02日 星期五 19时21分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 90;
const int INF = 0x3f3f3f3f;

int n, m, p[maxn], ans, f[maxn][maxn][maxn * maxn];

inline int calc(int n) { return n * (n - 1) / 2; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { int x; scanf("%d", &x); if ( x == 1 ) p[++ m] = i; }
    ++ n; ++ m; p[m] = n;
    ans = calc(n - m);
    memset(f, 0x3f, sizeof(f)); f[0][0][0] = 0; 
    REP(i, 0, n - 1) REP(j, 0, min(m - 1, i)) REP(k, 0, calc(n - 1))
    {
        if ( f[i][j][k] == INF ) continue ;
        REP(t, i + 1, n)
        {
            int x = abs(p[j + 1] - t);
            f[t][j + 1][k + x] = min(f[t][j + 1][k + x], f[i][j][k] + calc(t - i - 1));
        }
    }
    int Min = INF;
    REP(i, 0, calc(n - 1)) { Min = min(Min, f[n][m][i]); printf("%d ", ans - Min); } 
    puts("");
    return 0;
}
