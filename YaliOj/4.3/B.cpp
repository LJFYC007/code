/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月30日 星期四 09时17分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1

const int maxn = 4000010;

struct node
{
	int l, r;
	long long val, lazy;
} Tree[maxn];

int a[maxn], n, m, cnt;

inline void Push_up(int root) 
{
	Tree[root].val = Tree[lson].val + Tree[rson].val;
}

inline void Build(int root, int l, int r)
{
	Tree[root].l = l; Tree[root].r = r;
	Tree[root].val = Tree[root].lazy = 0;
	if ( l == r ) { Tree[root].val = a[l]; return ; }
	int Mid = l + r >> 1;
	Build(lson, l, Mid);
	Build(rson, Mid + 1, r);
	Push_up(root);
}

inline void Push_down(int root)
{
	if ( Tree[root].lazy == 0 ) return ;
	Tree[lson].lazy += Tree[root].lazy;
	Tree[lson].val += (Tree[lson].r - Tree[lson].l + 1) * Tree[root].lazy;
	Tree[rson].lazy += Tree[root].lazy;
	Tree[rson].val += (Tree[rson].r - Tree[rson].l + 1) * Tree[root].lazy;
	Tree[root].lazy = 0;
}

inline void Insert(int root, int L, int R, int l, int r, int val)
{
	if ( l <= L && R <= r ) 
	{
		Tree[root].lazy += val;
		Tree[root].val += 1LL * (R - L + 1) * val;
		return ;
	}
	Push_down(root);
	int Mid = L + R >> 1;
	if ( l > Mid ) Insert(rson, Mid + 1, R, l, r, val);
	else if ( r <= Mid ) Insert(lson, L, Mid, l, r, val);
	else
	{
		Insert(lson, L, Mid, l, r, val);
		Insert(rson, Mid + 1, R, l, r, val);
	}
	Push_up(root);
}

inline long long Query(int root, int L, int R, int l, int r)
{
	if ( l <= L && R <= r ) return Tree[root].val;
	Push_down(root);
	int Mid = L + R >> 1;
	long long sum = 0;
	if ( l > Mid ) sum += Query(rson, Mid + 1, R, l, r);
	else if ( r <= Mid ) sum += Query(lson, L, Mid, l, r);
	else 
	{
		sum += Query(lson, L, Mid, l, r);
		sum += Query(rson, Mid + 1, R, l, r);
	}
	return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n) scanf("%d", &a[i]);
	Build(1, 1, n);
	REP(i, 1, m)
	{
		int k; scanf("%d", &k);
		if ( k == 1 ) 
		{
			int l, r, x; scanf("%d%d%d", &l, &r, &x);
			Insert(1, 1, n, l, r, x);
		}
		else 
		{
			int l, r; scanf("%d%d", &l, &r);
			printf("%lld\n", Query(1, 1, n, l, r));
		}
//		REP(j, 1, 9) printf("%d %d %d %d\n", Tree[j].l, Tree[j].r, Tree[j].val, Tree[j].lazy);
//		puts("");
	}
    return 0;
}
