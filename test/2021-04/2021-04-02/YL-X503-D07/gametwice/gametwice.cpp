/***************************************************************
	File name: gametwice.cpp
	Author: ljfcnyali
	Create time: 2021年04月02日 星期五 08时21分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 310;
const int Delta = maxn * maxn;
const int Mod = 998244353;

int n, m, f[maxn], g[maxn][maxn * maxn * 2];
bool Edge[maxn][maxn];
char s[maxn];

int main()
{
    freopen("gametwice.in", "r", stdin);
    freopen("gametwice.out", "w", stdout);
	scanf("%d%d", &n, &m);
	scanf("%s", s + 1);
	REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); Edge[u][v] = true; } 
	for ( int i = n; i >= 1; -- i ) 
		if ( s[i] == 'W' ) 
		{
			int Max = 0;
			REP(j, i + 1, n) if ( Edge[i][j] ) Max = max(Max, f[j] + 1);
			f[i] = Max;
		}
		else
		{
			int Min = 0;
			REP(j, i + 1, n) if ( Edge[i][j] ) Min = min(Min, f[j] - 1);
			f[i] = Min;
		}
	// REP(i, 1, n) cout << f[i] << " "; cout << endl;
	g[n][Delta] = 1;
	for ( int i = n; i >= 1; -- i ) for ( int j = 0; j < Delta + Delta; ++ j ) if ( g[i][j] ) 
	{
		g[i - 1][j + f[i]] = (g[i - 1][j + f[i]] + g[i][j]) % Mod;
		g[i - 1][j] = (g[i - 1][j] + g[i][j]) % Mod;
	}
	int ans = 0;
	REP(i, Delta + 1, Delta + Delta - 1) ans = (ans + g[0][i]) % Mod;
	printf("%d\n", ans);
    return 0;
}
