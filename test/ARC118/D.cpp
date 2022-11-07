/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;
#define int long long

const int maxn = 2e5 + 10;

int P, a, b, ans[maxn], p[maxn], q[maxn];
bool vis[maxn];

inline int power(int a, int b, int Mod) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline bool Check(int g)
{
	int x = P - 1;
	for ( int i = 2; i * i <= x; ++ i ) if ( x % i == 0 ) 
	{
		if ( power(g, (P - 1) / i, P) == 1 ) return false;
		while ( x % i == 0 ) x /= i;
	}
	if ( x > 1 && power(g, (P - 1) / x, P) == 1 ) return false;
	return true;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &P, &a, &b);
	int g = 2; while ( !Check(g) ) ++ g;
	int x = 1; p[x] = 0; q[0] = x;
	REP(i, 1, P - 2) { x = x * g % P; p[x] = i; q[i] = x; } 
	a = p[a]; b = p[b];
	int d = __gcd(a, b);
	cerr << g << " " << P - 1 << endl;
	cerr << a << " " << b << " " << d << endl;
	if ( __gcd(d, P - 1) > 1 ) { puts("No"); return 0; } 
	vis[0] = true;

	int N = 1, val = a;
	while ( val != 0 ) { ++ N; val = (val + a) % (P - 1); }
	int M = 1; val = b;
	while ( val != 0 ) { ++ M; val = (val + b) % (P - 1); }

	x = 0;
	int op = 1;
	swap(a, b); 
	REP(i, 2, P - 1)
	{
		int y = (x + op * a + P - 1) % (P - 1);
		if ( vis[y] ) { x = (x + b) % (P - 1); op = op == 1 ? -1 : 1; }
		else x = y;
		vis[x] = true; ans[i] = x;
	}
	puts("Yes");
	REP(i, 1, P) printf("%lld ", q[ans[i]]); puts("");
	REP(i, 1, P - 1) 
	{
		assert((q[ans[i]] * q[a] % P == q[ans[i + 1]]) || (q[ans[i]] * q[b] % P == q[ans[i + 1]]) ||
	}
    return 0;
}
