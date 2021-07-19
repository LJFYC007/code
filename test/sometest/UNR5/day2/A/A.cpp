
/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年07月19日 星期一 08时53分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e5 + 10;

int n, m, nxt[maxn], pre[maxn], ans[maxn], p[maxn], lst, cnt1, cnt2, op, w[maxn];
struct node { int l, a[3]; } a[maxn];
multiset<int> l1[maxn], l2[maxn];
map<int, int> Map[maxn]; bool vis[maxn], use[maxn];
vector<int> Root, ROOT;

inline void Maintain(int x, int y)
{
	vis[x] = true; nxt[lst] = x; pre[x] = lst; ans[x] = y; lst = x;
	if ( a[x].l == 1 ) l1[a[x].a[1]].erase(l1[a[x].a[1]].find(x));
	else { l2[a[x].a[1]].erase(l2[a[x].a[1]].find(x)); l2[a[x].a[2]].erase(l2[a[x].a[2]].find(x)); }
}

inline void Link(int x)
{
	if ( op == 0 ) p[++ cnt1] = x; else { p[-- cnt2] = x; ans[x] ^= 1; }
	op ^= 1; if ( nxt[x] ) Link(nxt[x]);
}

inline void DFS(int u)
{
	int pp = nxt[u], now = (a[u].l == 1 || ans[u] == 1) ? a[u].a[1] : a[u].a[2]; lst = u;
	int val = now;
	if ( l2[now].empty() ) return ;
	while ( !l2[now].empty() ) 
	{
		int x = *l2[now].begin();
		Maintain(x, (a[x].a[2] == now) ^ 0);
		now = a[x].a[1] + a[x].a[2] - now;
	}
	assert(now == val);
	nxt[lst] = pp; pre[pp] = lst; DFS(u);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m); 
	REP(i, 1, n) { scanf("%d", &a[i].l); REP(j, 1, a[i].l) scanf("%d", &a[i].a[j]);  }
	REP(i, 1, n) if ( !vis[i] ) 
	{
		if ( a[i].l == 1 ) l1[a[i].a[1]].insert(i);
		else { l2[a[i].a[1]].insert(i); l2[a[i].a[2]].insert(i); }
	}

	REP(i, 1, n) 
	{
		if ( vis[i] || a[i].l == 2 || l2[a[i].a[1]].empty() ) continue ; 
		int now = a[i].a[1]; Root.push_back(i); lst = i; l1[now].erase(i); vis[i] = true;
		while ( !l2[now].empty() ) 
		{
			int x = *l2[now].begin();
			Maintain(x, a[x].a[2] == now);
			now = a[x].a[1] + a[x].a[2] - now;
		}
		if ( l1[now].empty() ) use[i] = true; else Maintain(*l1[now].begin(), 0);
	}

	REP(i, 1, m)
	{
		while ( l1[i].size() >= 2 ) 
		{
			int x = *l1[i].begin(); l1[i].erase(x);
			int y = *l1[i].begin(); l1[i].erase(y);
			Root.push_back(x); nxt[x] = y; pre[y] = x; vis[x] = vis[y] = true;
		}
		if ( l1[i].size() == 1 ) 
		{
			int x = *l1[i].begin(); l1[i].erase(x);
			Root.push_back(x); use[x] = vis[x] = true;
		}
	}

	for ( auto it : Root ) 
	{
		int x = it; vector<int> b;
		while ( nxt[x] ) { b.push_back(x); x = nxt[x]; } 
		while ( !b.empty() ) { DFS(b.back()); b.pop_back(); } 
	}

	REP(i, 1, n) if ( !vis[i] ) 
	{
		int x = a[i].a[1], y = a[i].a[2];
		if ( Map[x].count(y) ) 
		{ 
			vis[i] = vis[Map[x][y]] = true; ROOT.push_back(i);
			ans[i] = 0; ans[Map[x][y]] = 0; nxt[i] = Map[x][y]; 
			Map[x].erase(y); continue ; 
		}
		if ( Map[y].count(x) ) 
		{ 
			vis[i] = vis[Map[y][x]] = true; ROOT.push_back(i);
			ans[i] = 0; ans[Map[y][x]] = 1; nxt[i] = Map[y][x]; 
			Map[y].erase(x); continue ; 
		}
		Map[x][y] = i;
	}
	REP(i, 1, n) if ( !vis[i] ) 
	{
		assert(a[i].a[1] == a[i].a[2]);
		use[i] = vis[i] = true;
		Root.push_back(i);	
	}

	cnt2 = n + 1; for ( auto it : ROOT ) Link(it);
	for ( auto it : Root ) if ( !use[it] ) Link(it); for ( auto it : Root ) if ( use[it] ) Link(it);
	REP(i, 1, n) printf("%d ", p[i]); puts("");
	REP(i, 1, n) printf("%d ", ans[p[i]]); puts("");
    return 0;
}
