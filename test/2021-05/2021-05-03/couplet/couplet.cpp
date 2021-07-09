#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>

const int maxn = 2e5 + 10;

int T, n, p[maxn]; vector<int> a, b, c;
bool vis[maxn];

inline void Solve1(vector<int> &a, vector<int> &b, vector<int> &c, int n)
{
	if ( n % 2 == 0 ) { puts("-1"); exit(0); } 
	a.resize(n); b.resize(n); c.resize(n);
	REP(i, 0, n - 1) a[i] = i;
	REP(i, 0, n - 1) b[i] = i == n - 1 ? 0 : i + 1;
	REP(i, 0, n - 1) c[i] = (a[i] + b[i]) % n;
}

inline int power(int a, int b, int Mod) 
{ 
	if ( !b ) return 1; int r = 1; 
	while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } 
	return r; 
} 

inline int phi(int n)
{
	int ret = 0;
	REP(i, 1, n) if ( __gcd(n, i) == 1 ) ++ ret;
	return ret;
}

inline bool Check(int g, int n, int Mod)
{
	int x = n;
	for ( int i = 2; i * i <= x; ++ i ) if ( x % i == 0 ) 
	{
		if ( power(g, n / i, Mod) == 1 ) return false;
		while ( x % i == 0 ) x /= i;
	}
	if ( x > 1 && power(g, n / x, Mod) == 1 ) return false;
	return true;
}

inline void Solve2(vector<int> &a, vector<int> &b, vector<int> &c, int n)
{
	Solve1(a, b, c, n);
	int g = 2; while ( !Check(g, phi(n), n) ) ++ g;
	REP(i, 0, n - 1) a[i] = power(g, a[i], n);
	REP(i, 0, n - 1) b[i] = power(g, b[i], n);
	REP(i, 0, n - 1) c[i] = power(g, c[i], n);
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("couplet.in", "r", stdin);
	freopen("couplet.out", "w", stdout);
#endif
	scanf("%lld%lld", &T, &n);

	if ( T == 3 ) 
	{
		REP(i, 0, n - 1) p[i] = i;
		do
		{
			REP(i, 0, n - 1) vis[i] = false;
			REP(i, 0, n - 1) vis[power(i, p[i], n)] = true;
			bool flag = true; REP(i, 0, n - 1) if ( !vis[i] ) flag = false;
			if ( flag ) 
			{ 
				REP(i, 0, n - 1) printf("%lld ", i); puts(""); 
				REP(i, 0, n - 1) printf("%lld ", p[i]); puts(""); 
				REP(i, 0, n - 1) printf("%lld ", power(i, p[i], n)); puts(""); 
				return 0; 
			} 
		} while ( next_permutation(p, p + n) ) ;
		puts("-1"); return 0;
	}

	if ( T == 1 ) Solve1(a, b, c, n);
	if ( T == 2 ) 
	{
		if ( n == 1 ) { puts("0\n0\n0"); return 0; } 
		if ( n == 2 ) { puts("0 1\n0 1\n0 1\n"); return 0; } 
		puts("-1"); return 0;
	}
	for ( auto it : a ) printf("%lld ", it); puts("");
	for ( auto it : b ) printf("%lld ", it); puts("");
	for ( auto it : c ) printf("%lld ", it); puts("");
	return 0;
}

