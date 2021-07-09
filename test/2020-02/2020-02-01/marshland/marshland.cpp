#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, k, Begin[maxn], From[maxn], Next[maxn], To[maxn], e = 1, W[maxn], F[maxn];
int dis[maxn], a[maxn], s, t, pre[maxn], v[60][60], id[60][60];
bool vis[maxn], use[60][60];
int dt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}, sum, ans;

inline void add(int u, int v, int f, int w)
{
	To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; F[e] = f; W[e] = w;
	swap(u, v); f = 0; w = -w;
	To[++ e] = v; From[e] = u; Next[e] = Begin[u]; Begin[u] = e; F[e] = f; W[e] = w;
}

inline bool BFS(int s, int t)
{
    memset(dis, 0x3f, sizeof(dis)); mem(vis);
    dis[s] = 0; vis[s] = true; a[s] = INF; queue<int> Q; Q.push(s);
    while ( !Q.empty() )
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] )
        {
            int v = To[i];
            if ( dis[v] > dis[u] + W[i] && F[i] > 0 )
            {
                dis[v] = dis[u] + W[i];
                a[v] = min(a[u], F[i]);
                pre[v] = i;
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
    return dis[t] != INF;
}

inline void SPFA(int s, int t)
{
    sum += a[t] * dis[t]; int u = t;
    while ( u != s ) { F[pre[u]] -= a[t]; F[pre[u] ^ 1] += a[t]; u = From[pre[u]]; }
}

int main()
{
	freopen("marshland.in", "r", stdin);
	freopen("marshland.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	int tot = 0;
	REP(i, 1, n) REP(j, 1, n)
	{
		scanf("%d", &v[i][j]); ans += v[i][j];
		id[i][j] = ++ tot; if ( i + j & 1 ) ++ tot;
	}
	int s = ++ tot, t = ++ tot;
	REP(i, 1, k) { int x, y; scanf("%d%d", &x, &y); use[x][y] = true; }
	REP(i, 1, n) REP(j, 1, n)
	{
		if ( use[i][j] ) continue ;
		if ( i & 1 && j & 1 )
		{
			add(s, id[i][j], 1, 0);
			REP(o, 0, 3)
			{
				int x = i + dt[o][0], y = j + dt[o][1];
				if ( use[x][y] || !id[x][y] ) continue ;
				add(id[i][j], id[x][y], 1, 0);
			}
		}
		else if ( i + j & 1 ) add(id[i][j], id[i][j] + 1, 1, 0);
		else
		{
			add(id[i][j], t, 1, 0);
			REP(o, 0, 3)
			{
				int x = i + dt[o][0], y = j + dt[o][1];
				if ( use[x][y] || !id[x][y] ) continue ;
				add(id[x][y] + 1, id[i][j], 1, -v[x][y]);
			}
		}
	}
	REP(i, 1, m)
	{
		if ( !BFS(s, t) ) break ;
		sum = 0; SPFA(s, t);
		if ( sum > 0 ) break ; ans += sum;
	}
	printf("%d\n", ans);
	return 0;
}
