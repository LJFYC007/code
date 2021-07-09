#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;
const int INF = 0x3f3f3f3f3f;

int n, a[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline pii Solve(int l, int r, int lim)
{
	int Min = INF, num = 0;
	REP(i, l, r) if ( a[i] < Min ) { Min = a[i]; num = 1; } else if ( a[i] == Min ) ++ num;
	int sum1 = 1, sum2 = 1;
	for ( int i = l, j; i <= r; i = j + 1 )
	{
		j = i; if ( a[i] == Min ) continue ;
		while ( j < r && a[j + 1] != Min ) ++ j;
		pii x = Solve(i, j, Min);
		sum1 = sum1 * x.first % Mod;
		sum2 = sum2 * (x.first + x.second) % Mod;
	}
	pii ans;
	ans.first = power(2, Min - lim) * sum1 % Mod;
	ans.second = (power(2, num) * sum2 + (power(2, Min - lim) - 2) * sum1) % Mod;
	return ans;
}

signed main()
{
	freopen("restore.in", "r", stdin);
	freopen("restore.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &a[i]);
	int ans = 1;
	REP(i, 2, n - 1)
		if ( a[i] > max(a[i - 1], a[i + 1]) )
		{
			ans = ans * power(2, a[i] - max(a[i - 1], a[i + 1])) % Mod;
			a[i] = max(a[i - 1], a[i + 1]);
		}
	printf("%lld\n", ans * Solve(1, n, 0).second % Mod);
	return 0;
}
