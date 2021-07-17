/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年07月17日 星期六 10时06分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, q, tot, cnt, anc[maxn * 4][20]; LL c[maxn], ans[maxn];
struct node { int op, l, r, x, y; } Q[maxn];
vector<pii> b[maxn]; pii val[maxn * 4];
pii Map[maxn][4];

inline int lowbit(int x) { return x & -x; } 
inline void modify(int pos, int val) { for ( int i = pos; i <= m; i += lowbit(i) ) c[i] += val; } 
inline LL query(int pos) { LL ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[i]; return ret; } 

struct Node { int lson, rson, lazy; } Tree[maxn << 2];
#define lson root << 1
#define rson root << 1 | 1

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) { Tree[root].lazy = val; return ; }
	int Mid = l + r >> 1; 
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
	return ;
}

inline int Query(int root, int l, int r, int pos)
{
	if ( l == r ) return Tree[root].lazy;
	int Mid = l + r >> 1; 
	if ( pos <= Mid ) return max(Tree[root].lazy, Query(lson, l, Mid, pos));
	return max(Tree[root].lazy, Query(rson, Mid + 1, r, pos));
}

inline int Find(int x, int y)
{
	REP(i, 0, 3) if ( Map[x][i].first == y ) 
		return Map[x][i].second;
	return 0;
}

inline void NewNode(int x, int y) 
{
	REP(i, 0, 3) if ( Map[x][i].first == y ) return ;
	REP(i, 0, 3) if ( !Map[x][i].first ) { Map[x][i] = pii(y, ++ tot); break ; }
	int t = Query(1, 1, n, y);
	if ( Q[t].op == 1 ) 
	{
		anc[tot][0] = Find(t - 1, Q[t].x + Q[t].y - y);
		REP(i, 1, 19) anc[tot][i] = anc[anc[tot][i - 1]][i - 1];
	}
	else { anc[tot][0] = 0; val[tot] = pii(Q[t].x, t); }
}

inline void read(int &x)
{
	x = 0; char c = getchar();
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	read(n); read(m); read(q);
	bool flag = true;
	REP(i, 1, m)
	{
		read(Q[i].op);
		if ( Q[i].op == 1 ) read(Q[i].x), read(Q[i].y);
		if ( Q[i].op == 2 ) read(Q[i].l), read(Q[i].r), read(Q[i].x);
		if ( Q[i].op == 2 ) flag = false;
		if ( Q[i].op == 3 ) read(Q[i].x);
	}
	REP(i, 1, q) { int l, r; read(l); read(r); b[r].push_back(pii(l, i)); }
	if ( flag ) 
	{
		REP(i, 1, q) puts("0");
		return 0;
	}

	REP(t, 1, m)
	{
		if ( Q[t].op == 1 ) 
		{
			int x = Q[t].x, y = Q[t].y;
			if ( x != y ) 
			{
				NewNode(t - 1, x); NewNode(t - 1, y);
				Modify(1, 1, n, x, x, t);
				Modify(1, 1, n, y, y, t);
				NewNode(t, x); NewNode(t, y);
			}
		}
		if ( Q[t].op == 2 ) Modify(1, 1, n, Q[t].l, Q[t].r, t);
		if ( Q[t].op == 3 ) 
		{
			int x = Q[t].x, y = Query(1, 1, n, x);
			if ( Q[y].op == 2 ) modify(m - y + 1, Q[y].x);
			else
			{
				x = Find(y, x);
				for ( int i = 19; i >= 0; -- i ) if ( anc[x][i] ) x = anc[x][i];
				modify(m - val[x].second + 1, val[x].first);
			}
		}
		for ( auto it : b[t] ) ans[it.second] = query(m - it.first + 1);
	}

	REP(i, 1, q) printf("%lld\n", ans[i]);
    return 0;
}
