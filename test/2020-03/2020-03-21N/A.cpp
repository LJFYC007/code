#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define y second
#define x first
typedef long long LL;

const int maxn = 110;
const int INF = 0x3f3f3f3f;

int n, m, a[maxn][maxn], f[maxn][maxn];
char s[maxn];
queue<pii> Q;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n)
	{
		scanf("%s", s + 1);
		REP(j, 1, m) if ( s[j] == '.' ) a[i][j] = 1; else a[i][j] = 2;
	}
	REP(i, 1, n) REP(j, 1, m) f[i][j] = INF;
	Q.push(pii(1, 1)); f[1][1] = a[1][1] - 1;
	while ( !Q.empty() )
	{
		pii u = Q.front(); Q.pop();
		pii v = pii(u.first + 1, u.second);
		if ( a[u.first][u.second] == 1 && a[v.first][v.second] == 2 )
		{
			if ( f[v.x][v.y] > f[u.x][u.y] + 1 )
			{
				f[v.x][v.y] = f[u.x][u.y] + 1;
				Q.push(v);
			}
		}
		else if ( f[v.x][v.y] > f[u.x][u.y] ) { f[v.x][v.y] = f[u.x][u.y]; Q.push(v); }

		v = pii(u.first, u.second + 1);
		if ( a[u.first][u.second] == 1 && a[v.first][v.second] == 2 )
		{
			if ( f[v.x][v.y] > f[u.x][u.y] + 1 )
			{
				f[v.x][v.y] = f[u.x][u.y] + 1;
				Q.push(v);
			}
		}
		else if ( f[v.x][v.y] > f[u.x][u.y] ) { f[v.x][v.y] = f[u.x][u.y]; Q.push(v); }
	}
	printf("%d\n", f[n][m]);
	return 0;
}
