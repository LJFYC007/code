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

int n, m, k;
pii a[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
	freopen("power.in", "r", stdin);
	freopen("power.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &k, &m);
	REP(i, 1, n) scanf("%lld%lld", &a[i].first, &a[i].second);
	int ans = 0;
	REP(i, a[1].first, a[1].second) ans = (ans + power(max(i, m), k)) % Mod;
	printf("%lld\n", ans * power(a[1].second - a[1].first + 1, Mod - 2) % Mod);
	return 0;
}
