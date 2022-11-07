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
typedef long long LL;

const int maxn = 1e5 + 10;

int a[10][10], n, m;
char s[maxn];

inline int Solve(int x, int y)
{
	if ( x == n && y == m ) return a[x][y]; 
	int ret = 0; if ( a[x][y] ) ret = 1;
	int Min1 = 10, Min2 = 10;
	REP(i, y + 1, m) if ( a[x][i] ) Min1 = i - y;
	REP(i, x + 1, n) if ( a[i][y] ) Min2 = i - x;
	if ( Min1 <= Min2 && y < m ) ret += Solve(x, y + 1);
	else ret += Solve(x + 1, y);
	return ret;
}

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
		REP(j, 1, m) a[i][j] = s[j] == '*';
	}
	printf("%d\n", Solve(1, 1));
    return 0;
}
