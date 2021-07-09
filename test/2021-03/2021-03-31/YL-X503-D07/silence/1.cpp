#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 310;
const int maxm = 1e6 + 10;

int n, p[maxm], ans, Begin[maxm], Next[maxm], To[maxm], e, id[maxn][maxn], m;
vector<int> a[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("silence.in", "r", stdin);
	freopen("silence.out", "w", stdout);
#endif
	scanf("%lld", &n); int t = 1; bool flag = true;
	REP(i, 1, 120) a[i].resize(i);
	REP(i, 1, n)
	{
		int k; scanf("%lld", &k); 
		REP(j, 0, k - 1) { int x; scanf("%lld", &x); a[k][j] += x; }
	}
	REP(i, 1, 120) REP(j, 0, i - 1) id[i][j] = ++ m;
	REP(i, 1, 120) REP(j, i + 1, 120) REP(x, 0, i - 1) REP(y, 0, j - 1)
	{
		int d = __gcd(i, j);
		if ( x % d == y % d ) add(id[i][x], id[j][y]);
	}
	printf("%lld\n", ans);
	return 0;
}
