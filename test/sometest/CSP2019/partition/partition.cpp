#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define int long long
#define lson root << 1
#define rson root << 1 | 1

const int maxn = 5e5 + 10;
const int INF = 5e18;

int n, type, a[maxn], sum[maxn], ans;
struct node { int lazy, val; } Tree[maxn << 2];

inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	Tree[lson].val = Tree[lson].lazy = Tree[rson].val = Tree[rson].lazy = Tree[root].lazy;
	Tree[root].lazy = 0;
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) { Tree[root].lazy = Tree[root].val = val; return ; }
	PushDown(root);
	int Mid = (l + r) >> 1;
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
}

inline int Query(int root, int l, int r, int pos)
{
	if ( l == r ) return Tree[root].val;
	PushDown(root);
	int Mid = (l + r) >> 1;
	if ( pos <= Mid ) return Query(lson, l, Mid, pos);
	return Query(rson, Mid + 1, r, pos);
}

inline void read(int &x)
{
	char c = getchar(); x = 0;
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
	freopen("partition.in", "r", stdin);
	freopen("partition.out", "w", stdout);
	scanf("%lld%lld", &n, &type);
	REP(i, 1, n) { read(a[i]); sum[i] = sum[i - 1] + a[i]; }
	Modify(1, 1, n, 1, n, 1);
	REP(i, 1, n)
	{
		int x = sum[i] - sum[Query(1, 1, n, i) - 1], L = i, R = n, pos = n + 1;
		while ( L <= R ) 
		{
			int Mid = (L + R) >> 1;
			if ( sum[Mid] - sum[i] >= x ) { pos = Mid; R = Mid - 1; }
			else L = Mid + 1;
		}
		Modify(1, 1, n, pos, n, i + 1);
	}	
	int i = n;
	while ( i ) 
	{
		int x = Query(1, 1, n, i) - 1;
		ans += (sum[i] - sum[x]) * (sum[i] - sum[x]);
		i = x;
	}
	printf("%lld\n", ans);
	return 0;
}
