/***************************************************************
	File name: satellite.cpp
	Author: ljfcnyali
	Create time: 2020年11月20日 星期五 15时23分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, q, w, h, Mod, a, b, ans[maxn];
struct node 
{
    int h, x, y; 
    node ( int a = 0, int b = 0, int c = 0 ) { h = a; x = b; y = c; }
} p[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
    freopen("satellite.in", "r", stdin);
    freopen("satellite1.out", "w", stdout);
    scanf("%lld%lld%lld%lld%lld%lld%lld", &n, &q, &w, &h, &Mod, &a, &b);
    REP(i, 1, n) scanf("%lld%lld%lld", &p[i].h, &p[i].x, &p[i].y); 
    REP(i, 1, q) 
    { 
        int x, y; scanf("%lld%lld", &x, &y); 
        int ans = 0;
        REP(j, 1, n) ans = (ans + p[j].h * power(a, abs(p[j].x - x)) % Mod * power(b, abs(p[j].y - y))) % Mod;
        printf("%lld\n", ans);
    }
    return 0;
}
