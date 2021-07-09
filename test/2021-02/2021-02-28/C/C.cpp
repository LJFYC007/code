#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 2e5 + 10;
const int seed1 = 131;
const int seed2 = 233;
const int Mod1 = 998244353;
const int Mod2 = 1e9 + 7;

int n, ans, p1[maxn], p2[maxn], invp1[maxn], invp2[maxn];
char s[maxn];
map<int, int> Map1, Map2;

inline int power(int a, int b, int Mod) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

struct node
{
	int a[maxn], tot, Hash1[maxn], Hash2[maxn], Hash3[maxn], Hash4[maxn];
	
	inline void INIT() { tot = 0; } 

	inline void Insert(int x) 
	{
		if ( tot && a[tot] == x ) -- tot;
		else 
		{ 
			a[++ tot] = x; 
			Hash1[tot] = (Hash1[tot - 1] + p1[tot] * (x - 'a' + 1)) % Mod1; 
			Hash2[tot] = (Hash2[tot - 1] + invp1[tot] * (x - 'a' + 1)) % Mod1; 

			Hash3[tot] = (Hash3[tot - 1] + p2[tot] * (x - 'a' + 1)) % Mod2; 
			Hash4[tot] = (Hash4[tot - 1] + invp2[tot] * (x - 'a' + 1)) % Mod2; 
		}
	}

	inline void Erase(int x) { Insert(x); } 

	inline int Get1(int l, int r)
	{
		int ret = (Hash1[r] - Hash1[l - 1] + Mod1) % Mod1;
		ret = ret * invp1[l] % Mod1; return ret;
	}

	inline int Get2(int l, int r)
	{
		int ret = (Hash3[r] - Hash3[l - 1] + Mod2) % Mod2;
		ret = ret * invp2[l] % Mod2; return ret;
	}
} pre, suf;

inline int Merge(node &a, node &b, int op)
{
	int len = 0, n = a.tot, m = b.tot, l = 1, r = min(n, m);
	while ( l <= r ) 
	{
		int Mid = l + r >> 1;
		if ( a.Get1(n - Mid + 1, n) == b.Get1(m - Mid + 1, m) 
		  && a.Get2(n - Mid + 1, n) == b.Get2(m - Mid + 1, m) ) { l = Mid + 1; len = Mid; } 
		else r = Mid - 1;
	}
	int x = (a.Hash1[n - len] + p1[n - len + m - len + 1] * b.Hash2[m - len]) % Mod1;
	int y = (a.Hash3[n - len] + p2[n - len + m - len + 1] * b.Hash4[m - len]) % Mod2;
	if ( op == 0 ) { ++ Map1[x]; ++ Map2[y]; }
	else ans += min(Map1[x], Map2[y]);
}

inline void Solve(int l, int r)
{
	if ( l >= r ) return ; 
	int Mid = (l + r) >> 1; 
	REP(x, 0, 2) REP(y, 0, 2) if ( x != y ) 
	{
		Map1.clear(); Map2.clear();
		node b; b.INIT(); for ( int i = Mid; i >= l; -- i ) b.Insert(s[i]);
		REP(i, l, Mid)
		{
			b.Erase(s[i]); 
			if ( s[i] - 'a' == x ) { b.Insert(y + 'a'); Merge(pre, b, 0); b.Erase(y + 'a'); }
			pre.Insert(s[i]);
		}
		for ( int i = Mid; i >= l; -- i ) pre.Erase(s[i]);

		b.INIT(); REP(i, Mid + 1, r) b.Insert(s[i]);
		for ( int i = r; i > Mid; -- i ) 
		{
			b.Erase(s[i]);
			if ( s[i] - 'a' == y ) { b.Insert(x + 'a'); Merge(suf, b, 1); b.Erase(x + 'a'); }
			suf.Insert(s[i]);
		}
		REP(i, Mid + 1, r) suf.Erase(s[i]);
	}
	for ( int i = r; i > Mid; -- i ) suf.Insert(s[i]); Solve(l, Mid);
	REP(i, Mid + 1, r) suf.Erase(s[i]); REP(i, l, Mid) pre.Insert(s[i]); Solve(Mid + 1, r);
	for ( int i = Mid; i >= l; -- i ) pre.Erase(s[i]);
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s + 1); n = str(s + 1); 
	p1[0] = p2[0] = invp1[0] = invp2[0] = 1; 
	REP(i, 1, n + n) 
	{ 
		p1[i] = p1[i - 1] * seed1 % Mod1; 
		invp1[i] = invp1[i - 1] * power(seed1, Mod1 - 2, Mod1) % Mod1; 
		p2[i] = p2[i - 1] * seed2 % Mod2; 
		invp2[i] = invp2[i - 1] * power(seed2, Mod2 - 2, Mod2) % Mod2; 
	}
	Solve(1, n); printf("%lld\n", ans);
	return 0;
}
