/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年06月23日 星期三 19时51分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e4 + 10;

int n, m, a[maxn], tot;
struct node { int lson, rson, size, val, lazy, rk; LL sum[30]; } Tree[maxn * 70];

inline void PushUp(int root)
{
	Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1;
	int x = Tree[root].val;
	REP(i, 0, 29)
	{
		Tree[root].sum[i] = Tree[ls(root)].sum[i] + Tree[rs(root)].sum[i] + x;
		x /= 2;
	}
}

inline void PushTag(int root)
{
	++ Tree[root].lazy; Tree[root].val /= 2;
	REP(i, 1, 29) Tree[root].sum[i - 1] = Tree[root].sum[i];
	Tree[root].sum[29] = 0;
}

inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	if ( ls(root) ) { ++ tot; Tree[tot] = Tree[ls(root)]; ls(root) = tot; Tree[tot].rk = rand(); }
	if ( rs(root) ) { ++ tot; Tree[tot] = Tree[rs(root)]; rs(root) = tot; Tree[tot].rk = rand(); }
	while ( Tree[root].lazy ) 
	{
		if ( ls(root) ) PushTag(ls(root));
		if ( rs(root) ) PushTag(rs(root));
		-- Tree[root].lazy;
	}
}

inline void Merge(int &root, int a, int b)
{
	root = ++ tot;
	if ( !a || !b ) { Tree[root] = Tree[a + b]; Tree[root].rk = rand(); return ; } 
	if ( Tree[a].rk < Tree[b].rk ) 
	{
		PushDown(a); Tree[root] = Tree[a]; Tree[root].rk = rand();
		Merge(rs(root), rs(root), b);
	}
	else
	{
		PushDown(b); Tree[root] = Tree[b]; Tree[root].rk = rand();
		Merge(ls(root), a, ls(root));
	}
	PushUp(root); 
}

inline void Split(int root, int &a, int &b, int k)
{
	if ( !root ) { a = b = 0; return ; } 
	PushDown(root);
	if ( Tree[ls(root)].size + 1 <= k ) 
	{
		a = ++ tot; Tree[a] = Tree[root]; Tree[a].rk = rand();
		Split(rs(a), rs(a), b, k - Tree[ls(root)].size - 1); PushUp(a);
	}
	else
	{
		b = ++ tot; Tree[b] = Tree[root]; Tree[b].rk = rand();
		Split(ls(b), a, ls(b), k); PushUp(b);
	}
}

inline int NewNode(int val)
{
	++ tot; Tree[tot].rk = rand();
	Tree[tot].val = val; PushUp(tot);
	return tot;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); int Root = 0;
	REP(i, 1, n) { scanf("%d", &a[i]); Merge(Root, Root, NewNode(a[i])); }
	scanf("%d", &m);
	while ( m -- ) 
	{
		int op, l, r, x; scanf("%d%d%d", &op, &l, &r);
		int a, b, c, A, B, C;
		if ( op == 1 ) 
		{
			scanf("%d", &x); 	
			Split(Root, a, c, r); Split(a, a, b, l - 1); A = b;
			Split(Root, a, c, x + r - l); Split(Root, a, b, x - 1); 
			Merge(Root, a, A); Merge(Root, Root, c);
		}
		if ( op == 2 ) 
		{
			Split(Root, a, c, r); Split(a, a, b, l - 1);
			x = ++ tot; Tree[x] = Tree[b]; Tree[x].rk = rand(); PushTag(x);
			Merge(Root, a, x); Merge(Root, Root, c);
		}
		if ( op == 3 ) 
		{
			Split(Root, a, c, r); 
			Split(a, a, b, l - 1);
			printf("%lld\n", Tree[b].sum[0]);
		}
	}
    return 0;
}
