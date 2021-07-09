/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年07月01日 星期四 08时48分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int n, m, q, f[maxn][maxn], pre[1 << 5][maxn][maxn], suf[1 << 5][maxn][maxn], p[maxn][maxn];
struct node { char s[maxn]; int len; } a[11], b;

inline void Solve(int (&g)[maxn][maxn], int x)
{
	REP(o, 1, b.len)
	{
		REP(i, o - 1, b.len) REP(j, 0, a[x].len) f[i][j] = 0;
		REP(i, o, b.len) REP(j, 1, a[x].len)	
		{
			f[i][j] = max(f[i - 1][j], f[i][j - 1]);
			if ( b.s[i] == a[x].s[j] ) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
		}
		REP(i, o, b.len) g[o][i] = f[i][a[x].len];
	}
}

inline void Merge(int (&f)[maxn][maxn], int (&g)[maxn][maxn], int (&h)[maxn][maxn])
{
	for ( int i = b.len; i >= 1; -- i ) REP(j, i, b.len)
	{
		int l = p[i][j - 1], r = p[i + 1][j];
		if ( i == j ) l = i - 1, r = i;
		REP(k, l, r) if ( g[i][k] + h[k + 1][j] >= f[i][j] ) 
		{
			f[i][j] = g[i][k] + h[k + 1][j];
			p[i][j] = k;
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) { scanf("%s", a[i].s + 1); a[i].len = str(a[i].s + 1); }
	scanf("%s", b.s + 1); b.len = str(b.s + 1);

	int X = n / 2, Y = n - X;
	REP(i, 1, X) Solve(pre[1 << i - 1], i);
	REP(i, 1, Y) Solve(suf[1 << i - 1], i + X);
	REP(o, 0, (1 << X) - 1) for ( int i = X; i >= 1; -- i ) if ( (o >> i - 1) & 1 ) 
	{
		Merge(pre[o], pre[o ^ (1 << i - 1)], pre[1 << i - 1]);
		break ; 
	}
	REP(o, 0, (1 << Y) - 1) for ( int i = Y; i >= 1; -- i ) if ( (o >> i - 1) & 1 ) 
	{
		Merge(suf[o], suf[o ^ (1 << i - 1)], suf[1 << i - 1]);
		break ; 
	}

	scanf("%d", &q);
	while ( q -- ) 
	{
		int s, x, y; scanf("%d%d%d", &s, &x, &y);
		int a = s & ((1 << X) - 1), b = s >> X, ret = 0;
		REP(i, x - 1, y) ret = max(ret, pre[a][x][i] + suf[b][i + 1][y]);
		printf("%d\n", ret);
	}
    return 0;
}
