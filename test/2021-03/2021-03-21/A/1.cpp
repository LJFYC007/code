/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年03月21日 星期日 09时01分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

int n, m, k, a[maxn], ans, lg[maxn], p[maxn], f[41][41][2];
char s[maxn];
bool vis[maxn];

inline int Solve(int m)
{
	REP(i, 1, m) printf("%d ", p[i]); puts("");
	int n = 0; REP(i, 1, m) n += p[i];
	mem(f); f[1][0][0] = 1; int now = 1, pos = 1;
	REP(i, 2, n)
	{
		++ now; if ( now > p[pos] ) { now = 1; ++ pos; } 
		if ( now == 1 ) 
		{
			REP(j, 0, i) REP(o, 0, 1)
			{
				f[i][j][0] = (f[i][j][0] + f[i - 1][j][o] * (i - j)) % Mod;
				if ( j >= 1 ) f[i][j - 1][0] = (f[i][j - 1][0] + f[i - 1][j][o] * j) % Mod;
			}
		}
		else
		{
			REP(j, 0, i)
			{
				REP(o, 0, 1)
				{
					if ( i - j - 2 + o >= 1 ) f[i][j][0] = (f[i][j][0] + f[i - 1][j][o] * (i - j - 2 + o)) % Mod;
					if ( j >= 1 ) f[i][j - 1][0] = (f[i][j - 1][0] + f[i - 1][j][o] * (j - o)) % Mod;
				}
				if ( j >= 1 ) f[i][j][1] = (f[i][j][1] + f[i - 1][j - 1][0] * 2 + f[i - 1][j - 1][1]) % Mod;
				f[i][j][1] = (f[i][j][1] + f[i - 1][j][1]) % Mod;
			}
		}
	}
	return (f[n][0][0] + f[n][0][1]) % Mod;
}

inline int DFS(int x, int s)
{
	if ( x > n ) 
	{ 
		int ret = 0; bool flag = false;
		REP(j, 1, n) if ( !vis[j] ) { ++ k; vis[j] = true; ret += DFS(j, s); vis[j] = false; flag = true; -- k; break ; } 
		if ( !flag && !s ) return Solve(k);
		return ret;
	}
	vis[x * 2] = true; ++ p[k];
	int ret = DFS(x * 2, s), y = lg[n / x] + 1;
	vis[x * 2] = false; -- p[k];
	REP(i, 1, m) if ( ((s >> i - 1) & 1) && a[i] <= y ) 
	{
		int val = x; REP(j, 1, a[i]) { val *= 2; vis[val] = true; }
		++ p[k]; ret = (ret + DFS(val, s ^ (1 << i - 1))) % Mod; -- p[k];
		val = x; REP(j, 1, a[i]) { val *= 2; vis[val] = false; } 
	}
	return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); scanf("%s", s + 1);
	for ( int i = 1, j; i < n; i = j + 1 ) 
	{
		j = i; if ( s[i] == '0' ) continue ; 
		while ( s[j + 1] == '1' ) ++ j;
		a[++ m] = j - i + 2;
		if ( a[m] > 6 ) { puts("0"); return 0; } 
	}
	REP(i, 2, n) lg[i] = lg[i >> 1] + 1;
	k = 1; vis[1] = true; printf("%d\n", (DFS(1, (1 << m) - 1) + Mod) % Mod);
    return 0;
}
