/***************************************************************
	File name: sequence.cpp
	Author: ljfcnyali
	Create time: 2021年06月20日 星期日 09时36分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, f[maxn], g[maxn][21], h[maxn][21], ans, Mod, a[maxn][21], b[maxn][21];

signed main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);
	scanf("%d%d", &n, &Mod);
	REP(i, 0, n) 
	{
		for ( int j = 20; j >= 0; -- j ) a[i][j] = a[i][j + 1] * 2 + ((i >> j) & 1);
		b[i][0] = i & 1;
		REP(j, 1, 20) b[i][j] = b[i][j - 1] + (((i >> j) & 1) ? 1 << j : 0);
	}
	REP(i, 0, n) f[i] = 1;

	int sum = 0;
	REP(x, 0, n) 
	{
		REP(i, 0, 20) 
		{
			if ( (x >> i) & 1 ) g[x][i] = (g[x][i] - h[a[x][i + 1]][i + 1]) % Mod;
			f[x] = (f[x] + g[x][i]) % Mod;
		}
		f[x] = (f[x] + sum) % Mod; sum = (sum + f[x]) % Mod;
		REP(i, 0, 20)
		{
			if ( b[x][i] == (1 << i) ) 
				h[a[x][i + 1] + 1][i + 1] = (h[a[x][i + 1] + 1][i + 1] + h[a[x][i + 1]][i + 1]) % Mod;
			h[a[x][i + 1] + 1][i + 1] = (h[a[x][i + 1] + 1][i + 1] + g[x][i]) % Mod;
			if ( !((x >> i) & 1) )
				h[a[x][i + 1] + 1][i + 1] = (h[a[x][i + 1] + 1][i + 1] + 1ll * f[x] * (1 << i)) % Mod;
		}
	}

	REP(i, 0, n) ans = (ans + f[i]) % Mod;
	printf("%d\n", (ans + Mod) % Mod); 
    return 0;
}
