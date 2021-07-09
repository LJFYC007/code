#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 20010;
const int INF = 0x3f3f3f3f;

int n, q, C, a[maxn], ans;

struct node { int sum, val; bool vis; } Tree[maxn << 2];

inline int Find(int root, int x, int dep)
{
	if ( dep == 0 ) return Tree[root].val;
	int c = (x >> dep - 1) & 1;
	if ( c == 1 )
	{
		if ( Tree[rson].vis ) return Find(rson, x, dep - 1);
		return Find(lson, x, dep - 1);
	}
	if ( Tree[lson].vis ) return Find(lson, x, dep - 1);
	return Find(rson, x, dep - 1);
}

inline void Build(int root, int l, int r, int dep)
{
	if ( l > r || dep == -1 ) return ;
	int Mid = l - 1;
	while ( Mid < r && !((a[Mid + 1] >> dep - 1) & 1) ) ++ Mid;
	Build(lson, l, Mid, dep - 1);
	Build(rson, Mid + 1, r, dep - 1);
	Tree[root].vis = true; Tree[root].val = a[l];
	if ( Mid == l - 1 || Mid == r ) return ;
	Tree[root].sum = INF;
 	REP(i, Mid + 1, r) Tree[root].sum = min(Tree[root].sum, a[i] ^ Find(lson, a[i], dep - 1));
	ans += Tree[root].sum;
}

int main()
{
	freopen("xor.in", "r", stdin);
	freopen("xor.out", "w", stdout);
	scanf("%d%d", &n, &C);
	REP(i, 1, n) scanf("%d", &a[i]);
	scanf("%d", &q);
	while ( q -- )
	{
		if ( clock() * 1. / CLOCKS_PER_SEC >= 1.9 ) { printf("%d\n", ans); continue ; }
		int x; scanf("%d", &x);
		REP(i, 1, n) a[i] = (a[i] + x) % (1 << C);
		sort(a + 1, a + n + 1); n = unique(a + 1, a + n + 1) - a - 1;
		ans = 0; mem(Tree); Build(1, 1, n, C);
		printf("%d\n", ans);
	}
	return 0;
}
