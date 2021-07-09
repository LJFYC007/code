/***************************************************************
	File name: ARC101F.cpp
	Author: ljfcnyali
	Create time: 2021年05月31日 星期一 16时50分48秒
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
const int INF = 2e9;
const int Mod = 1e9 + 7;

int n, m, N, a[maxn], b[maxn], f[maxn], ans, d[maxn];
pii c[maxn]; map<int, int> Map;

inline int lowbit(int x) { return x & -x; } 
inline void add(int pos, int val) { for ( int i = pos; i <= m; i += lowbit(i) ) d[i] = (d[i] + val) % Mod; } 
inline int query(int pos) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret = (ret + d[i]) % Mod; return ret; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n) scanf("%lld", &a[i]);
	REP(i, 1, m) scanf("%lld", &b[i]);
	sort(a + 1, a + n + 1); sort(b + 1, b + m + 1);
	N = 0;
	REP(i, 1, n) 
	{ 
		int x = lower_bound(b + 1, b + m + 1, a[i]) - b - 1; 
		if ( x == 0 || x == m ) continue ; 
		++ N; c[N] = pii(a[i] - b[x], a[i] - b[x + 1]); Map[c[N].first] = true; 
	}
	m = 0; for ( auto it : Map ) Map[it.first] = ++ m;
	REP(i, 1, N) c[i].first = Map[c[i].first];
	sort(c + 1, c + N + 1, [](const pii &a, const pii &b) { return a.second > b.second || (a.second == b.second && a.first < b.first); });
	for ( int i = 1, j; i <= N; i = j + 1 ) 
	{
		j = i; while ( j < n && c[i].second == c[j + 1].second ) ++ j;
		REP(o, i, j) if ( o == i || c[o].first != c[o - 1].first ) f[o] = query(c[o].first - 1) + 1;
		REP(o, i, j) add(c[o].first, f[o]);
	}
	ans = 1;
	REP(i, 1, n) ans = (ans + f[i]) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
