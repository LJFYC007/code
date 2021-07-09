#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1

const int maxn = 1e6 + 10;
const int INF = 2e9 + 10;

int n, m, a[maxn], b[maxn], ans = INF, num, val, p[maxn];
pii c[maxn];
struct node { int Min, Max, sum; bool tag; } Tree[maxn << 2];

inline void PushUp(int root)
{
	Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
	Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
	Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
	Tree[root].tag = Tree[lson].tag | Tree[rson].tag;
}

inline void Build(int root, int l, int r)
{
	if ( l == r ) { Tree[root].Max = Tree[root].Min = b[l]; Tree[root].sum = 1; Tree[root].tag = a[l] < b[l]; return ; } 
	int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r); PushUp(root);
}

inline void Modify(int root, int l, int r, int pos, int val)
{
	if ( l == r ) 
	{ 
		if ( val > 0 ) 
		{
			Tree[root].Max = Tree[root].Min = val; 
			Tree[root].sum = 1; Tree[root].tag = a[l] < b[l]; 
		}
		else { Tree[root].Max = 0; Tree[root].Min = INF; Tree[root].sum = Tree[root].tag = 0; }
		return ; 
	} 
	int Mid = l + r >> 1;
	if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
	else Modify(rson, Mid + 1, r, pos, val);
	PushUp(root);
}

inline int Query1(int root, int l, int r, int pos)
{
	if ( pos == 0 ) return INF;
	if ( l == r ) { num -= Tree[root].sum; val = max(val, Tree[root].Max); return Tree[root].Min; }
	int Mid = l + r >> 1;
	if ( pos <= Mid ) return Query1(lson, l, Mid, pos);
	num -= Tree[lson].sum; val = max(val, Tree[lson].Max);
	return min(Tree[lson].Min, Query1(rson, Mid + 1, r, pos));
}

inline int Query2(int root, int l, int r, int x)
{
	if ( l == r ) return a[l];
	int Mid = l + r >> 1;
	if ( Tree[rson].tag == 1 || Tree[rson].Min < x || num < Tree[rson].sum )
		return Query2(rson, Mid + 1, r, x);
	num -= Tree[rson].sum;
	return max(Tree[rson].Max, Query2(lson, l, Mid, x));
}

inline void Check(int x, int op, int pos)
{
	num = m - op; val = x;
	if ( Query1(1, 1, n, pos) < x ) return ; 

	if ( num < 0 ) return ;
 	val = max(val, Query2(1, 1, n, x));
	ans = min(ans, val - x);
}

inline void read(int &x)
{
	char c = getchar(); x = 0;
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); } 
}

int main()
{
	scanf("%d%d", &n, &m);
	REP(i, 1, n) read(a[i]); REP(i, 1, n) { read(b[i]); c[i] = pii(b[i], i); }
	sort(c + 1, c + n + 1); int x = 0;
	REP(i, 1, n)
	{
		while ( x < n && a[x + 1] <= c[i].first ) ++ x;	
		p[c[i].second] = x;
	}
	Build(1, 1, n);

	REP(i, 1, n) 
	{
		Modify(1, 1, n, i, -1);
		Check(a[i], 0, i); Check(b[i], 1, p[i]);
		Modify(1, 1, n, i, b[i]);
	}
	printf("%d\n", ans);
	return 0;
}
