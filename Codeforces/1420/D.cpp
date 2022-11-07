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
#define x first
#define y second
#define int long long
typedef long long LL;

const int maxn = 6e5 + 10;
const int Mod = 998244353;

int n, m, k, fac[maxn], inv[maxn], p1[maxn], p2[maxn], ans;
pii a[maxn];
vector<int> p;
map<int, int> Map;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &k);
	REP(i, 1, n) { scanf("%lld%lld", &a[i].x, &a[i].y); ++ a[i].y; }
	REP(i, 1, n) { p.push_back(a[i].x); p.push_back(a[i].y); }
	sort(p.begin(), p.end());
	REP(i, 0, p.size() - 1) if ( !Map.count(p[i]) ) Map[p[i]] = ++ m;
	REP(i, 1, n) { ++ p1[Map[a[i].x]]; ++ p2[Map[a[i].y]]; }

	fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;

	int ret = 0;
	REP(i, 1, m)
	{
		ret -= p2[i];
		REP(j, 1, p1[i])
		{
			++ ret;
			ans = (ans + C(ret - 1, k - 1)) % Mod;
		}
	}
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
