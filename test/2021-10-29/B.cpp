/***************************************************************
	File name: MCMF.cpp
	Author: ljfcnyali
	Create time: 2021年02月04日 星期四 16时24分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 2147483647;

int n, m, Begin[maxn], Next[maxn], To[maxn], e = 1, s, t, W[maxn], F[maxn];
int dis[maxn], pre[maxn], a[maxn], flow, cost, pos[maxn], num;
bool vis[maxn];
queue<int> Q;

inline void add(int u, int v, int w, int f)
{
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f;
	swap(u, v); w = 0; f = -f;
	To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; F[e] = f;
}

inline bool BFS()
{
	REP(i, 1, num) dis[i] = INF; dis[s] = 0; a[s] = INF; Q.push(s);
	while ( !Q.empty() ) 
	{
		int u = Q.front(); Q.pop();
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{
			int v = To[i]; if ( !W[i] ) continue ; 
			if ( dis[v] > dis[u] + F[i] ) 
			{
				dis[v] = dis[u] + F[i]; pre[v] = i; pos[v] = u;
				a[v] = min(a[u], W[i]);
				if ( !vis[v] ) { vis[v] = true; Q.push(v); }
			}
		}
		vis[u] = false;
	}
	return dis[t] != INF;
}

inline void Solve()
{
	if ( dis[t] > 0 ) 
	{
		cout << -cost;
		exit(0);
	}
	int x = t; flow += a[t]; cost += dis[t] * a[t];
	while ( x != s ) 
	{
		W[pre[x]] -= a[t]; W[pre[x] ^ 1] += a[t];
		x = pos[x];
	}
}

int h[maxn]; vector<int> A[510], B[510];
bool f[510][510];

int main()
{
    scanf("%d%d", &n, &m);
    if ( n > 100 ) return 0;
	REP(i, 1, n) scanf("%d", &h[i]);
	//REP(i, 1, n) f[i][i] = true;
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); f[u][v] = true; } 
    REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) f[i][j] |= f[i][k] & f[k][j];

    s = n + n + 1; t = n + n + 2;
    num = t;
    REP(i, 1, n)
    {
        int k; scanf("%d", &k); 
        REP(j, 1, k) { int x; scanf("%d", &x); ++ num; add(s, num, 1, x - h[i]); add(num, i, INF, 0); }
    }
    REP(i, 1, n)
    {
        int k; scanf("%d", &k); 
        REP(j, 1, k) { int x; scanf("%d", &x); ++ num; add(num, t, 1, x + h[i]); add(n + i, num, INF, 0); }
    }
    REP(i, 1, n) REP(j, 1, n) if ( f[i][j] && h[i] > h[j] ) 
        add(i, n + j, INF, 0);

	while ( BFS() ) Solve();
    cout << -cost;
    return 0;
}