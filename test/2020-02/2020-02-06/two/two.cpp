#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 1e6 + 10;

int n, a[2][maxn], sum;
vector<int> last, ret;
vector<pii> Edge[2][maxn];

struct node
{
	int Begin[maxn], Next[maxn], To[maxn], e, dis[maxn], p[maxn], id[maxn], tot, size[maxn];
	vector<int> ans;
	vector<pii> W[maxn];
	struct node1 { set<pii> Set; } Tree[maxn << 2];

	inline void PushUp(int root)
	{
		for ( auto i : Tree[lson].Set ) Tree[root].Set.insert(i);
		for ( auto i : Tree[rson].Set ) Tree[root].Set.insert(i);
	}

	inline void build(int root, int l, int r)
	{
		if ( l == r ) { for ( auto it : W[l] ) Tree[root].Set.insert(it); return ; }
		int Mid = l + r >> 1;
		build(lson, l, Mid); build(rson, Mid + 1, r);
		PushUp(root);
	}

	inline void Query(int root, int l, int r, int L, int R)
	{
		if ( L <= l && r <= R )
		{
			auto itl = Tree[root].Set.lower_bound(pii(L, 0));
			auto itr = Tree[root].Set.lower_bound(pii(R + 1, 0));
			for ( auto it = Tree[root].Set.begin(); it != itl; ++ it ) ans.push_back(it -> second);
			for ( auto it = itr; it != Tree[root].Set.end(); ++ it ) ans.push_back(it -> second);
			return ;
		}
		int Mid = l + r >> 1;
		if ( L <= Mid ) Query(lson, l, Mid, L, R);
		if ( Mid < R ) Query(rson, Mid + 1, r, L, R);
	}

	inline void Modify(int root, int l, int r, int pos, pii x)
	{
		Tree[root].Set.erase(x);
		if ( l == r ) return ;
		int Mid = l + r >> 1;
		if ( pos <= Mid ) Modify(lson, l, Mid, pos, x);
		else Modify(rson, Mid + 1, r, pos, x);
	}

	inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

	inline void DFS(int u, int fa)
	{
		size[u] = 1; p[u] = ++ tot; id[tot] = u;
		for ( int i = Begin[u]; i; i = Next[i] )
		{
			int v = To[i]; if ( v == fa ) continue ;
			dis[v] = dis[u] + 1; DFS(v, u);
			size[u] += size[v];
		}
	}

	inline void Init(int op)
	{
		REP(i, 2, n)
		{
			int u, v = i; scanf("%d", &u);
			add(u, v); add(v, u); a[op][v] = u;
			Edge[op][u].push_back(pii(v, i - 1)); Edge[op][v].push_back(pii(u, i - 1));
		}
		dis[1] = 1; DFS(1, 0);
	}

	inline void Build(int op)
	{
		REP(i, 1, n) for ( auto it : Edge[op ^ 1][id[i]] ) W[i].push_back(pii(p[it.first], it.second));
		build(1, 1, n);
	}

	inline void Solve(int x, int op)
	{
		int v = x + 1, u = a[op][v]; if ( dis[u] > dis[v] ) swap(u, v);
		int L = p[v], R = p[v] + size[v] - 1;
		ans.clear();
		Query(1, 1, n, L, R);
		for ( auto i : ans )
		{
			ret.push_back(i);
			int u = i + 1, v = a[op ^ 1][u];
			Modify(1, 1, n, p[u], pii(p[v], i));
			Modify(1, 1, n, p[v], pii(p[u], i));
		}
	}

	inline void Delete(int op, int i)
	{
		int u = i + 1, v = a[op ^ 1][u];
		Modify(1, 1, n, p[u], pii(p[v], i));
		Modify(1, 1, n, p[v], pii(p[u], i));
	}
} A, B;

int main()
{
	freopen("two.in", "r", stdin);
	freopen("two.out", "w", stdout);
	scanf("%d", &n);
	A.Init(0); B.Init(1);
	A.Build(0); B.Build(1);
	int x, op = 0; scanf("%d", &x); last.push_back(x);
	B.Delete(1, x);
	while ( !last.empty() )
	{
		if ( op == 0 ) puts("Blue"); else puts("Red");
		sort(last.begin(), last.end());
		for ( auto i : last ) printf("%d ", i); puts("");
		ret.clear();
		for ( auto x : last )
		{
			if ( op == 0 ) A.Solve(x, op);
			else B.Solve(x, op);
		}
		swap(last, ret); op ^= 1;
	}
	return 0;
}
