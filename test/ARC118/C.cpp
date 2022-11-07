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

int n, a[maxn];
bool vis[maxn];
vector<int> p;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	a[1] = 2 * 89; a[2] = 3 * 5 * 7 * 89;
	int num = 2;
	REP(i, 2, 10000) 
	{
		if ( i % 89 == 0 ) continue ;
		if ( i % 2 != 0 ) continue ; 
		if ( i % 3 != 0 && i % 5 != 0 && i % 7 != 0 ) continue ;
		a[++ num] = i;
	}
	REP(i, 1, n) printf("%d ", a[i]); puts("");
    return 0;
}
