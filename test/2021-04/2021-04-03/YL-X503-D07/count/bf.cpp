/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年04月03日 星期六 10时51分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int n, k, c, ans;
bool use[maxn][maxn], a[maxn][maxn];

inline bool Check()
{
	REP(i, 1, n)
	{
		bool flag = false;
		REP(j, 1, n) if ( a[i][j] ) flag = true;
		if ( !flag ) return false;
	}
	REP(i, 1, n)
	{
		bool flag = false;
		REP(j, 1, n) if ( a[j][i] ) flag = true;
		if ( !flag ) return false;
	}
	bool flag = false; REP(i, 1, n) if ( a[i][i] ) flag = true; if ( !flag ) return false;
	flag = false; REP(i, 1, n) if ( a[i][n + 1 - i] ) flag = true; if ( !flag ) return false;
	return true;
}

inline void DFS(int x, int y, int num)
{
	if ( num > c ) return ; 
	if ( x == n + 1 ) 
	{
		if ( num == c && Check() ) ++ ans;
		return ; 
	}
	if ( y == n + 1 ) { DFS(x + 1, 1, num); return ; } 
	if ( use[x][y] ) DFS(x, y + 1, num);
	else { a[x][y] = true; DFS(x, y + 1, num + 1); a[x][y] = false; DFS(x, y + 1, num); } 
}

int main()
{
    freopen("count.in", "r", stdin);
    freopen("count1.out", "w", stdout);
	scanf("%d%d%d", &n, &k, &c);
	REP(i, 1, k) { int x, y; scanf("%d%d", &x, &y); use[x][y] = true; } 
	DFS(1, 1, 0);
	printf("%d\n", ans % 10007);
    return 0;
}
