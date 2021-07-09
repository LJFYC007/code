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
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int maxm = 4e4 + 10;
const int Delta = 2e4 + 3;
const int INF = 0x3f3f3f3f;

int n, x, y, a[maxn], b[maxn];
int f[2][maxm], pre[maxm], suf[maxm];

inline bool chk(int val, int num) { return (val + num * x) % y == 0; }
inline int calc(int val, int num) { return (val + num * x) / y; }

inline void exgcd(int a, int b, int &x, int &y)
{
    if ( !b ) { x = 1; y = 0; return ; }
    exgcd(b, a % b, x, y); int t = x; x = y; y = t - (a / b) * y; 
}

inline int Solve(int a, int b, int c)
{
    if ( c == 0 ) return 0;
    int t = __gcd(a, b); c /= t; a /= t; b /= t;
    int x, y; exgcd(a, b, x, y); x *= c; y *= c;
    assert(a * x + b * y == c);
    int ans = INF;
    int X = (x % b + b) % b; ans = min(ans, abs((c - a * X) / b) + X);
    int Y = (y % a + a) % a; ans = min(ans, abs((c - b * Y) / a) + Y);
    int now = ans;
    REP(i, -1, +1) ans = min(ans, abs((c - a * X - i * a * b) / b) + abs(X + i * b));
    REP(i, -1, +1) ans = min(ans, abs((c - b * Y - i * a * b) / a) + abs(Y + i * a));
    return ans;
}

signed main()
{
    freopen("ghost.in", "r", stdin);
    freopen("ghost.out", "w", stdout);
    scanf("%lld", &n);
    int u, v; scanf("%lld%lld", &u, &v);
    scanf("%lld%lld", &u, &v); x = abs(u - v);
    scanf("%lld%lld", &u, &v); y = abs(u - v);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n) { scanf("%lld", &b[i]); a[i] = b[i] - a[i]; }
    int ans = 0;
    REP(i, 1, n + 1) ans += Solve(x, y, a[i] - a[i - 1]);
    printf("%lld\n", ans / 2);
    return 0;
}
