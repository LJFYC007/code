#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e4 + 10;

int n, m, f[maxn][11], g[maxn][11][11], ans, a[maxn];
char s[maxn];
bool flag, vis[maxn];

int main()
{
	freopen("delete.in", "r", stdin);
	freopen("delete.out", "w", stdout);
	scanf("%d", &n);
	scanf("%s", s + 1);
	ans = 6; flag = true;
	REP(i, 1, n)
	{
		if ( s[i] == 'a' ) { ans += 11; flag = true; }
		else { a[++ m] = s[i] - 'a'; vis[m] = flag; flag = false; }
	}
	memset(f, 0x3f, sizeof(f));
	memset(g, 0x3f, sizeof(g));
	f[0][a[1]] = 0;
	REP(i, 1, m) REP(j, 1, 10)
	{
		int Min = min(f[i - 1][a[i]] + 7, g[i - 1][a[i]][a[i]] + 7);
		if ( j != a[i] && !vis[i] ) Min = min(Min, f[i - 1][j]);
		if ( j != a[i] ) Min = min(Min, g[i - 1][a[i]][j]);
		f[i][j] = Min;
		REP(k, 1, 10)
		{
			Min = min(f[i - 1][a[i]] + 18, g[i - 1][a[i]][a[i]] + 18);
			if ( j != a[i] ) Min = min(Min, f[i - 1][j] + 11);
			if ( j != a[i] && k != a[i] ) Min = min(Min, g[i - 1][j][k] + 4);
			if ( k != a[i] ) Min = min(Min, g[i - 1][a[i]][k] + 11);
			if ( j != a[i] ) Min = min(Min, g[i - 1][j][a[i]] + 11);
			g[i][j][k] = Min;
		}
	}
	printf("%d\n", f[m][10] + ans - 7);
	return 0;
}
