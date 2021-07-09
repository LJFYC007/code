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
const int Delta = 2e4 + 3;
const int INF = 0x3f3f3f3f;

int n, x, y, a[maxn], b[maxn];
int f[2][maxm], pre[maxm], suf[maxm];

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
    int m = min(max(abs(x), abs(y)), Delta - 3);
    int op = 0;
    REP(j, Delta - m, Delta + m) f[0][j] = INF; f[0][Delta] = 0;
    REP(i, 1, n) 
    {
        op ^= 1;
        REP(j, Delta - m, Delta + m) f[op][j] = INF;
        REP(j, Delta - m - 1, Delta + m + 1) pre[j] = suf[j] = INF;
        REP(j, Delta - m, Delta + m)
        {
            pre[j] = f[op ^ 1][j] - j + calc(i - 1, j - Delta);
            suf[j] = f[op ^ 1][j] + j - calc(i - 1, j - Delta);
        }
        REP(j, Delta - m, Delta + m) pre[j] = min(pre[j], pre[j - 1]);
        for ( int j = Delta + m; j >= Delta - m; -- j ) suf[j] = min(suf[j], suf[j + 1]);
        REP(j, Delta - m, Delta + m)
        {
            if ( !chk(i, j - Delta) ) continue ;
            f[op][j] = min(f[op][j], j - calc(i, j - Delta) + pre[j]);
            f[op][j] = min(f[op][j], calc(i, j - Delta) - j + suf[j]);
        }
    }
    int ans = INF;
    REP(i, Delta - m, Delta + m) ans = min(ans, f[op][i] + abs(Delta - i));
    printf("%d\n", ans / 2);
    return 0;
}
