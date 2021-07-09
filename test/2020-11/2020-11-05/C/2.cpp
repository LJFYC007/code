/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年11月05日 星期四 15时16分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

const int maxn = 110;
const int Mod = 998244353;

int n, m;
struct node 
{ 
    int f, g, h; 
    node ( int a = 0, int b = 0, int c = 0 ) { f = a; g = b; h = c; }
} a[maxn][maxn];

inline int calc1(int x) { int ret = 0; REP(i, 1, x) ret = (ret + i) % Mod; return ret; }
inline int calc2(int x) { int ret = 0; REP(i, 1, x) ret = (ret + i * i) % Mod; return ret; }
inline node operator + (node a, node b) { return node((a.f + b.f) % Mod, (a.g + b.g) % Mod, (a.h + b.h) % Mod); }

inline node Solve(int n, int m)
{
    if ( n <= 0 ) return node(1, 1, 1);
    if ( m == 0 ) return node(0, 0, 0);
    if ( n == 1 ) return node(calc2(m), calc1(m), m);
    if ( a[n][m].f != -1 ) return a[n][m];
    node ret = node(1, 1, 1);
    REP(i, 1, n) REP(j, i, n) 
    {
        node x = Solve(j - i + 1, m - 1), y = Solve(n - j - 1, m);
        node t;
        t.f = (x.f * y.h + y.f * x.h + 2 * x.g * y.g) % Mod;
        t.g = (x.g * y.h + y.g * x.h) % Mod;
        t.h = (x.h * y.h) % Mod;
        ret = ret + t;
    }
    a[n][m] = ret; return ret;
}

signed main()
{
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 0, n) REP(j, 0, m) a[i][j] = node(-1, -1, -1);
    int ans = (Solve(n, m).f - Solve(n, m - 1).f) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
