/***************************************************************
	File name: interval.cpp
	Author: ljfcnyali
	Create time: 2021年06月30日 星期三 09时58分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e5 + 10;
const int Mod = 998244353;

int n, m, q, a[maxn], b[maxn], c[maxn], s[maxn], t[maxn], num = 1;
vector<pii> p;

inline int Get(int l, int r) { return (s[r] - s[l - 1]) % Mod; }
inline int calc(int l, int r) { return (t[r] - t[l - 1]) % Mod; }
inline int ccc(int n) 
{ 
	if ( n <= 0 ) return 0;
	return (1ll * n * (n + 1) / 2) % Mod; 
}

inline int Query(int l, int r)
{
	int posl = lower_bound(p.begin(), p.end(), pii(l, n + 1)) - p.begin() - 1;
	if ( p[posl].first <= l && p[posl].second >= r - 1 )
		return ccc(r - l);
	int posr = lower_bound(p.begin(), p.end(), pii(r + 1, 0)) - p.begin() - 1;
	int ret = 0;
	if ( posr > posl ) ret = (ret + c[posr - 1] - c[posl]) % Mod;

	ret = (ret + ccc(min(p[posl].second + 1, r) - max(p[posl].first, l))) % Mod;
	if ( posl != posr ) ret = (ret + ccc(min(p[posr].second + 1, r) - max(p[posr].first, l))) % Mod;

	return ret;
}

inline int Solve(int l, int r, int n)
{
	if ( l == r ) return m - 1;
	int ret = (1ll * Get(l + 1, r) * (m - 2) + m - 1) % Mod;
	ret = (ret + 1ll * (r - l) * (m - 1)) % Mod;
	ret = (ret + 1ll * calc(l + 2, r) * (m - 1)) % Mod;
	ret = (ret - 1ll * Get(l + 2, r) * l % Mod * (m - 1)) % Mod;

	ret = (ret + 1ll * Get(l + 1, r) * m) % Mod;
	ret = (ret + 1ll * Get(l + 1, r) * (r - 1) % Mod * (m - 1)) % Mod;
	ret = (ret - 1ll * calc(l + 1, r) * (m - 1)) % Mod;

	ret = (ret - Query(l, r)) % Mod;
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("interval.in", "r", stdin);
    freopen("interval.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &m, &q);
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 2, n) s[i] = s[i - 1] + (a[i] != a[i - 1]);
	REP(i, 2, n) t[i] = (t[i - 1] + (a[i] != a[i - 1]) * (i - 1)) % Mod;

	p.push_back(pii(0, -1)); 
	for ( int l = 1, r; l < n; l = r ) 
	{
		r = l + 1; if ( a[l] == a[r] ) continue ; 
		while ( r < n && a[r + 1] == a[r - 1] ) ++ r;
		p.push_back(pii(l, r - 1));
		c[num] = (c[num - 1] + ccc(r - l)) % Mod; ++ num;
	}
	p.push_back(pii(n + 1, n + 1));

	while ( q -- ) 
	{
		int l, r; scanf("%d%d", &l, &r);
		printf("%d\n", (Solve(l, r, r - l + 1) + Mod) % Mod);
	}
    return 0;
}
