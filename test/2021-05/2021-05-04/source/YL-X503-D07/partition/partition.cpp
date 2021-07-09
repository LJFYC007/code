#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e6 + 10;
const int maxm = 1010;
const int Mod = 998244353;

int n, k, p, h[maxn], g[maxn], f[maxn], ans;

inline void add(int &x, int y) { x = x + y >= Mod ? x + y - Mod : x + y; }  

int main()
{
#ifndef ONLINE_JUDGE
	freopen("partition.in", "r", stdin);
	freopen("partition.out", "w", stdout);
#endif
	scanf("%d%d%d", &n, &k, &p);
	REP(i, 0, p - 1) scanf("%d", &h[i]);
	if ( k > 0 ) 
	{
		g[0] = 1; 
		REP(m, 1, n) 
		{
			REP(i, 0, n) if ( i + m <= n ) g[i + m] = (g[i + m] + g[i]) % Mod;
			int val = m * (m - 1) / 2 * k + m;
			if ( val > n ) break ; 
			if ( h[m % p] ) ans = (ans + g[n - val]) % Mod;
		}
	}
	else
	{
		g[0] = f[0] = 1; int m = sqrt(n);
		REP(i, 1, m) REP(j, 0, n - i) add(g[i + j], g[j]);
		int num = m + 1; ans = g[n];
		REP(i, 1, m) 
		{
			for ( int j = n; j >= num; -- j ) f[j] = f[j - m - 1];
			REP(j, num + i, n) add(f[j], f[j - i]);
			REP(j, num, n) ans = (ans + 1ll * f[j] * g[n - j]) % Mod;
			num += m + 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}
