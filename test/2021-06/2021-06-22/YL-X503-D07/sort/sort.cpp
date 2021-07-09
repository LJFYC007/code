/***************************************************************
	File name: sort.cpp
	Author: ljfcnyali
	Create time: 2021年06月22日 星期二 10时13分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int Mod = 12345678;

int n, m, a[16], f[1 << 15], g[1 << 15], ans[16];

signed main()
{
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
	scanf("%lld%lld", &n, &m); 
	REP(i, 1, n) scanf("%lld", &a[i]); 
	REP(i, 1, n) 
	{
		int s = 0;
		REP(j, 1, n) if ( a[j] >= i ) s |= (1 << j - 1);
		f[s] = 1;
	}
	REP(o, 1, m) REP(i, 1, n - 1) 
	{
		REP(j, 0, (1 << n) - 1)
		{
			int x = (j >> i - 1) & 1, y = (j >> i) & 1; 
			int s = j; if ( x ) s -= 1 << i - 1; if ( y ) s -= 1 << i;
			
			if ( x > y ) swap(x, y);
			int t = s + (x ? 1 << i - 1 : 0) + (y ? 1 << i : 0);
			g[t] = (g[t] - f[j] * 232) % Mod;
			t = s + (y ? 1 << i - 1 : 0) + (x ? 1 << i : 0);
			g[t] = (g[t] + f[j] * 233) % Mod;
		}
		REP(j, 0, (1 << n) - 1) { f[j] = g[j]; g[j] = 0; }
	}
	REP(i, 0, (1 << n) - 1) REP(j, 1, n) if ( (i >> j - 1) & 1 ) ans[j] = (ans[j] + f[i]) % Mod;
	REP(i, 1, n) printf("%lld ", (ans[i] + Mod) % Mod);
    return 0;
}
