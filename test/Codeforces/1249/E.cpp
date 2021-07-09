#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 200010;

int n, c, a[maxn], b[maxn], f[maxn], sum;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &c);
	REP(i, 1, n - 1) scanf("%d", &a[i]);
	REP(i, 1, n - 1) { scanf("%d", &b[i]); sum += b[i]; }
	printf("0 ");
	int Min = sum + c;
	REP(i, 1, n - 1)
	{
		sum -= b[i];
		f[i] = min(Min - sum, f[i - 1] + a[i]);
		Min = min(Min, f[i] + c + sum);
		printf("%d ", f[i]);
	}
	puts("");
	return 0;
}
