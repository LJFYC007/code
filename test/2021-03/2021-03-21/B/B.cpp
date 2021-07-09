/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月21日 星期日 10时30分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3e5 + 10;
const int INF = 1e18;
const int Mod = 1e9 + 7;

int n, m, a[4][maxn], dis[2][4][maxn], Begin[maxn], Next[maxn * 4], To[maxn * 4], e, W[maxn * 4];
int dt[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, ans, c[maxn], d[maxn];
bool vis[maxn * 4];
struct node 
{ 
	int x, y, z, op; 
	bool operator < (const node &a) const { return x < a.x; } 
} A[maxn];
priority_queue<pii> Q;
map<int, int> Map;

inline int lowbit(int x) { return x & -x; } 
inline void add1(int pos, int val) { for ( int i = pos; i <= m; i += lowbit(i) ) c[i] = (c[i] + val) % Mod; } 
inline int query1(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum = (sum + c[i]) % Mod; return sum; } 
inline void add2(int pos, int val) { for ( int i = pos; i <= m; i += lowbit(i) ) ++ d[i]; } 
inline int query2(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += d[i]; return sum; } 

inline int Id(int x, int y) { return (x - 1) * n + y; } 

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

inline void Get(int l, int r, int o, int x)
{
	e = 0; REP(i, 1, 3) REP(j, l, r) Begin[Id(i, j)] = 0;
	REP(i, 1, 3) REP(j, l, r) REP(t, 0, 3)
	{
		int x = i + dt[t][0], y = j + dt[t][1];
		if ( x < 1 || y < l || x > 3 || y > r ) continue ; 
		add(Id(i, j), Id(x, y), a[x][y]);
	}
	if ( o == 0 ) { add(Id(1, l), Id(3, l), x + a[3][l]); add(Id(3, l), Id(1, l), x + a[1][l]); }
	else { add(Id(1, r), Id(3, r), x + a[3][r]); add(Id(3, r), Id(1, r), x + a[1][r]); }

	REP(s, 1, 3) 
	{
		int pos = Id(s, o == 0 ? r : l); 
		REP(i, l, r) REP(j, 1, 3) { dis[o][s][Id(j, i)] = INF; vis[Id(j, i)] = false; } 
		dis[o][s][pos] = o == 0 ? a[s][r] : 0; Q.push(pii(-dis[o][s][pos], pos));
		while ( !Q.empty() )  
		{
			int u = Q.top().second; Q.pop();
			if ( vis[u] ) continue ; vis[u] = true;
			for ( int i = Begin[u]; i; i = Next[i] ) 
			{
				int v = To[i];
				if ( dis[o][s][v] > dis[o][s][u] + W[i] ) 
				{
					dis[o][s][v] = dis[o][s][u] + W[i];
					if ( !vis[v] ) Q.push(pii(-dis[o][s][v], v)); 
				}
			}
		}
	}
}

inline void calc(int l, int Mid, int r, int x, int y, int z)
{
	int n = 0; m = 0; Map.clear();
	REP(i, 1, 3) REP(j, l, Mid) 
		A[++ n] = {dis[0][x][Id(i, j)] - dis[0][y][Id(i, j)], dis[0][x][Id(i, j)] - dis[0][z][Id(i, j)], dis[0][x][Id(i, j)], 0};
	REP(i, 1, 3) REP(j, Mid, r) 
	{
		A[++ n] = {-dis[1][x][Id(i, j)] + dis[1][y][Id(i, j)], -dis[1][x][Id(i, j)] + dis[1][z][Id(i, j)], dis[1][x][Id(i, j)], 1};
		if ( x > y ) -- A[n].x; if ( x > z ) -- A[n].y;
	}
	REP(i, 1, n) Map[A[i].y] = true;		
	for ( auto it : Map ) { Map[it.first] = ++ m; c[m] = d[m] = 0; }
	REP(i, 1, n) A[i].y = Map[A[i].y];
	sort(A + 1, A + n + 1);
	for ( int i = 1, j; i <= n; i = j + 1 ) 
	{
		j = i; while ( j < n && A[j + 1].x == A[i].x ) ++ j;
		REP(k, i, j) if ( A[k].op == 0 ) { add1(A[k].y, A[k].z); add2(A[k].y, 1); }
		REP(k, i, j) if ( A[k].op == 1 ) ans = (ans + query1(A[k].y) + query2(A[k].y) * A[k].z) % Mod;
	}
}

inline void Solve(int l, int r, int x, int y)
{
	if ( l > r ) return ; 
	int Mid = l + r >> 1;
	Get(l, Mid, 0, x); Get(Mid, r, 1, y);
	calc(l, Mid, r, 1, 2, 3);
	calc(l, Mid, r, 2, 1, 3);
	calc(l, Mid, r, 3, 1, 2);
	int sum = 0;
	REP(i, 1, 3) REP(j, 1, i) 
	{
		ans = (ans - min(dis[0][i][Id(j, Mid)], dis[1][i][Id(j, Mid)] + a[i][Mid])) % Mod;
		sum = (sum - min(dis[0][i][Id(j, Mid)], dis[1][i][Id(j, Mid)] + a[i][Mid])) % Mod;
	}
	int val = dis[0][1][Id(3, Mid)];
	Solve(l, Mid - 1, x, dis[1][1][Id(3, Mid)] + a[1][Mid]);
	Solve(Mid + 1, r, val, y);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); REP(i, 1, 3) REP(j, 1, n) scanf("%lld", &a[i][j]);
	Solve(1, n, INF, INF);
	ans = ans * 2 % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
