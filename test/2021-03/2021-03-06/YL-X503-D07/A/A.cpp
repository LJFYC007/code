#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1030;
const int N = 2048;
const int M = 1024;
const int Mod = 1e9 + 7;

int n, ans;
char t[maxn];
bitset<N> s1, s2, ccc;

inline bitset<N> Solve(int x, int y)
{
	bitset<N> a, b;
	if ( !x ) { a.set(); return a; } 
	if ( !y ) { a.reset(); return a; } 
	if ( x < y ) 
	{
		b = Solve(x, y - x); int m = 0;
		REP(i, 0, y - 1) { if ( b[i] == 0 ) a[m ++] = 1; a[m ++] = b[i]; }
	}
	else
	{
		b = Solve(x - y, y); int m = 0;
		REP(i, 0, x - 1) { if ( b[i] == 1 ) a[m ++] = 0; a[m ++] = b[i]; }
	}
	return a;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	scanf("%lld", &n); scanf("%s", t); REP(i, 0, n - 1) ccc[i] = 1;
	REP(i, 0, n - 1) if ( t[i] != '?' ) { s2[i] = 1; s1[i] = t[i] - '0'; }
	REP(x, 0, n) 
	{
		bitset<N> S = Solve(x, n - x), s = S | (S << n);
		REP(i, 0, n - 1)
		{
			bitset<N> now = s >> i;
			if ( i && ((now ^ S) & ccc).count() == 0 ) break ; 
			now = (now & s2) ^ s1;
			if ( now.count() == 0 ) ++ ans;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
