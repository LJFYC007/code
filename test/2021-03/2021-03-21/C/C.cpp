/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年03月21日 星期日 10时31分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, dis[2][maxn], tot[2], now; LL ans, num;
vector<int> a[2][maxn];
struct node { int l, r, x; } id[2][maxn];
bool vis[2][maxn];
queue<pii> Q[2];
struct SegmentTree
{
	set<pii> Set[maxn * 2];
#define lson root << 1
#define rson root << 1 | 1

	inline void Modify(int root, int l, int r, int L, int R, pii x)
	{
		if ( L <= l && r <= R ) { Set[root].insert(x); return ; }
		int Mid = l + r >> 1;
		if ( L <= Mid ) Modify(lson, l, Mid, L, R, x);
		if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, x);
	}

	inline void Query(int root, int l, int r, int pos, int L, int R, int d)
	{
		auto itl = Set[root].lower_bound(pii(L, 0)), it = itl;
		auto itr = Set[root].lower_bound(pii(R + 1, 0));
		while ( it != itr ) 
		{ 
			if ( !vis[now ^ 1][it -> second] ) 
			{
				vis[now ^ 1][it -> second] = true;
				dis[now ^ 1][it -> second] = d;
				Q[now ^ 1].push(pii(it -> second, now ^ 1));
			}
			++ it; 
		} 
		Set[root].erase(itl, itr);
		if ( l == r ) return ;
		int Mid = l + r >> 1;
		if ( pos <= Mid ) Query(lson, l, Mid, pos, L, R, d);
		else Query(rson, Mid + 1, r, pos, L, R, d);
	}
} A[2];

inline void Build(int op)
{
	REP(i, 1, n)
	{
		int lst = 1;
		for ( auto it : a[op ^ 1][i] ) 
		{
			if ( lst <= it - 1 ) 
			{
				id[op ^ 1][++ tot[op ^ 1]] = {lst, it - 1, i};
				A[op ^ 1].Modify(1, 1, n, lst, it - 1, pii(i, tot[op ^ 1]));
			}
			lst = it + 1;
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, m) { int x, y; scanf("%d%d", &x, &y); a[0][x].push_back(y); a[1][y].push_back(x); } 
	REP(o, 0, 1) REP(i, 1, n) { a[o][i].push_back(n + 1); sort(a[o][i].begin(), a[o][i].end()); } 
	Build(0); Build(1); vis[1][1] = true; Q[1].push(pii(1, 1)); now = 1;
	while ( !Q[now].empty() ) 
	{
		while ( !Q[now].empty() ) 
		{
			pii u = Q[now].front(); Q[now].pop(); node t = id[u.second][u.first];
			int op = u.second ^ 1; A[op].Query(1, 1, n, t.x, t.l, t.r, dis[u.second][u.first] + 1); 
		}
		now ^= 1;
	}
	REP(o, 0, 1) REP(i, 1, tot[o]) if ( vis[o][i] ) 
	{
		ans += 1ll * dis[o][i] * (id[o][i].r - id[o][i].l + 1);
		num += id[o][i].r - id[o][i].l + 1;
	}
	ans -= num / 2; printf("%lld\n", ans / 2);
    return 0;
}
