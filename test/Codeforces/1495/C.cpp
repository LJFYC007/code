/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年03月10日 星期三 21时24分11秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 510;
 
int t, n, m;
char a[maxn][maxn];
 
inline void Get(int x, int y)
{
	while ( a[x][y] != 'X' ) 
	{ 
		a[x][y] = 'X'; 
		++ x; 
	} 
}
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &t);	
	while ( t -- ) 
	{
		scanf("%d%d", &n, &m);
		REP(i, 1, n) scanf("%s", a[i] + 1);
		int tmp=1;if(m%3==0) tmp=2;
		for ( int j = tmp; j <= m; j += 3 ) 
		{
		/*	if ( j + 2 == m ) 
			{
				REP(i, 1, n) if ( a[i][j + 1] == 'X' || a[i][j + 2] == 'X' ) 
					a[i][j + 1] = a[i][j + 2] = 'X';
			}
			else if ( j + 2 < m ) 
			{
			*/
				bool flag = false;
				REP(i, 1, n) if ( !flag && a[i][j + 1] == 'X' ) { a[i][j + 2] = 'X'; flag = true; } 
				REP(i, 1, n) if ( !flag && a[i][j + 2] == 'X' ) { a[i][j + 1] = 'X'; flag = true; } 
				if ( !flag ) { a[1][j + 1] = a[1][j + 2] = 'X'; }
			// }
			REP(i, 1, n) a[i][j] = 'X';
		}
		REP(i, 1, n) { REP(j, 1, m) printf("%c", a[i][j]); puts(""); } 
	}
    return 0;
}

