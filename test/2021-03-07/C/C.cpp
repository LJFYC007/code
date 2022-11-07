/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年03月07日 星期日 10时44分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int Mod = 998244353;

int n, m, k, q, Begin[maxn], Next[maxn], To[maxn], e = 1, id[41][41];
int dis[maxn], anc[maxn][11];
char s[41][41], t[maxn][27];
map<string, int> Map;
struct Matrix { int n, m, a[40][40]; } pre[maxn][11], suf[maxn][11], now;

Matrix operator *(Matrix a, Matrix b)
{
	Matrix c; c.n = a.n; c.m = b.m;	REP(i, 0, c.n) REP(j, 0, c.m) c.a[i][j] = 0;
	REP(i, 0, c.n) REP(k, 0, a.m) if ( a.a[i][k] ) REP(j, 0, c.m) if ( b.a[k][j] ) c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % Mod;
	return c;
}

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline int LCA(int x, int y)
{
	if ( dis[x] < dis[y] ) swap(x, y);
	for ( int i = 10; i >= 0; -- i ) if ( dis[anc[x][i]] >= dis[y] ) x = anc[x][i];
	if ( x == y ) return x;
	for ( int i = 10; i >= 0; -- i ) if ( anc[x][i] != anc[y][i] ) { x = anc[x][i]; y = anc[y][i]; } 
	return anc[x][0];
}

inline void DFS(int u, int fa)
{
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dis[v] = dis[u] + 1; anc[v][0] = u; DFS(v, u);
		
		pre[v][0].n = pre[v][0].m = k;
		REP(j, 1, str(t[i >> 1] + 1)) REP(o, 0, k) 
		{
			int x = id[o][t[i >> 1][j] - 'a'];
			if ( x != -1 ) ++ pre[v][0].a[o][x];
		}
		suf[v][0] = pre[v][0];
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &q);
	REP(i, 1, n - 1) { int u, v; scanf("%lld%lld%s", &u, &v, t[i] + 1); add(u, v); add(v, u); }
	REP(i, 1, m) scanf("%s", s[i] + 1); 
	string T; Map[T] = 1;
	REP(i, 1, m) REP(j, 1, str(s[i] + 1)) { string S; REP(o, 1, j) S += s[i][o]; Map[S] = (j == str(s[i] + 1) ? 2 : 1); }
	for ( auto it : Map ) Map[it.first] = it.second == 1 ? ++ k : 0;
	int pos = Map[T];
	for ( auto it : Map ) 
	{
		string S = it.first; if ( it.second == 0 ) continue ; 
		REP(j, 0, 25) 
		{
			id[it.second][j] = pos;
			bool flag = false;
			for ( int i = 0; i <= S.size(); ++ i ) 
			{
				string T; for ( int o = i; o < S.size(); ++ o ) T += S[o]; T += char('a' + j);
				if ( Map.count(T) && Map[T] == 0 ) { flag = true; break ; } 
			}
			if ( flag ) { id[it.second][j] = 0; continue ; } 
			for ( int i = 0; i <= S.size(); ++ i ) 
			{
				string T; for ( int o = i; o < S.size(); ++ o ) T += S[o]; T += char('a' + j);
				if ( Map.count(T) ) { id[it.second][j] = Map[T]; break ; } 
			}
		}
	} 

	dis[1] = 1; DFS(1, 0); 
	REP(j, 1, 10) REP(i, 1, n) 
	{ 
		anc[i][j] = anc[anc[i][j - 1]][j - 1];
		if ( !anc[i][j] ) continue ; 
		pre[i][j] = pre[i][j - 1] * pre[anc[i][j - 1]][j - 1];
		suf[i][j] = suf[anc[i][j - 1]][j - 1] * suf[i][j - 1];
	}

	while ( q -- ) 
	{
		int u, v; scanf("%lld%lld", &u, &v); int t = LCA(u, v);
		now.n = 0; now.m = k; REP(i, 0, k) now.a[0][i] = 0; now.a[0][pos] = 1;
		for ( int i = 10; i >= 0; -- i ) if ( dis[anc[u][i]] >= dis[t] ) { now = now * pre[u][i]; u = anc[u][i]; } 
		vector<pii> p;
		for ( int i = 10; i >= 0; -- i ) if ( dis[anc[v][i]] >= dis[t] ) { p.push_back(pii(v, i)); v = anc[v][i]; } 
		reverse(p.begin(), p.end());
		for ( auto it : p ) now = now * suf[it.first][it.second];
		printf("%lld\n", (now.a[0][0] + Mod) % Mod);
	}
    return 0;
}
