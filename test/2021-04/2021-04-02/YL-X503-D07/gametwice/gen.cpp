/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年04月02日 星期五 08时50分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int a[310][310], b[310];

int main()
{
    freopen("gametwice.in", "w", stdout);
	srand(time(0));
	int n = 300, m = 0;
	REP(i, 1, n)	
	{
		int k = n - i;
		REP(j, i + 1, n) b[j - i] = j;
		random_shuffle(b + 1, b + k + 1);
		REP(j, 1, k) if ( b[j] < b[j + 1] + rand() % 3 ) { ++ m; a[i][b[j]] = true; } else break ; 
	}
	
	printf("%d %d\n", n, m);
	REP(i, 1, n) printf("%c", rand() % 2 == 0 ? 'W' : 'B'); puts("");
	REP(i, 1, n) REP(j, 1, n) if ( a[i][j] ) printf("%d %d\n", i, j);
    return 0;
}
