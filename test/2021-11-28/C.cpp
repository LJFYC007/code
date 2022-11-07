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
typedef long long LL;
#define ull unsigned long long

const int maxn = 1e6 + 10;

int n, m, g[maxn], c[1010][1010]; ull a[maxn];
bool f[1010][1010];

inline int lowbit(int x) { return x & -x; } 
inline void add(int pos, int x, int val) { for ( int i = x; i <= 1000; i += lowbit(i) ) c[pos][i] += val; }
inline int ask(int pos, int x) { int ret = 0; for ( int i = x; i > 0; i -= lowbit(i) ) ret += c[pos][i]; return ret; }

inline void Solve(int i)
{
	g[i] = 0; int L = 1, R = 1000;
	while ( L <= R ) 
	{
		int Mid = (L + R) >> 1;
		if ( ask(i, Mid) == Mid ) { g[i] = Mid; L = Mid + 1; }
		else R = Mid - 1;
	}
}

struct node { int num[2], len, tag; ull sum, lazy1, lazy2; } Tree[maxn << 2];
#define lson root << 1
#define rson root << 1 | 1
bool flag;

inline void PushTag(int root, int op) 
{ 
	Tree[root].num[op] = Tree[root].len; Tree[root].tag = op;
	Tree[root].num[op ^ 1] = 0;
}

inline void PushTag1(int root, ull val) 
{ 
	if ( Tree[root].tag != -1 || !Tree[root].num[0] ) Tree[root].lazy2 += val;
	else Tree[root].lazy1 += val;
	Tree[root].sum += val * (Tree[root].num[0] ? Tree[root].num[0] : Tree[root].num[1]);
}

inline void PushUp(int root) 
{ 
	REP(o, 0, 1) Tree[root].num[o] = Tree[lson].num[o] + Tree[rson].num[o];
	Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
}

inline void PushDown(int root)
{
	if ( Tree[root].lazy1 ) 
	{
		if ( Tree[lson].num[0] ) PushTag1(lson, Tree[root].lazy1);
		if ( Tree[rson].num[0] ) PushTag1(rson, Tree[root].lazy1);
		Tree[root].lazy1 = 0;
	}

	if ( Tree[root].lazy2 )
	{
		Tree[lson].sum += Tree[root].lazy2 * Tree[lson].len; 
		Tree[rson].sum += Tree[root].lazy2 * Tree[rson].len; 
		Tree[lson].lazy2 += Tree[root].lazy2;
		Tree[rson].lazy2 += Tree[root].lazy2;
		Tree[root].lazy2 = 0;
	}

	if ( Tree[root].tag != -1 ) 
	{
		PushTag(lson, Tree[root].tag);
		PushTag(rson, Tree[root].tag);
		Tree[root].tag = -1;
	}
}

inline void Build(int root, int l, int r)
{
	Tree[root].len = Tree[root].num[0] = r - l + 1;
	Tree[root].tag = -1;
	if ( l == r ) return ;
	int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
}

inline void Modify(int root, int l, int r, int L, int R, int op)
{
	//cerr << root << " " << l << " " << r << " " << Tree[root].lazy1 << endl;
	if ( L <= l && r <= R ) { PushTag(root, op); return ; }
	PushDown(root);	
	int Mid = l + r >> 1;
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, op);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, op);
	PushUp(root);
}

inline int Get(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) return Tree[root].num[0];
	int ret = 0, Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) ret += Get(lson, l, Mid, L, R);
	if ( Mid < R ) ret += Get(rson, Mid + 1, r, L, R);
	return ret;
}

inline void Change(int root, int l, int r, int L, int R, ull val)
{
	if ( L <= l && r <= R ) 
	{
		//cerr << root << " " << l << " " << r << endl;
		if ( !flag || Tree[root].num[0] ) PushTag1(root, val); 
		return ;
	}
	PushDown(root);	
	int Mid = l + r >> 1;
	if ( L <= Mid ) Change(lson, l, Mid, L, R, val);
	if ( Mid < R ) Change(rson, Mid + 1, r, L, R, val);
	PushUp(root);
}

inline ull Query(int root, int l, int r, int L, int R)
{
	//cerr << root << " " << l << " " << r << endl;
	if ( L <= l && r <= R ) return Tree[root].sum;
	ull ret = 0; int Mid = l + r >> 1; PushDown(root);
	if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
	if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
	return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	if ( n > 1000 ) 
	{
		Build(1, 1, n);
		while ( m -- ) 
		{
			int op, l, r, x; scanf("%d", &op);
			if ( op == 1 )
			{
				scanf("%d%d%d", &l, &r, &x);
				assert(x == 1);
				Modify(1, 1, n, l, r, 1);
			}
			if ( op == 2 ) 
			{
				scanf("%d%d%d", &l, &r, &x);
				assert(x == 1);
				Modify(1, 1, n, l, r, 0);
			}
			if ( op == 3 ) 
			{
				scanf("%d%d", &l, &r); ull w; scanf("%llu", &w);
				flag = Get(1, 1, n, l, r);
				Change(1, 1, n, l, r, w);
			}
			if ( op == 4 ) 
			{
				scanf("%d%d", &l, &r);
				printf("%llu\n", Query(1, 1, n, l, r));
			}
		}
		return 0;
	}
	while ( m -- ) 
	{
		int op, l, r, x; scanf("%d", &op);
		if ( op == 1 )
		{
			scanf("%d%d%d", &l, &r, &x);
			REP(i, l, r) if ( !f[i][x] ) { f[i][x] = true; add(i, x, 1); Solve(i); }
		}
		if ( op == 2 ) 
		{
			scanf("%d%d%d", &l, &r, &x);
			REP(i, l, r) if ( f[i][x] ) { f[i][x] = false; add(i, x, -1); Solve(i); }
		}
		if ( op == 3 ) 
		{
			scanf("%d%d", &l, &r); ull w; scanf("%llu", &w);
			int Min = 1010;
			REP(i, l, r) Min = min(Min, g[i]);
			REP(i, l, r) if ( g[i] == Min ) a[i] += w;
		}
		if ( op == 4 ) 
		{
			scanf("%d%d", &l, &r);
			ull ret = 0; REP(i, l, r) ret += a[i];
			printf("%llu\n", ret);
		}
	}
    return 0;
}
