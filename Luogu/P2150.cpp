#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 510;

int f1[maxn][maxn], f2[maxn][maxn], dp[maxn][maxn], n, Mod, ans;
int prime[10] = {2, 3, 5, 7, 11, 13, 17, 19};
struct node { int x, y; bool operator < (const node &a) const { return y < a.y; } } a[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &Mod);
	REP(i, 2, n)
	{
		int x = i;
		REP(j, 0, 7) { if ( x % prime[j] == 0 ) a[i].x |= (1 << j); while ( x % prime[j] == 0 ) x /= prime[j]; }
		a[i].y = x;
	}
	dp[0][0] = 1;
	sort(a + 2, a + n + 1);
	REP(o, 2, n)
	{
		if ( o == 2 || a[o].y == 1 || a[o].y != a[o - 1].y ) REP(i, 0, 255) REP(j, 0, 255) f1[i][j] = f2[i][j] = dp[i][j];
		for ( int i = 255; i >= 0; -- i ) for ( int j = 255; j >= 0; -- j ) if ( !(i & j) )
		{
			if ( !(a[o].x & j) ) f1[i | a[o].x][j] = (f1[i | a[o].x][j] + f1[i][j]) % Mod;
			if ( !(a[o].x & i) ) f2[i][j | a[o].x] = (f2[i][j | a[o].x] + f2[i][j]) % Mod;
		}
		if ( o == n || a[o].y == 1 || a[o].y != a[o + 1].y )
			REP(i, 0, 255) REP(j, 0, 255) if ( !(i & j) ) dp[i][j] = (f1[i][j] + f2[i][j] - dp[i][j]) % Mod;
	}
	REP(i, 0, 255) REP(j, 0, 255) if ( !(i & j) ) ans = (ans + dp[i][j]) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
