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

int T, n;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d", &n);
		int ans = 0;
		int L = (n - 1) / 3 + 1;
		int R = n;
		ans += (R - L + 1) / 2;
		if ( L % 2 == 1 && R % 2 == 1 ) ++ ans;

		L = n / 2 + 1;
		R = n;
		ans += R - L + 1;
		printf("%d\n", ans);
	}
    return 0;
}
