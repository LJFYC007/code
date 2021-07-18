/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年07月18日 星期日 09时03分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2510;
const int Mod = 998244353;

int k, limit1, limit2, Begin[maxn], Next[maxn], To[maxn], e, Stack[maxn], tot, n;
char s[10]; int f[maxn][maxn][2][2][2], g[maxn][2][2][2], h[maxn][2][2][2];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, int dep)
{
	for ( int i = Begin[u]; i; i = Next[i] ) DFS(To[i], dep + 1);
	REP(x, 0, 1) 
	{
		if ( u == 1 && x == 1 ) continue ; 
		REP(i, 0, dep - 1) if ( i + x <= limit1 && dep - i - 1 - x <= limit2 ) 
		{
			if ( x == 1 ) g[i][0][0][0] = g[i][1][0][0] = 1;
			else g[i][0][0][0] = g[i][0][1][0] = g[i][0][0][1] = g[i][0][1][1] = 1;
			if ( u == 1 ) g[i][0][1][0] = g[i][0][0][1] = g[i][0][1][1] = 0;
		}
		for ( int i = Begin[u]; i; i = Next[i] ) 
		{	
			int v = To[i];
			REP(j, 0, dep)	REP(a, 0, 1) REP(b, 0, 1) REP(c, 0, 1) REP(A, 0, 1 - a) REP(B, 0, 1 - b) REP(C, 0, 1 - c)
				h[j][a + A][b + B][c + C] = (h[j][a + A][b + B][c + C] + 1ll * g[j][a][b][c] * f[v][j + x][A][B][C]) % Mod;
			REP(j, 0, dep)	REP(a, 0, 1) REP(b, 0, 1) REP(c, 0, 1)
			{
				g[j][a][b][c] = h[j][a][b][c];
				h[j][a][b][c] = 0;
			}
		}
		REP(i, 0, dep) REP(a, 0, 1) REP(b, 0, 1) REP(c, 0, 1)
		{
			f[u][i][a][b][c] = (f[u][i][a][b][c] + g[i][a][b][c]) % Mod;
			g[i][a][b][c] = 0;
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &k, &limit1, &limit2);
	n = tot = Stack[1] = 1;		
	REP(i, 1, k + k)
	{
		scanf("%s", s + 1);
		if ( s[2] == 'u' ) { Stack[++ tot] = ++ n; add(Stack[tot - 1], Stack[tot]); }
		else -- tot;
	}
	DFS(1, 1);
	printf("%d\n", f[1][0][1][1][1]);
    return 0;
}
