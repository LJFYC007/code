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
const int INF = 1e18;

int n, x, y, a[maxn], ansx[maxn], ansy[maxn];

inline bool chk(int val, int num) { return (val + num * x) % y == 0; }
inline int calc(int val, int num) { return (val + num * x) / y; }

inline void exgcd(int a, int b, int &x, int &y)
{
    if ( !b ) { x = 1; y = 0; return ; }
    exgcd(b, a % b, x, y); int t = x; x = y; y = t - (a / b) * y; 
}

inline int Solve(int pos, int a, int b, int c)
{
    if ( c == 0 ) return 0;
    int t = __gcd(a, b); c /= t; a /= t; b /= t;
    int x, y; exgcd(a, b, x, y); x *= c; y *= c;
    assert(a * x + b * y == c);
    int ans = INF, X = (x % b + b) % b, Y = (y % a + a) % a; 
    REP(i, -2, +2) 
    {
        int gg = abs((c - a * X - i * a * b) / b) + abs(X + i * b);
        if ( gg < ans ) { ans = gg; ansx[pos] = X + i * b; ansy[pos] = (c - a * X - i * a * b) / b; }
    }
    REP(i, -2, +2) 
    {
        int gg = abs((c - b * Y - i * a * b) / a) + abs(Y + i * a);
        if ( gg < ans ) { ans = gg; ansx[pos] = (c - b * Y - i * a * b) / a; ansy[pos] = Y + i * a; }
    }
    return ans;
}

struct node 
{
    int pos, val, op;
    node ( int a = 0, int b = 0, int c = 0 ) { pos = a; val = b; op = c; }
    bool operator < (const node &a) const { return val > a.val; }
} ;
priority_queue<node> Q;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &x, &y);
    REP(i, 1, n) scanf("%lld", &a[i]);
    int t = __gcd(x, y); x /= t; y /= t; 
    REP(i, 1, n) if ( a[i] % t != 0 ) { puts("-1"); return 0; }
    REP(i, 1, n) a[i] /= t;
    int ans = 0;
    REP(i, 1, n + 1) ans += Solve(i, x, y, a[i] - a[i - 1]);
    int sum = 0; REP(i, 1, n + 1) sum += ansx[i];
    REP(i, 1, n + 1) 
    {
        int val = abs(ansx[i]) + abs(ansy[i]); 
        if ( sum < 0 ) Q.push(node(i, abs(ansx[i] + y) + abs(ansy[i] - x) - val, y));
        else Q.push(node(i, abs(ansx[i] - y) + abs(ansy[i] + x) - val, -y));
    }
    while ( sum ) 
    {
        node gg = Q.top(); Q.pop();
        sum += gg.op; ans += gg.val; int i = gg.pos; 
        if ( gg.op > 0 ) { ansx[i] += y; ansy[i] -= x; }
        else { ansx[i] -= y; ansy[i] += x; }

        int val = abs(ansx[i]) + abs(ansy[i]); 
        if ( sum < 0 ) Q.push(node(i, abs(ansx[i] + y) + abs(ansy[i] - x) - val, y));
        else Q.push(node(i, abs(ansx[i] - y) + abs(ansy[i] + x) - val, -y));
    }
    printf("%lld\n", ans / 2);
    return 0;
}
