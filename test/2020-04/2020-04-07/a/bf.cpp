#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;
const int Mod = 998244353;

int n, m, N, a[maxn], ans;
char s[maxn];

inline int get(int l, int r) { return ((l + r) * (r - l + 1) / 2) % Mod; }

signed main()
{
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
	scanf("%s", s + 1); n = str(s + 1);
	REP(i, 1, maxn - 10)
	{
		int x = i, ret = 0; m = 0;
		while ( x ) { a[++ m] = x % 10; x /= 10; }
		if ( !a[1] || m > n ) continue ;
		REP(j, 1, m - 1) REP(k, j + 1, m) if ( a[j] > a[k] ) ++ ret;
		x = 0;
		REP(j, 1, m) x = x * 10 + a[j];
		int L = ret > x ? 0 : (x - ret) / m;
		if ( L * m + ret <= x ) ++ L;
		int R = n - m; bool flag = false;
		REP(j, 1, m) if ( a[j] > s[j] - '0' ) { flag = true; break ; } else if ( a[j] < s[j] - '0' ) break ;
		if ( flag == true ) -- R;
		if ( L <= R )
		{
			ans = (ans - x * (R - L + 1)) % Mod;
			ret %= Mod;
			ans = (ans + ret * (R - L + 1)) % Mod;
			ans = (ans + m * get(L, R)) % Mod;
		}
	}
	ans = (ans * 2) % Mod;

	REP(i, 1, n) N = N * 10 + s[i] - '0';
	REP(i, 1, N)
	{
		int x = i, ret = 0; m = 0;
		while ( x ) { a[++ m] = x % 10; x /= 10; }
		for ( int j = m; j >= 2; -- j ) REP(k, 1, j - 1) if ( a[j] > a[k] ) -- ret;
		x = 0;
		REP(j, 1, m) x = x * 10 + a[j];
		ret += x;
		ans = (ans + ret) % Mod;
	}
	printf("%lld\n", (ans + Mod) % Mod);

	return 0;
}
