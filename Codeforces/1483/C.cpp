/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 3e5 + 10;
const int INF = 1e18;

int n, h[maxn], b[maxn], Stack[maxn], top, f[maxn];
struct node { int Max, lazy; } Tree[maxn << 2];

inline void PushTag(int root, int val)
{
	Tree[root].Max += val;
	Tree[root].lazy += val;
}

inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	PushTag(lson, Tree[root].lazy);
	PushTag(rson, Tree[root].lazy);
	Tree[root].lazy = 0;
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) { PushTag(root, val); return ; } 
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
	Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
}

inline int Query(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) return Tree[root].Max;
	int Mid = l + r >> 1, ret = -INF; PushDown(root);
	if ( L <= Mid ) ret = max(ret, Query(lson, l, Mid, L, R));
	if ( Mid < R ) ret = max(ret, Query(rson, Mid + 1, r, L, R));
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &h[i]);
	REP(i, 1, n) scanf("%lld", &b[i]);
	REP(i, 1, n)
	{
		while ( top && h[Stack[top]] >= h[i] ) 
		{
			Modify(1, 1, n, Stack[top - 1] + 1, Stack[top], -b[Stack[top]]);
			-- top;
		}
		Stack[++ top] = i; Modify(1, 1, n, Stack[top - 1] + 1, Stack[top], b[Stack[top]]);
		f[i] = Query(1, 1, n, 1, i); 
		if ( i < n ) Modify(1, 1, n, i + 1, i + 1, f[i]);
	}
	printf("%lld\n", f[n]);
    return 0;
}
