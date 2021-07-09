#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int n, m, p[maxn], a[maxn], b[maxn], N1, N2, nex[maxn];
double f[20][20];

inline double Solve(int x, int len, bool op, bool pre)
{
	if ( x > N1 ) return 1;
	if ( !op && !pre && f[x][len] ) return f[x][len];
	int Max = op ? a[x] : 9;
	double ret = 0;
	REP(i, 0, Max)
	{
		int j = len;
		while ( j && j < N2 && i != b[j + 1] ) j = nex[j];
		if ( j < N2 && i == b[j + 1] ) ++ j;
		if ( N2 == 1 && b[1] == 0 && pre && !i ) j = 0;
		if ( j == N2 ) continue ;
		double k = Solve(x + 1, j, op & (i == Max), pre & (i == 0));
		ret += k * exp(i * p[N1 - x] * 1.0 / n);
	}
	if ( !op && !pre ) f[x][len] = ret;
	return ret;
}

int main()
{
	freopen("calc.in", "r", stdin);
	freopen("calc.out", "w", stdout);
	scanf("%d%d", &n, &m);
	p[0] = 1; REP(i, 1, 9) p[i] = p[i - 1] * 10;
	int x;
	x = n; while ( x ) { a[++ N1] = x % 10; x /= 10; }
	reverse(a + 1, a + N1 + 1);
	x = m; while ( x ) { b[++ N2] = x % 10; x /= 10; }
	reverse(b + 1, b + N2 + 1);
	if ( !N2 ) ++ N2;
	for ( int i = 2, j = 0; i <= N2; ++ i )
	{
		while ( j && b[i] != b[j + 1] ) j = nex[j];
		if ( b[i] == b[j + 1] ) ++ j;
		nex[i] = j;
	}
	double ans = Solve(1, 0, 1, 1);
	printf("%.3lf\n", ans - 1);
	return 0;
}
