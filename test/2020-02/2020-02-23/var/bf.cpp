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

int n, a[maxn], ans;
map<int, bool> Map;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
	freopen("var.in", "r", stdin);
	freopen("var.out", "w", stdout);
	scanf("%d", &n);
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, n) REP(j, i, n)
	{
		int sum = 0; REP(k, i, j) sum += a[k]; sum = sum * power(j - i + 1, Mod - 2) % Mod;
		int ret = 0; REP(k, i, j) { int x = (a[k] - sum); ret = (ret + x * x) % Mod; }
		ret = ret * power(j - i + 1, Mod - 2) % Mod;
		if ( !Map[ret] ) { Map[ret] = true; ++ ans; printf("%d %d\n", i, j); }
	}
	printf("%d\n", ans);
	return 0;
}
