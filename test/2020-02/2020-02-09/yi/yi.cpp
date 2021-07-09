#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
#define LL __int128

const int maxn = 3e5 + 1000;
const LL block = 55;

LL n, a[maxn], *b;
int ans;
char s[maxn];

inline void Solve(LL x)
{
	LL sum1 = 1, sum2 = 0;
	ans += block;
	while ( x )
	{
		x *= 3; LL len = x & -x;
		sum1 *= 3; sum2 = sum2 * 3 + len;
		x = (x + len) & (1ll << block) - 1;
		++ ans;
	}
	REP(i, 0, n - 1) b[i] = b[i] * sum1; b[0] += sum2;
	REP(i, 0, n - 1) { b[i + 1] += b[i] >> block; b[i] &= (1ll << block) - 1; }
	while ( b[n] )
	{
		b[n + 1] = b[n] >> block;
		b[n] &= (1ll << block) - 1;
		++ n;
	}
	++ b; -- n;
}

signed main()
{
	freopen("yi.in", "r", stdin);
	freopen("yi.out", "w", stdout);
	scanf("%s", s); n = str(s); reverse(s, s + n);
	REP(i, 0, n - 1) a[i / block] |= ((LL)s[i] - '0') << (i % block);
	n = (n + block - 1) / block; b = a;
	while ( n > 1 ) Solve(b[0]);
	while ( b[0] > 1 )
	{
		if ( b[0] & 1 ) b[0] = b[0] * 3 + 1;
		else b[0] >>= 1;
		++ ans;
	}
	printf("%d\n", ans);
	return 0;
}
