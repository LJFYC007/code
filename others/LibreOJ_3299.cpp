#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1

const int maxn = 2e6 + 10;

int Q, tot, p[maxn];
struct Node { int op, t, x, y, id; } q[maxn];
struct FHQ
{
	struct node { int Min, Max, lazy; } Tree[maxn << 2];

	inline void PushTag(const int root, const int val) 
	{ 
		Tree[root].Max += val; 
		Tree[root].Min += val; 
		Tree[root].lazy += val; 
	}

	inline void PushDown(const int root)
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
		Tree[root].Min = Tree[lson].Min;
		Tree[root].Max = Tree[rson].Max;
	}
	
	inline int Find(int root, int l, int r, int pos)
	{
		if ( l == r ) return l;
		int Mid = l + r >> 1; PushDown(root);
		if ( Tree[lson].Max > pos ) return Find(lson, l, Mid, pos);
		return Find(rson, Mid + 1, r, pos);
	}

	inline int Get2(int root, int l, int r, int pos)
	{
		if ( l == r ) return l;
		int Mid = l + r >> 1; PushDown(root);
		if ( Tree[rson].Min >= pos ) return Get2(rson, Mid + 1, r, pos);
		return Get2(lson, l, Mid, pos);
	}
} A, B;

inline int Query(int root, int l, int r)
{
	if ( l == r ) return l;
	int Mid = l + r >> 1; A.PushDown(root); B.PushDown(root);
	if ( A.Tree[rson].Min <= B.Tree[rson].Min ) return Query(rson, Mid + 1, r);
	return Query(lson, l, Mid);
}

inline void Update(int root, int l, int r, int pos, int &ans, int &x)
{
	if ( l == r ) 
	{
		int sum = min(A.Tree[root].lazy, B.Tree[root].lazy);
		if ( sum > ans || (sum == ans && l > x) ) { ans = sum; x = l; }
		return ;
	}
	int Mid = l + r >> 1; A.PushDown(root); B.PushDown(root);
	if ( pos <= Mid ) Update(lson, l, Mid, pos, ans, x);
	else Update(rson, Mid + 1, r, pos, ans, x);
}

inline void Find(int root, int l, int r, int pos, int &sum1, int &sum2)
{
	if ( l == r ) 
	{
		sum1 = A.Tree[root].lazy;
		sum2 = B.Tree[root].lazy;
		return ;
	}
	int Mid = l + r >> 1; A.PushDown(root); B.PushDown(root);
	if ( pos <= Mid ) Find(lson, l, Mid, pos, sum1, sum2);
	else Find(rson, Mid + 1, r, pos, sum1, sum2);
}

inline void read(int &x)
{
	x = 0; char c = getchar();
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
	scanf("%d", &Q);
	int N = 2000000;
	REP(o, 1, Q)
	{
        read(q[o].op);
        if ( q[o].op == 1 ) { read(q[o].t); read(q[o].x); read(q[o].y); }
        else read(q[o].t);
        q[o].id = o;
    }
    sort(q + 1, q + Q + 1, [](Node a, Node b) { return a.x < b.x; });
    tot = 1;
    REP(o, 1, Q)
    {
        if ( q[o].x == 0 ) continue ;
        int val = q[o].x;
        p[tot] = q[o].x; q[o].x = tot; 
        if ( val != q[o + 1].x ) ++ tot;
    }
    sort(q + 1, q + Q + 1, [](Node a, Node b) { return a.id < b.id; });
    REP(o, 1, Q)
    {
        int op = q[o].op;
		if ( op == 1 ) 
		{
			if ( q[o].t == 0 ) A.Modify(1, 1, N, q[o].x, N, q[o].y);
			else B.Modify(1, 1, N, 1, q[o].x, q[o].y);
		}
		else 
		{
            int x = q[o].t;
			if ( q[x].t == 0 ) A.Modify(1, 1, N, q[x].x, N, -q[x].y);
			else B.Modify(1, 1, N, 1, q[x].x, -q[x].y);
		}
		int pos = Query(1, 1, N), ans = 0;
		Update(1, 1, N, pos, ans, pos);

		int sum1, sum2; 
		Find(1, 1, N, pos + 1, sum1, sum2);
		int x = A.Find(1, 1, N, sum1), y = B.Get2(1, 1, N, sum2);
		Update(1, 1, N, x, ans, pos);
		Update(1, 1, N, y, ans, pos);

		if ( !ans ) puts("Peace");
		else printf("%d %d\n", p[pos], ans * 2);
	}
	return 0;
}
