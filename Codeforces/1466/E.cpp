/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e5 + 10;
const int Mod = 1e9 + 7;

int T, n, a[maxn], b[maxn], num[61], val[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T);
	while ( T -- )
	{
		scanf("%lld", &n); REP(i, 1, n) scanf("%lld", &a[i]);
		int ans = 0;
		REP(i, 0, 60)
		{
			num[i] = 0;
			REP(j, 1, n) if ( (a[j] >> i) & 1 ) ++ num[i];
		}
		REP(j, 1, n)
		{
			val[j] = 0;
			REP(i, 0, 60)
			{
				int sum, x = (1ll << i) % Mod;
				if ( (a[j] >> i) & 1 ) sum = n;
				else sum = num[i];
				val[j] = (val[j] + sum * x) % Mod;
			}
		}
		REP(i, 0, 60) REP(j, 1, n) if ( (a[j] >> i) & 1 )
		{
			int x = (1ll << i) % Mod;
			int ret = num[i] * val[j] % Mod;
			ans = (ans + x * ret) % Mod;
		}
		printf("%lld\n", (ans + Mod) % Mod);
	}

    return 0;
}
