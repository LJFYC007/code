/***************************************************************
	File name: AGC033D.cpp
	Author: ljfcnyali
	Create time: 2021年02月22日 星期一 20时52分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 187;

int n, m, f[maxn][maxn][maxn][20], a[maxn][maxn];
char s[maxn];

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
		REP(j, 1, m) a[i][j] = s[j] == '#' ? 1 : 2;
	}
	REP(i, 1, n) REP(j, i, n) REP(k, 1, m) REP(l, 0, 19) f[i][j][k][l] = k - 1;
	REP(i, 1, n) REP(j, i, n) for ( int k = m; k >= 1; -- k ) 
	{
		bool flag = true; REP(o, i + 1, j) if ( a[o][k] != a[o - 1][k] ) { flag = false; break ; } 
		if ( flag ) f[i][j][k][0] = a[i][k] == a[i][k + 1] ? f[i][j][k + 1][0] : k;
	}
	REP(l, 1, 19) REP(k, 1, m)
	{
		REP(i, 1, n) REP(j, i, n) 
		{
			int pos = f[i][j][k][l - 1];
			f[i][j][k][l] = max(f[i][j][k][l], pos);
			if ( pos < k ) continue ; 
			f[i][j][k][l] = max(f[i][j][k][l], f[i][j][pos + 1][l - 1]);
		}
		
		REP(i, 1, n)
		{
			int p = i;
			REP(j, i, n)
			{
				while ( p + 1 < j && min(f[i][p][k][l - 1], f[p + 1][j][k][l - 1]) <= min(f[i][p + 1][k][l - 1], f[p + 2][j][k][l - 1]) ) ++ p;
				f[i][j][k][l] = max(f[i][j][k][l], min(f[i][p][k][l - 1], f[p + 1][j][k][l - 1]));
			}
		}
	}
	REP(l, 0, 19) if ( f[1][n][1][l] >= m ) { printf("%d\n", l); return 0; } 
    return 0;
}
