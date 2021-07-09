#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e7 + 10;

int n, k, p, a[maxn], b[maxn], ans1, ans2;

inline void read(int &x)
{
	char c = getchar(); x = 0;
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
	freopen("disguise.in", "r", stdin);
	freopen("disguise.out", "w", stdout);
	scanf("%lld%lld%lld", &n, &k, &p);
	REP(i, 1, n) { int x; read(x); a[i] = b[i] = x; }
	REP(i, 1, n) a[i] += a[i - 1];
	for ( int i = n; i >= 1; -- i ) b[i] += b[i + 1];
	int sum = 0;
	REP(i, 1, (n + 1) / 2)
	{
		if ( a[min(n, i + k * i)] - (k == 0 ? a[i - 1] : 0) >= (sum + 1) * p )
		{
			if ( k ) ++ sum;
		}
		else ++ ans1;
	}
	sum = 0;
	for ( int i = n; i > (n + 1) / 2; -- i )
		if ( b[max(1ll, i - k * (n - i + 1))] - (k == 0 ? b[i + 1] : 0) >= (sum + 1) * p )
		{
			if ( k ) ++ sum;
		}
		else ++ ans2;
	printf("%lld\n", max(ans1, ans2));
	return 0;
}
