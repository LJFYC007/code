/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2019年10月16日 星期三 10时52分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define inv(x) power(x, Mod - 2)
typedef long long LL;

const int Mod = 1e9 + 7;
const int maxn = 10000010;

int n, m, ans, p1[maxn], p2[maxn];

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

inline int C(int n, int m)
{
    int sum = (p1[n] * p2[m] % Mod) * p2[n - m] % Mod;
    return sum;
}

signed main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    p1[0] = 1; REP(i, 1, 2 * n) p1[i] = p1[i - 1] * i % Mod;
    REP(i, 0, 2 * n) p2[i] = inv(p1[i]);
    REP(i, 1, n)
    {
        int x = power(i, 2 * m);
        int y = C(2 * i, i) - 1 + Mod;
        ans = (ans + x * y) % Mod;
    }
    ans = (ans + Mod) % Mod;
    printf("%lld\n", ans);
    return 0;
}

