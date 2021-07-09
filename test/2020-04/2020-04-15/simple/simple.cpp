/***************************************************************
	File name: simple.cpp
	Author: ljfcnyali
	Create time: 2020年04月15日 星期三 19时05分43秒
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
const int INF = 1e18;

inline int get(int n, int a, int b, int c)
{
    int ret = 0;
    REP(i, 0, n) ret += (a * i + b) / c;
    return ret;
}

inline int f(int n, int a, int b, int c)
{
    n = b / (-a);
    cerr << n << " " << a << " " << b << " " << c << endl;
    if ( n <= INF ) return get(n, a, b, c);
    int ret = (n + 1) * (b / c) + (a / c) * n * (n + 1) / 2;
    cerr << n << " " << a << " " << b << " " << c << " " << ret << endl;
    return ret + f(n, a % c, b % c, c);
}

inline LL Solve(int n, int m, int limit)
{
    int ans = limit;
    int x = __gcd(n, m); n /= x; m /= x; limit /= x;
    int a = -n, b = limit, c = m;  
    ans -= f(limit / n, a, b, c);
    ans -= limit / n;
    return ans;
}

LL T, n, m, c, vis[maxn];

signed main()
{
    freopen("simple.in", "r", stdin);
    freopen("simple.out", "w", stdout);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld%lld", &n, &m, &c);
        if ( n > m ) swap(n, m);
        REP(i, 0, n) vis[i] = INF;
        int x = 0, ans = c + 1;
        while ( vis[(x * m) % n] == INF )
        {
            vis[(x * m) % n] = x;
            ++ x;
        }
        REP(i, 0, n - 1) if ( vis[i] != INF ) 
        {
            x = m * vis[i];
            if ( x < c ) ans -= (c - x) / n + 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
