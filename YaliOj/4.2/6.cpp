/***************************************************************
	File name: 6.cpp
	Author: ljfcnyali
	Create time: 2019年05月31日 星期五 15时23分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10010;

char s[maxn];
int f[maxn][10], len, m, ans[maxn];

inline int minn(int x, int y)
{
	return s[x] <= s[y] ? x : y;
}

inline int check(int l, int r)
{
	int k = (int)(log((double)(r - l + 1)) / log(2.0));
    return minn(f[l][k],f[r - (1 << k) + 1][k]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	while ( ~scanf("%s", s) )
	{
		scanf("%d", &m); getchar(); len = str(s);
		m = len - m;
		REP(i, 0, len - 1) f[i][0] = i;
		for ( int j = 1; (1 << j) < len; ++ j )
			for ( int i = 0; i + (1 << j) - 1 < len; ++ i )
				f[i][j] = minn(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
		int pos = 0, num = 0;
		while ( m -- ) 
		{
			pos = check(pos, len - m - 1);
			ans[++ num] = s[pos ++];
		}
		int j;
		for ( j = 1; j <= num; ++ j ) if ( ans[j] != '0' ) break ; 
		if ( j == num + 1 ) printf("0");
		else while ( j <= num )  printf("%c", ans[j ++]);
		puts("");
	}
    return 0;
}
