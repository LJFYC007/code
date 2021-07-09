/***************************************************************
	File name: ghost.cpp
	Author: ljfcnyali
	Create time: 2020年11月10日 星期二 11时06分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;
const int maxm = 4e4 + 10;
const int Delta = 2e4;
const int INF = 0x3f3f3f3f;

int n, x, y, a[maxn], b[maxn];
int f[maxn][maxm], pre[maxm], suf[maxm];

inline bool chk(int pos, int num) { return (a[pos] + num * x) % y == 0; }
inline int calc(int pos, int num) { return (a[pos] + num * x) / y; }

int main()
{
    freopen("ghost.in", "r", stdin);
    freopen("ghost.out", "w", stdout);
    scanf("%d", &n);
    int u, v; scanf("%d%d", &u, &v);
    scanf("%d%d", &u, &v); x = u - v;
    scanf("%d%d", &u, &v); y = u - v;
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n) { scanf("%d", &b[i]); a[i] = b[i] - a[i]; }
    int m = min(max(abs(x), abs(y)), Delta);
    REP(i, 0, n) REP(j, Delta - m, Delta + m) f[i][j] = INF; f[0][Delta] = 0;
    REP(i, 1, n) REP(j, Delta - m, Delta + m)
    {
        if ( !chk(i, j - Delta) ) continue ;
        int Minpre = INF, Minsuf = INF;
        REP(k, Delta - m, Delta + m)
        {
            if ( f[i - 1][k] == INF ) continue ;
            f[i][j] = min(f[i][j], f[i - 1][k] + abs(j - k) + abs(calc(i, j - Delta) - calc(i - 1, k - Delta)));
        }
    }
    int ans = INF;
    REP(i, Delta - m, Delta + m) ans = min(ans, f[n][i] + abs(Delta - i));
    printf("%d\n", ans / 2);
    return 0;
}
