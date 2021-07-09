/***************************************************************
	File name: sequence.cpp
	Author: ljfcnyali
	Create time: 2020年11月04日 星期三 19时57分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;
const int INF = 1e18;

int n, m, a[maxn], ans[maxn], suf[maxn], pre1[maxn], pre2[maxn];
pii f[maxn], g[maxn];

inline void add(int root, int l, int r, int L, int R, int id)
{
     
}

inline void Solve(int l, int r)
{
    if ( l > r ) return ;
    int Mid = (l + r) >> 1; Solve(l, Mid - 1); Solve(Mid + 1, r);
    int n1 = 0, n2 = 0, pos1 = 1, pos2 = 1, Min = INF, Max = -INF;
    suf[Mid - 1] = pre1[Mid - 1] = pre2[Mid - 1] = 0;
    REP(i, Mid, r)
    {
        if ( !n1 || a[i] > f[n1].x ) f[++ n1] = pii(a[i], i);
        if ( !n2 || a[i] < g[n2].x ) g[++ n2] = pii(a[i], i);
        suf[i] = (suf[i - 1] + f[n1].x * g[n2].x) % Mod;
        pre1[i] = (pre1[i - 1] + f[n1].x) % Mod;
        pre2[i] = (pre2[i - 1] + g[n2].x) % Mod;
    }
    f[++ n1] = pii(INF, r + 1); g[++ n2] = pii(-INF, r + 1);
    for ( int i = Mid; i >= l; -- i ) 
    {
        Min = min(Min, a[i]); Max = max(Max, a[i]);
        while ( pos1 <= n1 && Max > f[pos1].x ) ++ pos1;
        while ( pos2 <= n2 && Min < g[pos2].x ) ++ pos2;
        int x1 = f[pos1].y, x2 = g[pos2].y;
        int posx = min(x1 - 1, x2 - 1);
        if ( posx >= Mid ) ans = (ans + (Max * Min % Mod) * (posx - Mid + 1)) % Mod;
        int posy = max(x1, x2);
        if ( posy <= r ) ans = (ans + suf[r] - suf[posy - 1]) % Mod;
        if ( x1 < x2 ) ans = (ans + Min * (pre1[x2 - 1] - pre1[x1 - 1])) % Mod;
        if ( x1 > x2 ) ans = (ans + Max * (pre2[x1 - 1] - pre2[x2 - 1])) % Mod;
    }
}

signed main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, m)
    {
        int l, r; scanf("%lld%lld", &l, &r); 
        add(1, 1, n, l, r, i);
    }
    return 0;
}
