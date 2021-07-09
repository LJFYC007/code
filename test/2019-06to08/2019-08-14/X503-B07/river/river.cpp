/***************************************************************
	File name: river.cpp
	Author: ljfcnyali
	Create time: 2019年08月14日 星期三 08时48分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 6010;
const LL Mod = 1e9 + 7;

struct node
{
    int x, y, X, Y;
} a[maxn];

inline int cmp1(node a, node b) { return a.x < b.x; }
inline int cmp2(node a, node b) { return a.y < b.y; }

int N, n, m;
LL ans, px[maxn], py[maxn], f[maxn][maxn];

int main()
{
    freopen("river.in", "r", stdin);
    freopen("river.out", "w", stdout);
    scanf("%d", &N);
    REP(i, 1, N) scanf("%d%d", &a[i].x, &a[i].y);
    sort(a + 1, a + N + 1, cmp1);
    REP(i, 1, N) { if ( a[i].x != a[i - 1].x ) ++ n; a[i].X = n; px[n] = a[i].x; }
    sort(a + 1, a + N + 1, cmp2);
    REP(i, 1, N) { if ( a[i].y != a[i - 1].y ) ++ m; a[i].Y = m; py[m] = a[i].y; }
    REP(i, 1, N) REP(j, i + 1, N)
    {
        int Minx = min(a[i].X, a[j].X), Maxx = max(a[i].X, a[j].X);
        int Miny = min(a[i].Y, a[j].Y), Maxy = max(a[i].Y, a[j].Y);
        ++ f[Minx][Miny]; -- f[Minx][Maxy]; -- f[Maxx][Miny]; ++ f[Maxx][Maxy];
    }
    REP(i, 1, n - 1) REP(j, 1, m - 1)
    {
        f[i][j] += f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1]; 
        if ( f[i][j] >= 2 ) 
        {
            LL u = ((f[i][j] - 1) * f[i][j] / 2) % Mod;
            LL v = (px[i + 1] - px[i]) * (py[j + 1] - py[j]); v %= Mod;
            ans = (ans + (u * v) % Mod) % Mod;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
