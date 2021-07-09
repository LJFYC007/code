#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 1e9 + 7;

int n, tot, b[maxn], f[maxn], ans, sum;
vector<int> Q[maxn];
struct node { int sum, lazy, len; } Tree[maxn << 2];
pii a[maxn];
bool vis[maxn];

inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

inline void PushTag(int root, int val) { Tree[root].sum += Tree[root].len * val; Tree[root].lazy += val; }

inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
	Tree[root].lazy = 0;
}

inline void Build(int root, int l, int r)
{
	Tree[root].len = r - l + 1;
	if ( l == r ) { Tree[root].sum = f[l]; return ; }
	int Mid = l + r >> 1;
	Build(lson, l, Mid); Build(rson, Mid + 1, r);
	PushUp(root);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) { PushTag(root, val); return ; }
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

inline void read(int &x)
{
	char c = getchar(); x = 0;
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 1, n) { read(a[i].first); a[i].second = i; }
	sort(a + 1, a + n + 1);
	REP(i, 1, n)
	{
		if ( i == 1 || a[i].first != a[i - 1].first ) ++ tot;
		b[a[i].second] = tot;
	}
	REP(i, 1, n)
	{
		f[i] = f[i - 1];
		if ( !vis[b[i]] ) { vis[b[i]] = true; ++ f[i]; }
		sum = (sum + f[i] * f[i]) % Mod;
	}
	ans = sum;
	REP(i, 1, tot) Q[i].push_back(n + 1);
	for ( int i = n; i >= 1; -- i ) Q[b[i]].push_back(i);
	Build(1, 1, n);
	REP(i, 1, n)
	{
		Q[b[i]].pop_back();
		int pos = Q[b[i]].back();
		sum = sum + pos - i - 2 * Query(1, 1, n, i, pos - 1);
		Modify(1, 1, n, i, pos - 1, -1);
		sum %= Mod; ans = (ans + sum) % Mod;
	}
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
