#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1

const int maxn = 2e6 + 10;

int n, m, q, p[maxn], a[maxn], f[maxn], g[maxn], Root[maxn], tot; bool ans[maxn];
char s[maxn], t[maxn]; vector<pii> Q[maxn], P[maxn];
struct node { int Max; } Tree[maxn << 2];

inline void Modify(int root, int l, int r, int pos, int val)
{
	Tree[root].Max = max(Tree[root].Max, val);
	if ( l == r ) return ;
	int Mid = l + r >> 1;
	if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
	else Modify(rson, Mid + 1, r, pos, val);
}

inline int Query(int root, int l, int r, int L, int R)
{
	if ( L <= l && r <= R ) return Tree[root].Max;
	int Mid = l + r >> 1, ret = 0;
	if ( L <= Mid ) ret = max(ret, Query(lson, l, Mid, L, R));
	if ( Mid < R ) ret = max(ret, Query(rson, Mid + 1, r, L, R));
	return ret;
}

inline void Solve()
{
    int len = n + n + 1;
    REP(i, 1, len) p[i] = 0; 
    for ( int i = n; i >= 1; -- i ) s[i + i] = s[i];
    REP(i, 1, len) if ( i & 1 ) s[i] = '$';
    int Max = 0, pos = 0;
    REP(i, 1, len)
    {
        if ( Max >= i ) p[i] = min(Max - i, p[pos + pos - i]);
        while ( i - p[i] >= 1 && i + p[i] <= len && s[i - p[i]] == s[i + p[i]] ) ++ p[i];
        if ( i + p[i] > Max ) { Max = i + p[i]; pos = i; }
    }
}

struct Segment
{
	struct node { int Max, Min; } Tree[maxn << 2];

	inline void PushTag(int root, int op, int val)
	{
		if ( op == 0 ) Tree[root].Max = max(Tree[root].Max, val);
		if ( op == 1 ) Tree[root].Min = min(Tree[root].Min, val);
	}

	inline void PushDown(int root)
	{
		PushTag(lson, 0, Tree[root].Max);
		PushTag(lson, 1, Tree[root].Min);
		PushTag(rson, 0, Tree[root].Max);
		PushTag(rson, 1, Tree[root].Min);
	}

	inline void Modify(int root, int l, int r, int L, int R, int op, int val)
	{
		if ( L > R ) return ;
		if ( L <= l && r <= R ) { PushTag(root, op, val); return ; } 
		int Mid = l + r >> 1; PushDown(root);
		if ( L <= Mid ) Modify(lson, l, Mid, L, R, op, val);
		if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, op, val);
	}

	inline int Query1(int root, int l, int r, int pos)
	{
		if ( l == r ) return Tree[root].Max;
		int Mid = l + r >> 1; PushDown(root);
		if ( pos <= Mid ) return Query1(lson, l, Mid, pos);
		return Query1(rson, Mid + 1, r, pos);
	}

	inline int Query2(int root, int l, int r, int pos)
	{
		if ( l == r ) return Tree[root].Min;
		int Mid = l + r >> 1; PushDown(root);
		if ( pos <= Mid ) return Query2(lson, l, Mid, pos);
		return Query2(rson, Mid + 1, r, pos);
	}
} Seg;

int main()
{
    freopen("pass.in", "r", stdin);
    freopen("pass.out", "w", stdout);
    scanf("%d", &n); scanf("%s", t + 1); 
    REP(i, 1, n) s[i] = t[i]; Solve(); REP(i, 1, n) s[i] = t[i];
    REP(i, 3, n) a[i] = a[i - 1] + (s[i] == s[i - 2]);

	REP(i, 1, n * 4) Seg.Tree[i].Min = n + 1 + n;
	REP(i, 1, n + n - 1) if ( i & 1 ) 
	{
		int x = (i - p[i] + 2) / 2, y = (i + p[i] - 2) / 2;
		Seg.Modify(1, 1, n, (x + y) / 2 + 1, y, 0, x + y);
		Seg.Modify(1, 1, n, x, (x + y) / 2, 1, x + y);
	}
	REP(i, 1, n) { f[i] = max(0, Seg.Query1(1, 1, n, i) - i);  g[i] = min(n + 1, Seg.Query2(1, 1, n, i) - i); } 
	REP(i, 1, n) P[f[i]].push_back(pii(i, g[i]));

    scanf("%d", &q); 
    REP(i, 1, q) 
    { 
        int l, r; scanf("%d%d", &l, &r); ans[i] = true;
        if ( a[r] <= a[l + 1] ) Q[l].push_back(pii(r, i));
    }

	REP(i, 1, n)
	{
		for ( auto it : P[i - 1] ) Modify(1, 1, n, it.first, it.second);
		for ( auto it : Q[i] ) if ( Query(1, 1, n, i, it.first) > it.first ) 
			ans[it.second] = false;
	}
    REP(i, 1, q) printf("%d", ans[i]);
    return 0;
}
