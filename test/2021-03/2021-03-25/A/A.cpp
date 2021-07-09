#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, M, a[maxn], m[maxn], q, prime[maxn], tot, p[maxn];
int g[maxn], f[maxn], cnt[maxn], d[maxn];
LL ans[maxn], c[maxn];
vector<pii> t[maxn], Q[maxn];

inline int lowbit(int x) { return x & -x; }
inline void add1(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[i] += val; }
inline LL query1(int pos) { LL ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[i]; return ret; }
inline void add2(int pos) { for ( int i = pos; i <= n; i += lowbit(i) ) ++ d[i]; }
inline int query2(int pos) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += d[i]; return ret; }

inline void add(int x, int val)
{
	for ( int i = 0; i < t[x].size(); ++ i ) 
	{
		int num = t[x][i].second, u = t[x][i].first;
		REP(j, 1, num)
		{
			if ( val == 1 && !cnt[u] ) g[u] = a[x] % u;
			cnt[u] += val; u *= t[x][i].first;
		}
	}
}

inline bool Check(int x)
{
	for ( int i = 0; i < t[x].size(); ++ i ) 
	{	
		int num = t[x][i].second, u = t[x][i].first;
		REP(j, 1, num)
		{
			if ( cnt[u] && g[u] != a[x] % u ) return false;
			u *= t[x][i].first;
		}
	}
	return true;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) { scanf("%d%d", &m[i], &a[i]); M = max(M, m[i]); }
	REP(i, 2, M)
	{
		if ( !p[i] ) { prime[++ tot] = i; p[i] = i; }
		for ( int j = 1; j <= tot && prime[j] * i <= M; ++ j ) 
		{
			p[i * prime[j]] = prime[j];
			if ( i % prime[j] == 0 ) break ; 
		}
	}
	REP(i, 1, n)
	{
		int x = m[i];
		while ( x > 1 ) 
		{
			int val = p[x], num = 0;
			while ( x % val == 0 ) { ++ num; x /= val; } 
			t[i].push_back(pii(val, num));
		}
	}

	int now = 0;
	REP(i, 1, n)	
	{
		while ( now < i ) add(++ now, 1);
		f[i] = now; while ( now < n && Check(now + 1) ) { add(++ now, 1); ++ f[i]; } 
		add(i, -1);
	}

	scanf("%d", &q);
	REP(i, 1, q) { int l, r; scanf("%d%d", &l, &r); Q[l].push_back(pii(r, i)); }
	for ( int i = n; i >= 1; -- i )
	{
 		add1(f[i], f[i]); add2(f[i]);
		for ( auto it : Q[i] ) 
		{
			int r = it.first, id = it.second;
			ans[id] = -1ll * (i + r - 2) * (r - i + 1) / 2;
			ans[id] += query1(r) + 1ll * (r - i + 1 - query2(r)) * r;
		}
	}
	REP(i, 1, q) printf("%lld\n", ans[i]);
	return 0;
}
