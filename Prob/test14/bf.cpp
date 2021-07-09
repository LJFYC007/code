/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年06月25日 星期五 14时37分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int n, m, a[maxn][maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(o, 1, n)
	{
		int x1, y1 ,x2 ,y2;
		scanf("%d%d%d%d", &x1 ,&y1, &x2, &y2);
		int num = 0;
		REP(i, y1, y2) REP(j, x1, x2)
		{
			if ( num % 5 == 0 ) a[i][j] = true;
			++ num;
		}
	}
	int ans = 0;
	REP(i, 0, 1000) REP(j, 0, 1000) if ( a[i][j] ) ++ ans;
	printf("%d\n", ans);
    return 0;
}
