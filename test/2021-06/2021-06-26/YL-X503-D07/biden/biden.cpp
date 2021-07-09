/***************************************************************
	File name: biden.cpp
	Author: ljfcnyali
	Create time: 2021年06月26日 星期六 10时57分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;
const int Mod = 998244353;

int n, m, w[maxn], a[maxn], f[maxn], g[maxn];

int main()
{
    freopen("biden.in", "r", stdin);
    freopen("biden.out", "w", stdout);
	scanf("%d%d", &n, &m);
	REP(i, 1, n) scanf("%d", &w[i]);
	while ( m -- ) 
	{
		int op, pos, val, l, r, k; scanf("%d", &op);
		if ( op == 1 ) { scanf("%d%d", &pos, &val); a[pos] += val; }
		if ( op == 2 ) { scanf("%d%d", &pos, &val); a[pos] -= val; }
		if ( op == 3 ) 
		{
			scanf("%d%d%d", &l, &r, &k);
			int sum = 0; mem(f); f[0] = 1;
			REP(i, l, r)
			{
				REP(x, 0, sum) REP(y, 0, a[i]) g[x + y * w[i]] = (g[x + y * w[i]] + f[x]) % Mod;
				sum += a[i] * w[i];
				REP(x, 0, sum) { f[x] = g[x]; g[x] = 0; }
			}
			int ans = 0; REP(i, 1, k) ans = (ans + f[i]) % Mod;
			printf("%d\n", ans);
		}
	}
    return 0;
}
