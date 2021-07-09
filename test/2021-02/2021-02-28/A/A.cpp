#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson

const int maxn = 2e5 + 10;
const int N = 1e9;

int n, m, a[maxn], b[maxn], t[maxn], tot, Root[maxn], R;
long long ans;
struct node { int lson, rson, sum; } Tree[maxn << 6];
struct Node
{
	struct NODE { int lson, rson, Max; } Tree[maxn << 6];
	int tot = 0;
		
	inline void Modify(int &root, int l, int r, int pos, int val)
	{
		if ( !root ) root = ++ tot;
		Tree[root].Max = max(Tree[root].Max, val);
		if ( l == r ) return ;
		int Mid = l + r >> 1;
		if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val);
		else Modify(rs(root), Mid + 1, r, pos, val);
	}

	inline int ask(int root, int l, int r, int L, int R)
	{
		if ( L > R || !root ) return 0;
		if ( L <= l && r <= R ) return Tree[root].Max;
		int Mid = l + r >> 1, ret = 0;
		if ( L <= Mid ) ret = max(ret, ask(ls(root), l, Mid, L, R));
		if ( Mid < R ) ret = max(ret, ask(rs(root), Mid + 1, r, L, R));
		return ret;
	}
} A;

inline int Modify(int now, int l, int r, int pos, int val)
{
	int root = ++ tot; Tree[root] = Tree[now]; ++ Tree[root].sum;
	if ( l == r ) return root;
	int Mid = l + r >> 1; 
	if ( pos <= Mid ) ls(root) = Modify(ls(root), l, Mid, pos, val);
	else rs(root) = Modify(rs(root), Mid + 1, r, pos, val);
	return root;
}

inline int query(int root, int l, int r, int L, int R)
{
	if ( !root ) return Tree[root].sum;
	if ( L <= l && r <= R ) return Tree[root].sum;
	int Mid = l + r >> 1, ret = 0;
	if ( L <= Mid ) ret += query(ls(root), l, Mid, L, R);
	if ( Mid < R ) ret += query(rs(root), Mid + 1, r, L, R);
	return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n) scanf("%d%d", &a[i], &b[i]); 
	REP(i, 1, m) { scanf("%d", &t[i]); A.Modify(R, 1, N, t[i], i); }
	for ( int i = m; i >= 1; -- i ) Root[i] = Modify(Root[i + 1], 1, N, t[i], 1); 
	REP(i, 1, n)
	{
		int x = min(a[i], b[i]), y = max(a[i], b[i]);
		int pos = A.ask(R, 1, N, x, y - 1), val = query(Root[pos + 1], 1, N, y, N);
		if ( !pos ) ans += (val & 1) ? b[i] : a[i];	
		else ans += (val & 1) ? x : y;
	}
	printf("%lld\n", ans);
	return 0;
}
