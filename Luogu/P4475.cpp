/***************************************************************
	File name: P4475.cpp
	Author: ljfcnyali
	Create time: 2021年04月07日 星期三 19时10分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e9;

int n, m, D, tot, Root;
struct node { int x[2], h; bool operator < (const node &a) const { return x[D] < a.x[D]; } } a[maxn];
struct Node { int lson, rson, Min[2], Max[2], sum; node t; } Tree[maxn << 2];

inline void PushUp(int root)
{
	REP(i, 0, 1)
	{
		Tree[root].Min[i] = Tree[root].Max[i] = Tree[root].t.x[i];
		Tree[root].Min[i] = min(Tree[root].Min[i], Tree[ls(root)].Min[i]);
		Tree[root].Min[i] = min(Tree[root].Min[i], Tree[rs(root)].Min[i]);
		Tree[root].Max[i] = max(Tree[root].Max[i], Tree[ls(root)].Max[i]);
		Tree[root].Max[i] = max(Tree[root].Max[i], Tree[rs(root)].Max[i]);
	}
	Tree[root].sum = Tree[ls(root)].sum + Tree[rs(root)].sum + Tree[root].t.h;
}

inline void Build(int &root, int l, int r, int op)
{
	if ( l > r ) return ; if ( !root ) root = ++ tot;
	int Mid = l + r >> 1; D = op; nth_element(a + l, a + Mid, a + r + 1);
	Tree[root].t = a[Mid]; 
	Build(ls(root), l, Mid - 1, op ^ 1);
	Build(rs(root), Mid + 1, r, op ^ 1);
	PushUp(root);
}

inline int Get(node t, int a, int b, int c) { return t.x[0] * a + t.x[1] * b < c ? t.h : 0; }

inline int Query(int root, int a, int b, int c)
{
	if ( !root ) return 0;
	int val = max(Tree[root].Min[0] * a, Tree[root].Max[0] * a) + max(Tree[root].Min[1] * b, Tree[root].Max[1] * b);
	if ( val < c ) return Tree[root].sum;
	val = min(Tree[root].Min[0] * a, Tree[root].Max[0] * a) + min(Tree[root].Min[1] * b, Tree[root].Max[1] * b);
	if ( val >= c ) return 0;
	return Query(ls(root), a, b, c) + Query(rs(root), a, b, c) + Get(Tree[root].t, a, b, c);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n) { int x, y, h; scanf("%lld%lld%lld", &a[i].x[0], &a[i].x[1], &a[i].h); }
	Tree[0].Min[0] = Tree[0].Min[1] = INF;
	Tree[0].Max[0] = Tree[0].Max[1] = -INF;
	Build(Root, 1, n, 0);
	REP(i, 1, m) 
	{
		int a, b, c; scanf("%lld%lld%lld", &a, &b, &c);
		printf("%lld\n", Query(1, a, b, c));
	}
    return 0;
}
