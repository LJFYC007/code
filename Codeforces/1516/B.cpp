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

int T, n, a[maxn];
bool f[maxn][maxn];
unordered_map<int, int> Map;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d", &n); mem(f); Map.clear(); int m = 0;
		REP(i, 1, n) { scanf("%d", &a[i]); a[i] ^= a[i - 1]; }
		REP(i, 1, n - 1) { Map[a[i]] = ++ m; f[i][m] = true; } 
		REP(i, 2, n) REP(j, i, n)
		{
			int val = a[j] ^ a[i - 1];
			if ( !Map.count(val) ) continue ; 
			val = Map[val];
			if ( f[i - 1][val] ) f[j][val] = true;
		}
		bool flag = false;
		REP(i, 1, m) flag |= f[n][i];
		if ( flag ) puts("YES");
		else puts("NO");
	}
    return 0;
}
