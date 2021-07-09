#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 510;
const int Mod = 998244353;

int k, n, sum[maxn][maxn], a[maxn];
bool vis[maxn * maxn];
map<int, bool> Map;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Check(int len)
{
	Map.clear(); int ans = 0;
	REP(i, 1, len) REP(j, i, len)
	{
		int sum = 0; REP(k, i, j) sum += a[k]; sum = sum * power(j - i + 1, Mod - 2) % Mod;
		int ret = 0; REP(k, i, j) { int x = (a[k] - sum); ret = (ret + x * x) % Mod; }
		ret = ret * power(j - i + 1, Mod - 2) % Mod;
		if ( !Map[ret] ) { Map[ret] = true; ++ ans; }
	}
	return ans;
}

signed main()
{
	freopen("var.in", "r", stdin);
	freopen("var.out", "w", stdout);
	scanf("%lld", &k);
	srand(time(0));
	if ( k <= 500 )
	{
		printf("%lld\n", k);
		printf("2"); REP(i, 2, k) printf(" 3"); puts("");
		return 0;
	}
	n = 500;
	REP(i, 1, n) REP(j, i + 1, n) if ( __gcd(i, j) == 1 ) ++ sum[i][j];
	REP(i, 1, n) REP(j, 1, n) sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
	//REP(i, 1, n) REP(j, i, n) { printf("%lld %lld %lld\n", i, j, sum[i][j]); vis[sum[i][j]] = true; }
	//REP(i, 1, 100000) if ( !vis[i] ) printf("%lld\n", i);
	//cerr << 1 << endl;
	REP(i, 1, n) REP(j, i, n) if ( i + j <= n && sum[i][j] + 2 == k )
	{
		printf("%lld\n", i + j);
		printf("2");
		REP(o, 2, i) printf(" 2");
		REP(o, 1, j) printf(" 233333"); puts("");
		return 0;
	}
	else if ( i + j + 1 <= n && sum[i][j] + 2 + i + j == k )
	{
		int len = i + j + 1;
		REP(o, 1, i) a[o] = 2;
		REP(o, 1, j) a[i + o] = 233333;
		while ( true )
		{
			a[len] = rand() % 2333333 + 1;
			//cerr << Check(len) << endl;
			if ( Check(len) == k ) break ;
		}
		printf("%lld\n", len);
		REP(o, 1, len) printf("%lld ", a[o]); puts("");
		return 0;
	}
	return 0;
}
