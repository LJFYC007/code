/***************************************************************
	File name: LibreOJ_2492.cpp
	Author: ljfcnyali
	Create time: 2021年03月30日 星期二 08时15分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, a[maxn];
struct node 
{
	int sum[2][3], val[2][2][2], ans, len[2];
} Tree[maxn << 2];

inline int calc(int ls, int rs, int x, int y)
{
	int ret = 0;
	ret += Tree[ls].sum[x][0] * max(0ll, Tree[rs].len[y] - 2);
	ret += Tree[ls].sum[x][1] * max(0ll, Tree[rs].len[y] - 1);
	ret += Tree[rs].sum[x][2] * Tree[rs].len[y];
	REP(i, 0, 1) REP(j, 0, 1) REP(k, 0, 1 - j)
		ret += Tree[ls].val[x][i][j] * Tree[rs].val[y][i ^ 1][k];
	return ret;
}

inline void Maintain(int root, int ls, int rs, int x)
{
	Tree[root].
}

inline void PushUp(int root)
{
	Tree[root].ans = Tree[lson].ans + Tree[rson].ans + calc(lson, rson, 1, 0) + calc(rson, lson, 0, 1);
	Maintain(root, lson, rson, 0);
	Maintain(root, rson, lson, 1);
}

inline void Modify(int root, int l, int r, int pos, int val)
{
	if ( l == r ) 
	{
		REP(o, 0, 1)
		{
			Tree[root].len[o] = (val == 0);
			REP(i, 0, 2) Tree[root].sum[o][i] = 0;
			REP(i, 0, 1) REP(j, 0, 1) Tree[root].val[o][i][j] = 0;
			if ( val == 1 ) Tree[root].sum[o][0] = 1;
			Tree[root].val[o][0][0] = 1;
			if ( val == 1 ) Tree[root].val[o][1][0] = 1;
			else Tree[root].val[o][0][1] = 1;
		}
		Tree[root].ans = (val == 1);
		return ;
	}
	int Mid = l + r >> 1;
	if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
	else Modify(rson, Mid + 1, r, pos, val);
	PushUp(root);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) { scanf("%d", &a[i]); Modify(1, 1, n, i, a[i]); } 
	scanf("%d", &m);
	REP(i, 1, m)
	{
		int op, l, r, x; scanf("%d", &op);
		if ( op == 1 ) { scanf("%d", &x); a[x] ^= 1; Modify(1, 1, n, x, a[x]); } 
		if ( op == 2 ) 
		{
			scanf("%d%d", &l, &r);
			printf("%d\n", Query(1, 1, n, l, r));
		}
	}
    return 0;
}
