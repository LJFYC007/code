#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 310;
const int M = 6350400;
const int m = 2520;

int n, a[maxn][maxn], g[M], h[M], t[M];
LL f[M], ans;
const int p[26] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113};
bool vis[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("silence.in", "r", stdin);
	freopen("silence.out", "w", stdout);
#endif
	scanf("%d", &n); 
	REP(i, 1, n)
	{
		int k; scanf("%d", &k);
		REP(j, 0, k - 1) { int x; scanf("%d", &x); a[k][j] += x; }
	}
	REP(i, 0, 25)
	{
		REP(j, 0, p[i] - 1)
		{
			for ( int k = p[i]; k <= 120; k += p[i] ) 
			{
				vis[k] = true; int d = __gcd(k, m);
				for ( int o = j; o < k; o += p[i] ) t[o % d] = max(t[o % d], a[k][o]);
				REP(o, 0, d - 1) { for ( int s = o; s < m; s += d ) h[s] += t[o]; t[o] = 0; } 
			}
			REP(k, 0, m - 1) { g[k] = max(g[k], h[k]); h[k] = 0; } 
		}
		REP(j, 0, m - 1) { f[j] += g[j]; g[j] = 0; } 
	}

	REP(i, 0, m - 1) for ( int j = m + i; j < M; j += m ) f[j] = f[i];
	REP(i, 1, 120) if ( !vis[i] ) 
	{
		int x = 0;
		REP(k, 0, M - 1) 
		{
			f[k] += a[i][x ++];
			if ( x == i ) x = 0;
		}
	}
	REP(i, 0, M - 1) ans = max(ans, f[i]);
	printf("%lld\n", ans);
	return 0;
}
