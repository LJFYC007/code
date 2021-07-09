/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2021年03月18日 星期四 20时57分12秒
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
const int INF = 1e18;

int n, m, q, Q[maxn], p[maxn], a[maxn], b[maxn], dis[maxn], c[maxn], s[maxn], d[maxn];
map<int, int> Map[maxn];

inline int lowbit(int x) { return x & -x; } 
inline void add(int pos, int val) { for ( int i = pos; i <= n + 1; i += lowbit(i) ) c[i] += val; } 
inline int query(int pos) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[i]; return ret; }
inline void	ADD(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) d[i] = min(d[i], val); } 
inline int QUERY(int pos) { int ret = n + 1; for ( int i = pos; i > 0; i -= lowbit(i) ) ret = min(ret, d[i]); return ret; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &q);
	REP(i, 1, n) scanf("%lld", &p[i]);
	REP(i, 1, n) { scanf("%lld", &a[i]); s[i] = s[i - 1] + a[i]; } 
	REP(i, 1, n) scanf("%lld", &b[i]);
	set<int> Set; Set.insert(1); Set.insert(n + 1); Map[1][n + 1] = true;
	REP(i, 1, q)
	{
		scanf("%lld", &Q[i]); if ( Q[i] == 1 ) continue ; 
		auto it = Set.lower_bound(Q[i]);
		if ( *it != Q[i] ) 
		{
			auto itl = it, itr = it; -- itl; 
			Map[*itl][Q[i]] = Map[Q[i]][*itr] = true;
			Set.insert(Q[i]);
		}
		else
		{
			Set.erase(it); it = Set.lower_bound(Q[i]);
			auto itl = it; -- itl; Map[*itl][*it] = true;
		}
	}

	REP(i, 1, n) d[i] = n + 1;
	for ( int i = n; i >= 1; -- i ) 
	{
		int pos = QUERY(n - p[i] + 1); ADD(n - p[i] + 1, i); add(i + 1, a[i]); 
		if ( query(pos) > b[i] ) add(pos, b[i] - query(pos));
		for ( auto it : Map[i] ) Map[i][it.first] = query(it.first);
	}

	Set.clear(); Set.insert(1); Set.insert(n + 1); int ans = Map[1][n + 1];
	REP(i, 1, q)
	{
		if ( Q[i] != 1 ) 
		{
			auto it = Set.lower_bound(Q[i]);
			if ( *it != Q[i] ) 
			{
				auto itl = it, itr = it; -- itl; 
				ans = ans - Map[*itl][*itr] + Map[*itl][Q[i]] + Map[Q[i]][*itr];
				Set.insert(Q[i]);
			}
			else
			{
				auto itl = it, itr = it; -- itl; ++ itr;
				ans = ans + Map[*itl][*itr] - Map[*itl][Q[i]] - Map[Q[i]][*itr];
				Set.erase(it); 
			}
		}
		printf("%lld\n", ans);
	}
    return 0;
}
