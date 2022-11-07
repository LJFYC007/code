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

const int maxn = 2010;

char a[maxn][maxn];
int ans, sum, n, m;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n) { getchar(); REP(j, 1, m) scanf("%c", &a[i][j]); }
	bool flag = true;
	for ( int i = n, j = 1; i >= 1; )
	{
		int posx = i, posy = j;
		sum = 0;
		while ( flag ) 
		{
			if ( posx > n || posy > m || posx < 1 || posy < 1 ) break ; 
			if ( a[posx - 1][posy + 1] == '/' ) 
			{
				posx -= 2; posy += 2;
				ans += sum;
			}
			else if ( a[posx][posy + 1] == '-' ) 
			{
				posy += 4;
				++ sum;
			}
			else break ; 
		}

		if ( a[i - 1][j + 1] == '/' ) { i -= 2; j += 2; flag = false; }
		else { i -= 3; flag = true; } 
	}
	printf("%d\n", ans);
    return 0;
}
