#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define int long long

const int maxn = 10000010;
const int Mod = 998244353;

int T, n, m, p[maxn];

inline int power(int a, int b)
{
	int r = 1;
	while ( b ) 
	{
		if ( b & 1 ) r = (r * a) % Mod;
		a = (a * a) % Mod; b >>= 1;
	}
	return r;
}

signed main()
{
	freopen("ball.in", "r", stdin);
	freopen("ball.out", "w", stdout);
	scanf("%lld", &T);
	p[0] = p[1] = 1; REP(i, 2, maxn - 1) p[i] = (p[i - 1] * i) % Mod;
	while ( T -- ) 
	{
		scanf("%lld%lld", &n, &m);
		int ans = p[m];
		int sum = (p[n] * power(p[m], Mod - 2)) % Mod;
		sum = (sum * power(p[n - m], Mod - 2)) % Mod;
		sum = (sum * sum) % Mod;
		ans = (ans * sum) % Mod;
		printf("%lld\n", ans);
	}
	return 0;	
}
