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

const int maxn = 1e5 + 10;

int n, m, a[maxn], ans, b[maxn], f[maxn], g[maxn], pre[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i,1 , n) scanf("%d", &a[i]);
	for ( int l = 1, r; l <= n; l = r + 1  )
	{
		r = l; while ( a[r] == a[r + 1] ) ++ r;
		b[++ m] = a[l];
	}
	REP(i, 1, m) f[i] = g[i] = n + n + n;
	REP(i, 1, m)
	{
		f[i] = min(f[i - 1], g[i - 1]) + 1;
		if ( pre[b[i]] )
		{
			int x = pre[b[i]]; g[i] = min(f[x], g[x]) + (i - x - 1);
			if ( b[x - 1] == b[x + 1] ) g[i] = min(g[i], g[x] + (i - x - 2));
		}
		pre[b[i]] = i;
	}
	printf("%d\n", min(f[m], g[m]));
    return 0;
}
