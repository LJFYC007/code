#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define int long long

const int maxn = 1e5 + 10;
const int INF = 1e18;

int T, n, w, a[maxn], b[maxn], c[maxn], x;
double p[100];

signed main()
{
    freopen("merge.in", "r", stdin);
    freopen("merge.out", "w", stdout);
    scanf("%lld", &T);
	REP(i, 0, 61) p[(1ll << i) % 67] = 1.0 / (1ll << i);
    while ( T -- ) 
    {
        scanf("%lld%lld", &n, &w);
		REP(i, 1, n) scanf("%lld", &a[i]);
		x = 0; REP(i, 1, n) b[i] = (1ll << w + 1) - 1;
		for ( int o = w - 1; o >= 0; -- o ) 
		{
			x |= (1ll << o);
			REP(i, 1, n) c[i] = b[i] & (~(a[i] >> o));
			long double sum = 0;
			REP(i, 1, n) sum += p[(c[i] & -c[i]) % 67]; 
			if ( sum >= 1 ) REP(i, 1, n) b[i] = c[i];
			else x ^= (1ll << o);
		}
		printf("%lld\n", (1ll << w) - 1 - x);
    }
    return 0;
}
