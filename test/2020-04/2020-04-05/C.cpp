#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int Mod = 998244353;

int f[maxn];

inline int lowbit(int x) { return x & -x; }

inline int get(int x, int y)
{
	int ret = 0;
	REP(i, 1, 44)
	{
		int sum1 = f[i - 1] % Mod;
		int sum2 = ((x + f[i - 1]) / f[i]) % Mod;
		int sum3 = ((y + f[i - 1]) / f[i]) % Mod;
		ret = (ret + sum1 * (sum3 - sum2)) % Mod;
	}
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	REP(i, 0, 50) f[i] = 1ll << i;
	int n; scanf("%lld", &n);
	int ans = 0;
	for ( int i = 1, j; i <= n; i = j + 1 )
	{
		j = n / (n / i);
		int sum1 = (n / i) % Mod;
		ans = (ans + sum1 * get(i - 1, j)) % Mod;
	}
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
