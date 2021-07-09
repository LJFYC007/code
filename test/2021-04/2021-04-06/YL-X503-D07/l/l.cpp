/***************************************************************
	File name: l.cpp
	Author: ljfcnyali
	Create time: 2021年04月06日 星期二 10时58分33秒
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

int a, b, T, n;

inline int power(int a, int b, int Mod = INF) 
{ 
	if ( b < 0 ) return 1; int r = 1; 
	while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } 
	return r; 
} 
inline void exgcd(int a, int b, int &x, int &y)
{
	if ( !b ) { x = 1; y = 0; return ; } 
	exgcd(b, a % b, x, y); int t = x; x = y; y = t - a / b * y;
}

inline int Get(int A, int B) { int x, y; exgcd(A, B, x, y); return (x % B + B) % B; }

inline bool Check(int g)
{
	int p = g / __gcd(g, a); if ( p % 3 == 0 && a % 3 != 0 ) return false;
	int t = Get(3, p) * a * a % p, ans = INF;
	if ( p % 3 == 0 ) { p /= 3; t = (a * a / 3) % p;} 
	REP(k, 0, g / p - 1)
	{
		int t0 = (t + k * p) % g, A = ((a * a - t0) % g + g) % g, B = g, C = -a * t0 - b, x, y, d = __gcd(A, B);
		if ( C % d != 0 ) continue ; A /= d; B /= d; C /= d; exgcd(A, B, x, y); x *= C; y *= C;
		x = (x % B + B) % B; int val = x;
		do
		{
			if ( (x * x + x * a + t0) % g == 0 ) ans = min(ans, x);
			x = (x + B) % g;
		} while ( x != val ) ;
	}
	if ( ans == INF ) return false;
	printf("%lld\n", ans); return true;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("l.in", "r", stdin);
    freopen("l.out", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- ) 
	{
		scanf("%lld%lld", &a, &b); 
		int val = power(a, 7) + 27 * a * b * b; vector<int> p; 
		for ( int i = 1; i * i <= val; ++ i ) if ( val % i == 0 ) 
		{
			p.push_back(i);
			if ( val != i * i ) p.push_back(val / i);
		}
		sort(p.begin(), p.end()); reverse(p.begin(), p.end());
		for ( auto it : p ) if ( Check(it) ) break ; 
	}
    return 0;
}
