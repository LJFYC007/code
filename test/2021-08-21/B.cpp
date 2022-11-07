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
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, T, fac[3010], S[3010][3010];

const int Mod= 1e9 + 7;

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	n = 3000;
	fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod ;
	S[0][0] = 1;
	REP(i, 1, n) REP(j, 1, i) S[i][j] = (S[i - 1][j - 1] + S[i - 1][j] * j) % Mod;
	scanf("%lld", &T);
	while ( T -- ) 
	{
		scanf("%lld%lld", &n, &m);
		int ans = 0;
		REP(i, 1, n) REP(j, i - 1, i + 1) if ( j >= 1 && j <= m ) 
		{
			int ret = S[n][i] * fac[i] % Mod;
			ret = ret * S[m][j] % Mod * fac[j] % Mod;
			if ( i == j ) ret = ret * 2 % Mod;
			ans = ( ans + ret) % Mod;
		}
		printf("%lld\n", (ans + Mod) % Mod);
	}
    return 0;
}
