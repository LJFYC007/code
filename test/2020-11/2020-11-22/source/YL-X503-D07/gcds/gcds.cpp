/***************************************************************
	File name: gcds.cpp
	Author: ljfcnyali
	Create time: 2020年11月22日 星期日 09时18分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int N = 5e5;

int n, a[maxn], ans, st[20][maxn], lg[maxn], pre[maxn], suf[maxn];
vector<int> p;

inline int Get(int l, int r)
{
    int x = lg[r - l + 1];
    return __gcd(st[x][l], st[x][r - (1 << x) + 1]);
}

inline int Find1(int pos, int x, int y = 1)
{
    if ( x == 1 ) return pos + 1;
    int l = pos;
    for ( int j = 15; j >= 0; -- j ) if ( l - (1 << j) >= 1 && __gcd(st[j][l - (1 << j)], x) > y ) 
    { x = __gcd(x, st[j][l - (1 << j)]); l -= (1 << j); }
    return l;
}

inline int Find2(int pos, int x, int y = 1)
{
    if ( x == 1 ) return pos - 1;
    int r = pos;
    for ( int j = 15; j >= 0; -- j ) if ( r + (1 << j) <= n && __gcd(st[j][r + 1], x) > y )
    { x = __gcd(x, st[j][r + 1]); r += (1 << j); }
    return r;
}

inline int calc(int x) 
{
    for ( int i = 2; i * i <= x; ++ i ) if ( x % i == 0 ) return i;
    return x;
}

signed main()
{
    freopen("gcds.in", "r", stdin);
    freopen("gcds.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld", &a[i]); st[0][i] = a[i]; }
    REP(j, 1, 15) REP(i, 1, n) st[j][i] = __gcd(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
    lg[2] = 1; REP(i, 3, n) lg[i] = lg[i >> 1] + 1;

    REP(i, 1, n) pre[i] = pre[i - 1] + i - Find1(i, a[i]) + 1;
    for ( int i = n; i >= 1; -- i ) suf[i] = suf[i + 1] + Find2(i, a[i]) - i + 1;

    REP(i, 1, n) 
    {
        int l = Find1(i, 0), r = Find2(i, 0);
        int x = calc(Get(l, i - 1)), y = calc(Get(i + 1, r));
        int val = pre[i - 1] + suf[i + 1], t = __gcd(a[i - 1], a[i + 1]);

        if ( x * y <= N ) ans = max(ans, val + r - l + 1);
        else ans = max(ans, val + max(i - l + 1, r - i + 1));

        if ( t == 1 || i == 1 || i == n ) continue ;

        p.clear();
        for ( int j = 2; j * j <= t; ++ j )
        {
            if ( t % j != 0 ) continue ;
            p.push_back(j); while ( t % j == 0 ) t /= j;
        }
        if ( t > 1 ) p.push_back(t);

        int m = p.size();
        for ( int j = 1; j < (1 << m); ++ j )
        {
            if ( m == 6 && j != (1 << m) - 1 ) continue ;
            int t = 1;
            REP(k, 0, m - 1) if ( (j >> k) & 1 ) t *= p[k];
            if ( t > N ) continue ;
            int L = Find1(i, t, t - 1), R = Find2(i, t, t - 1);
            ans = max(ans, val + (R - i) * (i - L) + 1);
            if ( t * x <= N ) ans = max(ans, val + (R - i) * (i - L) + i - l + 1);
            if ( t * y <= N ) ans = max(ans, val + (R - i) * (i - L) + r - i + 1);
            if ( t * x * y <= N ) ans = max(ans, val + (R - i) * (i - L) + r - l + 1);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
