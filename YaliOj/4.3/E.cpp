/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年05月30日 星期四 15时31分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 4000010;

struct node
{
	int l, r, len;
	LL val, lazy1, lazy2;
} Tree[maxn];

int Mod, n, m, a[maxn];

inline void Push_up(int root)
{
	Tree[root].val = (Tree[lson].val + Tree[rson].val) % Mod;
}

inline void Push_down(int root)
{
	if ( Tree[root].lazy1 == 0 && Tree[root].lazy2 == 1 ) return ;
	LL val1 = Tree[root].lazy1, val2 = Tree[root].lazy2;

	Tree[root].lazy1 = 0; Tree[root].lazy2 = 1;

	if ( Tree[root].l != Tree[root].r ) 
	{
		Tree[lson].lazy2 *= val2; Tree[lson].lazy2 %= Mod;
		Tree[rson].lazy2 *= val2; Tree[rson].lazy2 %= Mod;
		Tree[lson].lazy1 = Tree[lson].lazy1 * val2 + val1; Tree[lson].lazy1 %= Mod;
		Tree[rson].lazy1 = Tree[rson].lazy1 * val2 + val1; Tree[rson].lazy1 %= Mod;
	}

	Tree[root].val = (Tree[root].val * val2 + Tree[root].len * val1) % Mod;
}

inline void Build(int root, int l, int r)
{
	Tree[root].l = l; Tree[root].r = r; Tree[root].len = r - l + 1;
	Tree[root].lazy1 = 0; Tree[root].lazy2 = 1;
	if ( l == r ) 
	{
		Tree[root].val = a[l];
		return ;
	}
	int Mid = l + r >> 1;
	Build(lson, l, Mid);
	Build(rson, Mid + 1, r);
	Push_up(root);
}

inline void Update(int root, int L, int R, int p, int val)
{
	Push_down(root);
//	if ( Tree[root].lazy2 == 0 ) Tree[root].lazy2 = 1;
	if ( Tree[root].l >= L && Tree[root].r <= R ) 
	{
		if ( p == 2 ) 
		{
			Tree[root].lazy1 *= val; Tree[root].lazy1 %= Mod;
			Tree[root].lazy2 *= val; Tree[root].lazy2 %= Mod;
		}
		else { Tree[root].lazy1 += val; Tree[root].lazy1 %= Mod; }
		return ;			
	}
	int Mid = Tree[root].l + Tree[root].r >> 1;
	if ( L <= Mid ) Update(lson, L, R, p, val);
	if ( Mid + 1 <= R ) Update(rson, L, R, p, val);
	Push_down(lson); Push_down(rson);
	Push_up(root);
}

inline LL Query(int root, int L, int R)
{
//	if ( Tree[root].lazy2 == 0 ) Tree[root].lazy2 = 1;
	Push_down(root);
	if ( Tree[root].l >= L && Tree[root].r <= R ) return Tree[root].val;
	int Mid = Tree[root].l + Tree[root].r >> 1;
	LL sum = 0;
	if ( L <= Mid ) sum += Query(lson, L, R);
	if ( Mid + 1 <= R ) sum += Query(rson, L, R);
	sum %= Mod;
	return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &Mod);
	REP(i, 1, n) scanf("%d", &a[i]);
	Build(1, 1, n);
	scanf("%d", &m);
	REP(i, 1, m)
	{
		int k, l, r; scanf("%d%d%d", &k, &l, &r);
		if ( k == 3 ) printf("%lld\n", Query(1, l, r) % Mod);
		else 
		{
			int val; scanf("%d", &val);
			Update(1, l, r, 3 - k, val);
		}
	}
    return 0;
}
