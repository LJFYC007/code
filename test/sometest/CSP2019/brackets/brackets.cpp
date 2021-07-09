#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 5e5 + 10;
const int INF = 0x3f3f3f3f;

int n, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], N, sum;
bool flag;
LL ans;
char s[maxn];
struct node { int Min, sum, lazy; } Tree[maxn << 2];

inline void PushUp(int root)
{
	Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
	Tree[root].sum = 0;
	if ( Tree[lson].Min == Tree[root].Min ) Tree[root].sum += Tree[lson].sum;
	if ( Tree[rson].Min == Tree[root].Min ) Tree[root].sum += Tree[rson].sum;
}

inline void PushTag(int root, int val) { Tree[root].lazy += val; Tree[root].Min += val; }

inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	PushTag(lson, Tree[root].lazy);
	PushTag(rson, Tree[root].lazy);
	Tree[root].lazy = 0;
}

inline void Build(int root, int l, int r)
{
	if ( l == r ) { Tree[root].sum = 1; return ; }
	int Mid = (l + r) >> 1;
	Build(lson, l, Mid); Build(rson, Mid + 1, r);
	PushUp(root);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
	if ( L <= l && r <= R ) { PushTag(root, val); return ; }
	PushDown(root);
	int Mid = (l + r) >> 1;
	if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
	if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
	PushUp(root);
}

inline void Query(int root, int l, int r, int L, int R)
{
    // printf("%d %d %d %d %d %d %d\n", root, l, r, L, R, Tree[root].Min, Tree[root].sum);
    if ( !flag ) return ;
    if ( l == r && Tree[root].Min < 0 ) { flag = false; return ; }
	if ( L <= l && r <= R && Tree[root].Min >= 0 ) 
    { 
        if ( Tree[root].Min == 0 ) sum += Tree[root].sum; 
        return ; 
    }
    PushDown(root);
    int Mid = l + r >> 1;
    if ( Mid < R ) Query(rson, Mid + 1, r, L, R); 
    if ( L <= Mid ) Query(lson, l, Mid, L, R);
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, LL ret, int dep)
{
	Modify(1, 1, N, 1, dep, a[u]);
    flag = true; sum = 0; Query(1, 1, N, 1, dep);
    // printf("%d %d\n", u, sum);
	ret += sum; ans ^= ret * u;
	for ( int i = Begin[u]; i; i = Next[i] ) DFS(To[i], ret, dep + 1);
	Modify(1, 1, N, 1, dep, -a[u]);
}

inline void DFS1(int u, int dep)
{
	N = max(N, dep);
	for ( int i = Begin[u]; i; i = Next[i] ) DFS1(To[i], dep + 1);
}

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
	freopen("brackets.in", "r", stdin);
	freopen("brackets.out", "w", stdout);
	scanf("%d", &n); 
	scanf("%s", s + 1);
	REP(i, 1, n) if ( s[i] == ')' ) a[i] = 1; else a[i] = -1;
	REP(i, 2, n) { int x; read(x); add(x, i); }
	DFS1(1, 1); Build(1, 1, N); DFS(1, 0, 1);
	printf("%lld\n", ans);
	return 0;
}
