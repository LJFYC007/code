#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100010;

int n, a[maxn], b[maxn], p[maxn], ans;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) { scanf("%d", &a[i]); p[a[i]] = i; }
	REP(i, 1, n) { int x; scanf("%d", &x); b[x] = i; }
	int Max = 0;
	REP(i, 1, n)
	{
		if ( b[a[i]] < Max ) ++ ans;
		else Max = max(Max, b[a[i]]);
	}
	printf("%d\n", ans);
	return 0;
}
