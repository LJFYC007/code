#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
 
const int maxn = 6e5 + 10;
 
int n, m, Begin[maxn], Next[maxn], To[maxn], e = 1, dis[maxn], tot, Root[maxn];
int dfn[maxn], low[maxn], cnt, size[maxn], anc[maxn][20], h[maxn][20], gggg[maxn];
bool cut[maxn];
vector<int> son[maxn], pa[maxn];
map<int, int> Map[maxn];
struct node { int lson, rson; } Tree[maxn << 5];

inline void Modify(int &root, int l, int r, int pos)
{
	if ( !root ) root = ++ tot;
	if ( l == r ) return ;
	int Mid = l + r >> 1;
	if ( pos <= Mid ) Modify(ls(root), l, Mid, pos);
	else Modify(rs(root), Mid + 1, r, pos);
}

inline void Merge(int &p, int q, int l, int r)
{
	if ( !p || !q ) { p += q; return ; } 
	if ( l == r ) return ; 
	int Mid = l + r >> 1;
	Merge(ls(p), ls(q), l, Mid); Merge(rs(p), rs(q), Mid + 1, r);
}

inline bool Query(int root, int l, int r, int L, int R)
{
	if ( !root ) return false;
	if ( L <= l && r <= R ) return true;
	int Mid = l + r >> 1; bool ret = false;
	if ( L <= Mid ) ret |= Query(ls(root), l, Mid, L, R);
	if ( Mid < R ) ret |= Query(rs(root), Mid + 1, r, L, R);
	return ret;
}
 
inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline int Get(int u, int v)
{
	if ( anc[u][0] == v ) return 0; 
	int Min = n;
	for ( int i = 18; i >= 0; -- i ) if ( dis[anc[u][i]] > dis[v] ) { Min = min(Min, h[u][i]); u = anc[u][i]; }
	return Min;
}

inline void DFS1(int u)
{
	low[u] = dfn[u] = ++ cnt; size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
		if ( !dfn[v] ) 
		{ 
			dis[v] = dis[u] + 1; anc[v][0] = u; son[u].push_back(v); 
			DFS1(v); low[u] = min(low[u], low[v]); size[u] += size[v];
		}
		else if ( dfn[v] < dfn[u] ) { pa[u].push_back(v); low[u] = min(low[u], dfn[v]); } 
	}
	set<int> Set; for ( auto v : son[u] ) if ( low[v] >= dfn[u] ) Set.insert(v);
	if ( Set.size() >= 2 ) gggg[u] = -1;
	else if ( Set.size() == 1 ) gggg[u] = *Set.begin();
}

#define GG return cut[Map[u][v]] = true

inline bool Check(int u, int v)
{
	int t = u; for ( int i = 18; i >= 0; -- i ) if ( dis[anc[t][i]] > dis[v] ) t = anc[t][i];
	if ( v != 1 ) { if ( gggg[v] == -1 || (gggg[v] > 0 && gggg[v] != t) ) GG; } 
	else 
	{
		if ( son[v].size() > 2 ) GG; 
		if ( son[v].size() > 1 && (size[u] != 1 || anc[u][0] != v)) GG; 
	} 

	if ( v == 1 && anc[u][0] == v ) 
	{
		if ( son[u].size() > 1 ) GG;
		return true;
	}

	bool flag = v == 1 ? true : Get(u, v) < dfn[v];
	for ( auto w : son[u] ) 
	{
		bool num1 = Query(Root[w], 1, n, 1, dfn[v] - 1);
		bool num2 = Query(Root[w], 1, n, dfn[v] + 1, dfn[u] - 1);
		if ( !num1 && !num2 ) GG;
		if ( num1 && num2 ) flag = true;
	}
	if ( !flag ) GG ; 
	return true;
}
 
inline void DFS2(int u)
{
	REP(j, 1, 18) h[u][j] = min(h[u][j - 1], h[anc[u][j - 1]][j - 1]);
	int Min = n; for ( auto w : pa[u] ) Min = min(Min, dfn[w]);
	multiset<int> Set; Set.insert(Min); for ( auto w : son[u] ) Set.insert(low[w]);

	for ( auto v : son[u] ) 
	{
		Set.erase(Set.find(low[v]));
		h[v][0] = *Set.begin(); DFS2(v); 
		Set.insert(low[v]);
	}
	for ( auto v : pa[u] ) Check(u, v); 
	for ( auto v : son[u] ) Merge(Root[u], Root[v], 1, n);
	for ( auto v : pa[u] ) Modify(Root[u], 1, n, dfn[v]);
}
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m); 
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); Map[u][v] = Map[v][u] = i; }
	dis[1] = 1; DFS1(1); 
	REP(j, 1, 18) REP(i, 1, n) anc[i][j] = anc[anc[i][j - 1]][j - 1];
	DFS2(1);
    REP(i, 1, m) printf("%d", cut[i]); puts("");
    return 0;
}
