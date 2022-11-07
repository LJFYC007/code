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

int n, a[maxn]; bool f[110][maxn];

inline bool Check()
{
	mem(f); f[0][0] = true;
	int sum = 0; REP(i, 1, n) sum += a[i];
	if ( sum & 1 ) return true; sum /= 2;
	REP(i, 1, n) REP(j, 0, sum) if ( f[i - 1][j] )
	{
		f[i][j] = true;
		if ( j + a[i] <= sum ) f[i][j + a[i]] = true;
	}
	if ( f[n][sum] ) return false;
	return true;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
	if ( Check() ) { puts("0"); return 0; } 
	-- n;
	REP(i, 1, n + 1)
	{
		swap(a[i], a[n + 1]);
		if ( Check() ) { printf("1\n%d\n", i); return 0; } 
		swap(a[i], a[n + 1]);
	}
    return 0;
}
