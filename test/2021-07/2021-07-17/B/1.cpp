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

int n, m, q, tot, cnt, anc[maxn][20]; LL c[maxn], ans[maxn];
struct node { int op, l, r, x, y; } Q[maxn];
vector<pii> b[maxn]; pii a[maxn], val[maxn];
map<int, int> Map[maxn]; bool vis[maxn];

inline int lowbit(int x) { return x & -x; } 
inline void modify(int pos, int val) { for ( int i = pos; i <= m; i += lowbit(i) ) c[i] += val; } 
inline LL query(int pos) { LL ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[i]; return ret; } 

struct Node { int lson, rson, lazy; } Tree[maxn * 50];
int Root[maxn]; 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson

inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	if ( !ls(root) ) ls(root) = ++ cnt; Tree[ls(root)].lazy = Tree[root].lazy;
	if ( !rs(root) ) rs(root) = ++ cnt; Tree[rs(root)].lazy = Tree[root].lazy;
	Tree[root].lazy = 0;
}

inline int Modify(int now, int l, int r, int L, int R, int val)
{
	int root = ++ cnt; Tree[root] = Tree[now];
	if ( L <= l && r <= R ) { Tree[root].lazy = val; return root; }
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) ls(root) = Modify(ls(root), l, Mid, L, R, val);
	if ( Mid < R ) rs(root) = Modify(rs(root), Mid + 1, r, L, R, val);
	return root;
}

inline int Query(int root, int l, int r, int pos)
{
	if ( l == r || !root ) return Tree[root].lazy;
	int Mid = l + r >> 1; PushDown(root);
	if ( pos <= Mid ) return Query(ls(root), l, Mid, pos);
	return Query(rs(root), Mid + 1, r, pos);
}

inline void NewNode(int x, int y) 
{
	if ( Map[x].count(y)) return ;
	Map[x][y] = ++ tot;
	int t = Query(Root[x], 1, n, y);
	if ( Q[t].op == 1 ) 
	{
		anc[tot][0] = Map[t - 1][Q[t].x + Q[t].y - y];
		REP(i, 1, 19) anc[tot][i] = anc[anc[tot][i - 1]][i - 1];
	}
	else { anc[tot][0] = 0; val[tot] = pii(Q[t].x, t); }
}

int main()
{
	n = m = q = 400000;
	REP(i, 1, m)
	{
		Q[i].op = rand() % 3 + 1;
		if ( Q[i].op == 1 ) { Q[i].x = rand() % n + 1; Q[i].y = rand() % n + 1; }
		if ( Q[i].op == 2 ) 
		{
			 Q[i].l = rand() % n + 1; Q[i].r = rand() % n + 1;
			if ( Q[i].l > Q[i].r ) swap(Q[i].l, Q[i].r);
			 Q[i].x = rand() % n + 1;
		}
		if ( Q[i].op == 3 ) Q[i].x = rand() % n + 1;
	}
	REP(i, 1, q) { int l, r; l = rand() % n + 1; r = rand() % n + 1; if ( l > r ) swap(l, r); b[r].push_back(pii(l, i)); }

	REP(t, 1, m)
	{
		Root[t] = Root[t - 1];
		if ( Q[t].op == 1 ) 
		{
			int x = Q[t].x, y = Q[t].y;
			if ( x != y ) 
			{
				Root[t] = Modify(Root[t], 1, n, x, x, t);
				Root[t] = Modify(Root[t], 1, n, y, y, t);
				NewNode(t - 1, x); NewNode(t - 1, y);
				NewNode(t, x); NewNode(t, y);
			}
		}
		if ( Q[t].op == 2 ) Root[t] = Modify(Root[t], 1, n, Q[t].l, Q[t].r, t);
		if ( Q[t].op == 3 ) 
		{
			int x = Q[t].x, y = Query(Root[t], 1, n, x);
			if ( Q[y].op == 2 ) modify(m - y + 1, Q[y].x);
			else
			{
				x = Map[y][x];
				for ( int i = 19; i >= 0; -- i ) if ( anc[x][i] ) x = anc[x][i];
				modify(m - val[x].second + 1, val[x].first);
			}
		}
		for ( auto it : b[t] ) ans[it.second] = query(m - it.first + 1);
	}

	REP(i, 1, q) printf("%lld\n", ans[i]);
    return 0;
}
