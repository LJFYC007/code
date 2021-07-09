/***************************************************************
File name: B.cpp
Author: ljfcnyali
Create time: 2021年06月20日 星期日 19时41分20秒
 ***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define int unsigned long long
typedef long long LL;

const int maxn = 5e5 + 10;
const int INF = 1e9;

int n, m, a[maxn], ans;
struct node { int Minn, Min, num, lazy1, lazy2, len, sum; } Tree[maxn << 2];

inline void PushUp(int root)
{
	Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
	if ( Tree[lson].Min < Tree[rson].Min ) 
	{
		Tree[root].num = Tree[lson].num;
		Tree[root].Minn = min(Tree[rson].Min, Tree[lson].Minn);
	}
	else if ( Tree[lson].Min > Tree[rson].Min ) 
	{
		Tree[root].num = Tree[rson].num;
		Tree[root].Minn = min(Tree[lson].Min, Tree[rson].Minn);
	}
	else 
	{
		Tree[root].num = Tree[lson].num + Tree[rson].num; 
		Tree[root].Minn = min(Tree[lson].Minn, Tree[rson].Minn); 
	}
	Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
}

inline void PushTag1(int root, int val)
{
	Tree[root].Min -= val; Tree[root].Minn -= val; Tree[root].lazy1 += val;
	Tree[root].sum -= val * Tree[root].len;	
}

inline void PushTag2(int root, int val)
{
	Tree[root].Minn -= val; Tree[root].lazy2 += val;
	Tree[root].sum -= val * (Tree[root].len - Tree[root].num);	
}

inline void PushDown(int root)
{
	if ( Tree[root].lazy1 ) 
	{
		PushTag1(lson, Tree[root].lazy1); PushTag1(rson, Tree[root].lazy1);
		Tree[root].lazy1 = 0;
	}
	if ( Tree[root].lazy2 ) 
	{
		if ( Tree[lson].Min == Tree[root].Min ) PushTag2(lson, Tree[root].lazy2); 
		else PushTag1(lson, Tree[root].lazy2);
		if ( Tree[rson].Min == Tree[root].Min ) PushTag2(rson, Tree[root].lazy2); 
		else PushTag1(rson, Tree[root].lazy2);
		Tree[root].lazy2 = 0;
	}
}

inline void Build(int root, int l, int r, int val)
{
	Tree[root].len = r - l + 1;
	if ( l == r ) 
	{
		Tree[root].Minn = -1; Tree[root].num = 1;
		Tree[root].Min = Tree[root].sum = a[l]; 
		return ;
	}
	int Mid = l + r >> 1; Build(lson, l, Mid, val); Build(rson, Mid + 1, r, val);
	PushUp(root);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) 
	{
		if ( Tree[root].Min > val ) { PushTag1(root, val); return ; } 
		if ( Tree[root].Min == val && Tree[root].Minn - Tree[root].Min >= val ) { PushTag2(root, val); return ; } 
	}
	if ( l == r ) { Tree[root].Min -= val; Tree[root].sum -= val; return ; }
	int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
	PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) return Tree[root].sum;
	int Mid = l + r >> 1, ret = 0; PushDown(root);
	if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
	if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%llu%llu", &n, &m); 
	REP(i, 1, n) scanf("%llu", &a[i]);
	Build(1, 1, n, 1);
	while ( m -- ) 
	{
		int op, l, r, x; scanf("%llu%llu%llu", &op, &l, &r);
		ans %= (1 << 20); l ^= ans; r ^= ans;
		if ( op == 1 ) 
		{
			scanf("%llu", &x); x ^= ans; 
			Modify(1, 1, n, l, r, x);
		}
		else
		{
			ans = Query(1, 1, n, l, r);
			printf("%llu\n", ans);
		}
	}
	return 0;
}
