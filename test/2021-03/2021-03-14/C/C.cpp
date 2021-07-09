/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年03月14日 星期日 08时25分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 2e5 + 10;

int n, q, a[maxn], M[2];
struct node { int Max, sum[2], tag[2]; } Tree[maxn << 2];

inline void PushUp(int root)
{
	Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
	Tree[root].sum[0] = Tree[lson].sum[0] & Tree[rson].sum[0];	
	Tree[root].sum[1] = Tree[lson].sum[1] | Tree[rson].sum[1];	
}

inline void PushTag(int root, int val, int op)
{
	if ( op == 0 ) 
	{ 
		Tree[root].Max &= val; 
		Tree[root].tag[0] &= val; Tree[root].tag[1] &= val;
		Tree[root].sum[0] &= val; Tree[root].sum[1] &= val; 
	}
	if ( op == 1 ) 
	{ 
		Tree[root].Max |= val; 
		Tree[root].tag[0] |= val; Tree[root].tag[1] |= val;
		Tree[root].sum[0] |= val; Tree[root].sum[1] |= val; 
	}
}

inline void PushDown(int root)
{
	REP(i, 0, 1) if ( Tree[root].tag[i] != M[i] ) 
	{
		PushTag(lson, Tree[root].tag[i], i);
		PushTag(rson, Tree[root].tag[i], i);
		Tree[root].tag[i] = M[i];
	}
}

inline void Build(int root, int l, int r)
{
	REP(i, 0, 1) Tree[root].tag[i] = M[i];
	if ( l == r ) { Tree[root].sum[0] = Tree[root].sum[1] = Tree[root].Max = a[l]; return ; } 
	int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
	PushUp(root);
}

inline void Modify(int root, int l, int r, int L, int R, int val, int op)
{
	if ( op == 0 && (Tree[root].sum[1] & val) == Tree[root].sum[1] ) return ; 
	if ( op == 1 && (Tree[root].sum[0] | val) == Tree[root].sum[0] ) return ; 
	if ( L <= l && r <= R ) 
	{
		if ( op == 0 && (Tree[root].sum[0] & val) == (Tree[root].sum[1] & val) ) { PushTag(root, val, op); return ; } 
		if ( op == 1 && (Tree[root].sum[0] | val) == (Tree[root].sum[1] | val) ) { PushTag(root, val, op); return ; } 
	}
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val, op);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val, op);
	PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) return Tree[root].Max;
	int Mid = l + r >> 1, ret = 0; PushDown(root);
	if ( L <= Mid ) ret = max(ret, Query(lson, l, Mid, L, R));
	if ( Mid < R ) ret = max(ret, Query(rson, Mid + 1, r, L, R));
	return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	M[0] = (1 << 21) - 1; M[1] = 0;
	scanf("%d%d", &n, &q);
	REP(i, 1, n) scanf("%d", &a[i]);	
	Build(1, 1, n);
	while ( q -- ) 
	{
		int op, l, r, x; scanf("%d%d%d", &op, &l, &r);
		if ( op == 1 ) { scanf("%d", &x); Modify(1, 1, n, l, r, x, 0); }
		if ( op == 2 ) { scanf("%d", &x); Modify(1, 1, n, l, r, x, 1); }
		if ( op == 3 ) printf("%d\n", Query(1, 1, n, l, r));
		// REP(i, 1, n) printf("%d ", Query(1, 1, n, i, i)); puts("");
	}
    return 0;
}
