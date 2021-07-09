#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;
const int INF = 0x3f3f3f3f;

int n, f[maxn], g[maxn][21], a[maxn], b[maxn], A[maxn], B[maxn];

inline bool cmp(int n)
{
	REP(i, 1, n)
	{
		if ( A[i] < B[i] ) return true;
		if ( A[i] > B[i] ) return false;
	}
	return false;
}

int main()
{
	freopen("pl.in", "r", stdin);
	freopen("pl.out", "w", stdout);
	scanf("%d", &n);
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, n) scanf("%d", &b[i]);
	REP(i, 1, (1 << n) - 1) f[i] = INF;
	REP(i, 0, (1 << n) - 2) REP(j, 1, n)
	{
		if ( (i >> j - 1) & 1 ) continue ;
		int x = i | (1 << j - 1);
		int val = INF;
		REP(k, 1, n) if ( (x >> k - 1) & 1 ) val = min(val, a[j] ^ b[k]);
		val += f[i];
		if ( val < f[x] )
		{
			f[x] = val;
			int tot = 0;
			REP(k, 1, n) if ( (i >> k - 1) & 1 ) { ++ tot; g[x][tot] = g[i][tot]; }
			g[x][++ tot] = j;
		}
		else if ( val == f[x] )
		{
			int tot = 0;
			REP(k, 1, n) if ( (x >> k - 1) & 1 ) B[++ tot] = g[x][tot];
			REP(k, 1, tot - 1) A[k] = g[i][k]; A[tot] = j;
			if ( cmp(tot) ) REP(k, 1, tot) g[x][k] = A[k];
		}
	}
	printf("%d\n", f[(1 << n) - 1]);
	REP(i, 1, n) printf("%d ", g[(1 << n) - 1][i]); puts("");
	return 0;
}
