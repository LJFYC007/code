/***************************************************************
	File name: jump.cpp
	Author: ljfcnyali
	Create time: 2021年05月06日 星期四 20时08分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 7e4 + 10;

int n, m, w, h, dis[maxn]; pii p[maxn];
struct node { int t, L, R, D, U; } ; vector<node> a[maxn];
struct Node { set<pii> Set; } Tree[maxn << 2];
struct NODE 
{
	int dis; node a;
	bool operator < (const NODE &b) const { return dis > b.dis; } 
} ; 
priority_queue<NODE> Q;

#define lson root << 1
#define rson root << 1 | 1
inline void Modify(int root, int l, int r, int pos, pii val, int op)
{
	if ( op == 1 ) Tree[root].Set.insert(val); else Tree[root].Set.erase(val);
	if ( l == r ) return ;
	int Mid = l + r >> 1;
	if ( pos <= Mid ) Modify(lson, l, Mid, pos, val, op);
	else Modify(rson, Mid + 1, r, pos, val, op);
}

inline int Query(int root, int l, int r, int L, int R, int x, int y)
{
	auto it = Tree[root].Set.lower_bound(pii(x, 0));
	if ( it == Tree[root].Set.end() || (*it).x > y ) return 0;
	if ( l == r ) return (*it).y;
	int Mid = l + r >> 1;
	if ( L <= Mid ) { int t = Query(lson, l, Mid, L, R, x, y); if ( t ) return t; } 
	if ( Mid < R ) return Query(rson, Mid + 1, r, L, R, x, y);
	return 0;
}

int main()
{
    freopen("jump.in", "r", stdin);
    freopen("jump.out", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &w, &h);
	REP(i, 1, n) { scanf("%d%d", &p[i].x, &p[i].y); if ( i != 1 ) Modify(1, 1, w, p[i].x, pii(p[i].y, i), 1); }
	REP(i, 1, m)
	{
		int x, t, L, R, D, U; scanf("%d%d%d%d%d%d", &x, &t, &L, &R, &D, &U);
		a[x].push_back({t, L, R, D, U});
	}
	for ( auto it : a[1] ) Q.push({it.t, it});
	while ( !Q.empty() ) 
	{
		node x = Q.top().a; int dep = Q.top().dis; Q.pop();
		while ( int pos = Query(1, 1, w, x.L, x.R, x.D, x.U) )	
		{
			Modify(1, 1, w, p[pos].x, pii(p[pos].y, pos), -1);
			dis[pos] = dep;
			for ( auto it : a[pos] ) Q.push({dep + it.t, it});
		}
	}
	REP(i, 2, n) printf("%d\n", dis[i]);
    return 0;
}
