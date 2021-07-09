/***************************************************************
	File name: LibreOJ_6620.cpp
	Author: ljfcnyali
	Create time: 2021年03月30日 星期二 16时13分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 5e5 + 10;
const double INF = 1e18;

int n, sum1, sum2, tot; double ans;
struct node { int a, b; double x; } a[maxn];
struct Node { int lson, rson, size, suma, sumb, val, rnk, a, b; double x; } Tree[maxn];

inline void PushUp(int root)
{
	Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + Tree[root].val;
	Tree[root].suma = Tree[ls(root)].suma + Tree[rs(root)].suma + Tree[root].a;
	Tree[root].sumb = Tree[ls(root)].sumb + Tree[rs(root)].sumb + Tree[root].b;
}

inline int NewNode(int i)
{
	++ tot; Tree[tot].val = a[i].a; Tree[tot].rnk = rand();
	Tree[tot].a = a[i].a; Tree[tot].b = a[i].b; Tree[tot].x = a[i].x;
	PushUp(tot); return tot;
}

inline void Split(int root, int &a, int &b, double val)
{
	if ( !root ) { a = b = 0; return ; }
	if ( Tree[root].x <= val ) { a = root; Split(rs(a), rs(a), b, val); PushUp(a); }
	else { b = root; Split(ls(b), a, ls(b), val); PushUp(b); } 
}

inline void Merge(int &root, int a, int b)
{
	if ( !a || !b ) { root = a + b; return ; } 
	if ( Tree[a].rnk < Tree[b].rnk ) { root = a; Merge(rs(a), rs(a), b); } 
	else { root = b; Merge(ls(b), a, ls(b)); }
	PushUp(root);
}

inline void Query(int root, int k, int s1, int s2)
{
	if ( ls(root) && k <= Tree[ls(root)].size ) { Query(ls(root), k, s1, s2); return ; } 
	k -= Tree[ls(root)].size + Tree[root].val; s1 += Tree[ls(root)].suma + Tree[root].a; s2 += Tree[ls(root)].sumb + Tree[root].b;
	if ( k <= 0 ) ans = Tree[root].x * (s1 + s1 - sum1) + (s2 + s2 - sum2);
	else Query(rs(root), k, s1, s2);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &a[i].a); REP(i, 1, n) scanf("%lld", &a[i].b);
	REP(i, 1, n) if ( a[i].a < 0 ) { a[i].a = -a[i].a; a[i].b = -a[i].b; } 
	REP(i, 1, n) a[i].x = -(double)a[i].b / a[i].a;
	int Root = 0;
	REP(i, 1, n)
	{
		ans = INF; sum1 += a[i].a; sum2 += a[i].b;
		int A, B, C; Split(Root, A, B, a[i].x); C = NewNode(i); Merge(B, C, B); Merge(Root, A, B);
		Query(Root, sum1 / 2, 0, 0); printf("%.6lf\n", ans);
	}
    return 0;
}
