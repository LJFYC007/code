#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

unsigned int s;
int n, m, ans;

int main()
{
	freopen("js.in", "r", stdin);
	freopen("js.out", "w", stdout);
	cin >> m >> s;
	REP(i, 1, m)
	{
		int d = (s / 1024) % 10;
		n = n * 10 + d;
		s = 747796405 * s - 1403630843;
	}
	REP(j, 2, m)
	{
		int x = 0;
		REP(i, 1, j) x = x * 10 + 1;
		REP(i, 1, n) if ( i % x == 0 ) ++ ans;
	}
	printf("%d\n", ans);
	return 0;
}
