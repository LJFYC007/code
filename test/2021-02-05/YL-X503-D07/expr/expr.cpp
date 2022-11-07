/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

int n, m, len, a[10][maxn], Begin[maxn], Next[maxn], To[maxn], e;
int tot, belong[maxn], Stack[maxn], sum, pos, ans, f[maxn][10], h[10];
char s[maxn];
vector<pii> son[maxn];

inline void Add(int &x, int y) { x = (x + y) % Mod; }

inline void Solve(int u)
{
	REP(i, 0, m - 1) f[u][i] = 0;
	if ( belong[u] != -1 ) { f[u][belong[u]] = 1; return ; }
	for ( int i = 0; i < son[u].size(); ++ i )
	{
		int v = son[u][i].first; Solve(v);
		if ( i == 0 ) { REP(j, 0, m - 1) f[u][j] = f[v][j]; continue ; }
		REP(j, 0, m - 1) h[j] = 0;
		int op = son[u][i].second;
		REP(j, 0, m - 1) if ( f[v][j] )
			REP(k, 0, m - 1) if ( f[u][k] )
			{
				if ( op == 1 ) Add(h[a[j][pos] < a[k][pos] ? j : k], f[u][k] * f[v][j]);
				if ( op == 2 ) Add(h[a[j][pos] > a[k][pos] ? j : k], f[u][k] * f[v][j]);
				if ( op == 3 ) { Add(h[j], f[u][k] * f[v][j]); Add(h[k], f[u][k] * f[v][j]); }
			}
		REP(j, 0, m - 1) f[u][j] = h[j];
	}
}

signed main()
{
	freopen("expr.in", "r", stdin);
	freopen("expr.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 0, m - 1) REP(j, 1, n) scanf("%lld", &a[i][j]);
	scanf("%s", s + 1); len = str(s + 1);
	tot = 1; belong[1] = -1; Stack[0] = 1; int lstop = 0;
	REP(i, 1, len)
	{
		if ( s[i] == '(' )
		{
			++ tot; belong[tot] = -1; Stack[++ sum] = tot;
			son[Stack[sum - 1]].push_back(pii(tot, lstop));
			lstop = 0;
		}
		else if ( s[i] == ')' ) { -- sum; lstop = 0; }
		else if ( s[i] == '<' ) lstop = 1;
		else if ( s[i] == '>' ) lstop = 2;
		else if ( s[i] == '?' ) lstop = 3;
		else
		{
			++ tot; belong[tot] = s[i] - '0';
			son[Stack[sum]].push_back(pii(tot, lstop));
		}
	}
	REP(i, 1, n)
	{
		pos = i; Solve(1);
		REP(j, 0, m - 1) ans = (ans + f[1][j] * a[j][i]) % Mod;
	}
	printf("%lld\n", ans);
    return 0;
}
