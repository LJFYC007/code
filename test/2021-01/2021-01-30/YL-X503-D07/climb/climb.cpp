/***************************************************************
	File name: climb.cpp
	Author: ljfcnyali
	Create time: 2021年01月30日 星期六 09时08分18秒
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

const int maxm = 2e7 + 10;
const int maxn = 1e6 + 10;
const int Mod = 998244353;
const int inv2 = (Mod + 1) / 2;

int T, type, n, m, k, fac[maxm], inv[maxm], ans[maxn], sum[maxn], belong[maxn], block, d[maxm], num[maxm], prime[maxm], tot;
bool vis[maxm];
pii Q[maxn];
vector<pii> p;
unordered_map<int, int> F[200010];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; }

inline bool cmp (const pii &a, const pii &b) 
{
	if ( belong[a.first] != belong[b.first] ) return belong[a.first] < belong[b.first];
	return a.second < b.second;
}

inline int f(int x) 
{ 
	int ans = 0;
	for ( int i = n + x + 2; i - 1 <= n + n; i += x + 2 ) 
		ans = (ans + C(n + n, i) + C(n + n, i) - C(n + n, i - 1) - C(n + n, i + 1)) % Mod;
	return ans;
}

signed main()
{
    freopen("climb.in", "r", stdin);
    freopen("climb.out", "w", stdout);
	scanf("%lld%lld", &T, &type);
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;

	if ( type == 0 ) 
	{
		REP(i, 1, T) 
		{ 
			scanf("%lld%lld", &n, &k);
			if ( (n - k) % 2 == 0 ) 
			{
				ans[i] = k * C(n, (n - k) / 2) % Mod;
				sum[i] = C(n, (n - k) / 2);
				++ k;
			}
			m = (n - k - 1) / 2; Q[i] = pii(n, m); 
			if ( m >= 0 ) p.push_back(pii(n, m)); 
			if ( m >= 1 ) p.push_back(pii(n - 1, m - 1)); 
		}
		n = 200000; block = 300; REP(i, 1, n) belong[i] = (i - 1) / block + 1;
		sort(p.begin(), p.end(), cmp); n = m = 1; int val = 2;
		for ( register auto it : p ) 
		{
			int lim1 = it.first, lim2 = it.second;
			while ( n < lim1 ) { ++ n; val = (val + val - C(n - 1, m)) % Mod; }
			while ( n > lim1 ) { -- n; val = (val + C(n, m)) * inv2 % Mod; }
			while ( m < lim2 ) { ++ m; val = (val + C(n, m)) % Mod; }
			while ( m > lim2 ) { -- m; val = (val - C(n, m + 1)) % Mod; }
			F[n][m] = val;
		}
		REP(i, 1, T)
		{
			n = Q[i].first; m = Q[i].second;
			ans[i] = (ans[i] + (2 * n - 1) * F[n][m]) % Mod;
			ans[i] = (ans[i] - 4 * n * F[n - 1][m - 1]) % Mod;
			sum[i] = (sum[i] + 2 * F[n][m]) % Mod;
			ans[i] = ans[i] * power(sum[i], Mod - 2) % Mod;
			printf("%lld\n", (ans[i] + Mod) % Mod);
		}
	}
	else 
	{
		n = maxm - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
		inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
		n = maxm / 2;
		d[1] = 1; 	
		REP(i, 2, n)
		{
			if ( !vis[i] ) { prime[++ tot] = i; d[i] = 2; num[i] = 2; }
			for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j ) 
			{
				vis[i * prime[j]] = true;
				if ( i % prime[j] == 0 ) 
				{ 
					d[i * prime[j]] = d[i] / num[i] * (num[i] + 1); 
					num[i * prime[j]] = num[i] + 1;
					break ; 
				}
				d[i * prime[j]] = d[i] + d[i]; num[i * prime[j]] = 2;
			}
		}
		while ( T -- ) 
		{
			scanf("%lld", &n); 
			if ( n % 2 == 1 ) { puts("0"); continue ; } 
			n /= 2; int ans = 0, sum = (C(n + n, n) - C(n + n, n + 1)) % Mod;
			REP(i, 2, n + 1) 
			{
				int num = d[i] - 1; 
				ans = (ans - 2 * num * C(n + n, n + i)) % Mod;
				ans = (ans + num * C(n + n, n + i + 1)) % Mod;
				ans = (ans + num * C(n + n, n + i - 1)) % Mod;
			}
			ans = ans * power(sum, Mod - 2) % Mod;
			printf("%lld\n", (ans + Mod) % Mod);
		}
	}

    return 0;
}
