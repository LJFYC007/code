#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>

const int maxn = 110;

int n, m, a[maxn][maxn], b[maxn][maxn], c[maxn][maxn], num, f[maxn], deg[maxn];
int dfn[maxn], f1[maxn], f2[maxn], tot;
struct node { int x, y, z; } ; bool vis[maxn];
vector<node> ans, now; vector<int> leaf;

inline void DFS(int u, int fa)
{
    deg[u] = 1; f[u] = fa; vis[u] = true;
    REP(v, 1, n) if ( b[u][v] && v != fa ) { DFS(v, u); ++ deg[u]; }
    if ( deg[u] == 1 ) leaf.push_back(u);
}

inline bool Check(int u, int v)
{
    memset(vis, 0, sizeof(vis)); memset(deg, 0, sizeof(deg));
    now.clear(); leaf.clear(); DFS(u, v); int cnt = 100;
    while ( leaf[0] != u )
    {
        -- cnt; if ( !cnt ) return false;
        for ( auto it : leaf ) if ( deg[it] == 1 ) 
        {
            int pos = 0, val = 0;
            REP(i, 1, n) if ( a[it][i] )
            {
                int w = (!vis[i]) + 1;
                if ( w > val ) { val = w; pos = i; }
				else if ( val == 1 && w == 1 && rand() % 2 == 1 ) pos = i;
            }
            if ( val == 2 ) { vis[it] = false; now.push_back({it, f[it], pos}); -- deg[f[it]]; -- deg[it]; }
            if ( val == 1 ) { now.push_back({it, f[it], pos}); -- deg[f[it]]; ++ deg[pos]; f[it] = pos; }
        }
        leaf.clear();
        REP(i, 1, n) if ( deg[i] == 1 ) leaf.push_back(i);
    }
    if ( leaf[0] == u ) return true;
    return false;
}

inline void DFS1(int u, int fa)
{
	f1[u] = fa; dfn[++ tot] = u;
    REP(v, 1, n) if ( b[u][v] && v != fa ) DFS1(v, u);
}

inline void DFS2(int u, int fa)
{
	f2[u] = fa; 
    REP(v, 1, n) if ( c[u][v] && v != fa ) DFS2(v, u);
}

inline void Insert(int x, int y, int z)
{
	assert(Check(x, y) == true);
	for ( auto it : now ) ans.push_back(it);
	ans.push_back({x, y, z});
	while ( !now.empty() ) 
	{
		ans.push_back({now.back().x, now.back().z, now.back().y});
		now.pop_back();
	}
	b[x][y] = b[y][x] = 0;
	b[z][x] = b[x][z] = 1;

}

int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, m)
    {
        int u, v, x, y; scanf("%d%d%d%d", &u, &v, &x, &y);
        a[u][v] = a[v][u] = 1;
        b[u][v] = b[v][u] = x;
        c[u][v] = c[v][u] = y;
        if ( x == 1 && y == 1 ) ++ num;
    }

    srand(1233);

	while ( 1 ) 
	{
		tot = 0; DFS1(1, 0); DFS2(1, 0);
		bool flag = false;
		for ( int i = n; i >= 1; -- i ) 
		{
			int x = dfn[i];
			if ( f1[x] != f2[x] ) 
			{
				Insert(x, f1[x], f2[x]);
				flag = true; break ; 
			}
		}
		if ( !flag ) break ; 
	}

    puts("Yes"); printf("%d\n", ans.size());
    for ( auto it : ans ) printf("%d %d\n", it.x, it.z);
    return 0;
}
