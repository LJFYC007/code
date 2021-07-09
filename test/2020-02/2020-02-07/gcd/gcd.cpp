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

int n, a[maxn], phi[maxn], prime[maxn], tot, ans, cnt[maxn];
bool vis[maxn];
vector<int> p[maxn], use;

signed main()
{
	freopen("gcd.in", "r", stdin);
	freopen("gcd.out", "w", stdout);
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &a[i]);
	phi[1] = 1;
	REP(i, 2, n)
	{
		if ( !vis[i] ) { prime[++ tot] = i; phi[i] = i - 1; }
		for ( int j = 1; j <= tot && i * prime[j] <= n; ++ j )
		{
			vis[i * prime[j]] = true;
			if ( i % prime[j] == 0 ) { phi[i * prime[j]] = phi[i] * prime[j]; break ; }
			phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
	REP(i, 1, n) for ( int j = 1; j * j <= i; ++ j )
	{
		if ( i % j != 0 ) continue ;
		int x = j, y = i / j;
		p[i].push_back(x); if ( x != y ) p[i].push_back(y);
	}
	REP(t, 1, n)
	{
		use.clear();
		for ( int i = t; i <= n; i += t )
			REP(j, 0, p[a[i]].size() - 1)
			{
				int x = p[a[i]][j]; ++ cnt[x];
				if ( cnt[x] == 1 ) use.push_back(x);
			}
		int ret = 0;
		REP(i, 0, use.size() - 1)
		{
			ret = (ret + (cnt[use[i]] * cnt[use[i]] % Mod) * phi[use[i]]) % Mod;
			cnt[use[i]] = 0;
		}
		ans = (ans + phi[t] * ret) % Mod;
	}
	printf("%lld\n", ans);
	return 0;
}
