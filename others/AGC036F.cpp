/***************************************************************
	File name: AGC036F.cpp
	Author: ljfcnyali
	Create time: 2021年02月07日 星期日 08时42分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 510;

int n, m, Mod, l[maxn], r[maxn], ans, f[maxn][maxn];
pii a[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &Mod);
	REP(i, 0, n + n - 1)			
	{
		l[i] = ceil(sqrt(double(n * n - i * i)));
		r[i] = sqrt(double(4 * n * n - i * i));
		l[i] = max(l[i], 0ll); r[i] = min(r[i], n + n - 1) + 1;
		if ( i < n ) a[i] = pii(l[i], -i); else a[i] = pii(r[i], -i);
	}
	sort(a, a + n + n);
	REP(k, 0, n)
	{
		mem(f); f[0][0] = 1; int sum = 0;
		REP(i, 0, n + n - 1) 
		{
			int x = -a[i].second; if ( x >= n ) ++ sum;
			REP(j, 0, n) 
			{
				if ( x >= n && r[x] - sum - j + 1 > 0 ) f[i + 1][j] = (f[i + 1][j] + f[i][j] * (r[x] - sum - j + 1)) % Mod;
				if ( x < n ) 
				{
					if ( l[x] - sum - j > 0 ) f[i + 1][j + 1] = (f[i + 1][j + 1] - f[i][j] * (l[x] - sum - j)) % Mod;	
					if ( r[x] - k - n - (i + 1 - sum - j) + 1 > 0 )
						f[i + 1][j] = (f[i + 1][j] + f[i][j] * (r[x] - k - n - (i + 1 - sum - j) + 1)) % Mod;
				}
			}
		}
		ans = (ans + f[n + n][k]) % Mod;
	}
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
