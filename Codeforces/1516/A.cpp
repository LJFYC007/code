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

int n, k, T, a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d%d", &n, &k);
		REP(i, 1, n) scanf("%d", &a[i]);
		int pos = 1;
		while ( k ) 
		{
			while ( a[pos] == 0 ) ++ pos;
			if ( pos > n ) break ; 
			-- a[pos]; ++ a[n];
			k --;
		}
		REP(i, 1, n) printf("%d ", a[i]); puts("");
	}
    return 0;
}
