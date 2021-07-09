/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2021年02月23日 星期二 09时47分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
#define int long long
typedef long long LL;

const int maxn = 41;
const int Mod = 998244353;
const int INF = 1e18;

struct frac { int x, y; } z[maxn], v[maxn];
frac operator + (frac a, frac b) 
{
	frac c; c.y = a.y / __gcd(a.y, b.y) * b.y;
	c.x = a.x * (c.y / a.y) + b.x * (c.y / b.y);
	int d = __gcd(c.x, c.y); if ( d ) { c.x /= d; c.y /= d; }
	return c;
}
frac operator + (frac a, int b) { return {a.x + b * a.y, a.y}; }
frac operator * (frac a, frac b) { return {a.x * b.x, a.y * b.y}; }
frac operator * (frac a, int b) 
{
	a.x *= b; int d = __gcd(a.x, a.y); 
	if ( d ) { a.x /= d; a.y /= d; }
	return a;
}
frac operator / (frac a, int b)
{
	a.y *= b; int d = __gcd(a.x, a.y); a.x /= d; a.y /= d;
	return a;
}
bool operator < (frac a, frac b) { return a.x * b.y < a.y * b.x; }
bool operator == (frac a, frac b) { return a.x * b.y == a.y * b.x; }

int n, m, cnt, a[maxn], f[maxn][maxn][maxn], ans;
pii p[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline void Solve(frac z, frac L, frac R)
{
	REP(i, 1, m) v[i] = z * p[i].x + p[i].y; 
	sort(v + 1, v + m + 1);
	REP(i, 1, m - 1) REP(j, 1, n)
	{ 
		f[i][j][0] = 1; int len = a[j + 1] - a[j]; 
		frac l = max(z * a[i]
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, n + 1) scanf("%lld", &a[i]);
	frac Min = {INF, 1}; REP(i, 1, n) Min.x = min(Min.x, a[i + 1] - a[i]);

	REP(i, 1, n) { p[++ m] = pii(1 - i, a[i]); p[++ m] = pii(1 - i, a[i + 1]); }
	REP(i, 1, m - 1) REP(j, i + 1, m)
	{
		int x = p[j].y - p[i].y, y = p[i].x - p[j].x, d = __gcd(x, y);
		if ( d ) { x /= d; y /= d; } 
	 	if ( y ) z[++ cnt] = {x, y};
	}
	sort(z + 1, z + cnt + 1);
	REP(i, 1, cnt - 1)
	{
		if ( z[i] == z[i + 1] || Min < z[i] ) continue ; 
		Solve((z[i] + z[i + 1]) / 2, z[i], z[i + 1]);
	}
	printf("%llf\n", (ans + Mod) % Mod);
    return 0;
}
