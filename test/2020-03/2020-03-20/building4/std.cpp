#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int INF = 2e9;

int n, m, a[maxn], b[maxn], f1[maxn][2], f2[maxn][2], ans[maxn];

inline void Solve(int i, int col, int num)
 {
	ans[i] = col;
	if ( i == 1 ) return ;
	if ( f1[i - 1][0] <= num && num <= f2[i - 1][0] && a[i - 1] <= (col == 1 ? a[i] : b[i]) ) Solve(i - 1, 1, num - 1);
	else Solve(i - 1, 2, num);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); m = n; n *= 2;
	REP(i, 1, n) scanf("%d", &a[i]);
	REP(i, 1, n) scanf("%d", &b[i]);
	REP(i, 1, n) { f1[i][0] = f1[i][1] = INF; f2[i][0] = f2[i][1] = 0; }
	REP(i, 1, n)
	{
		if ( a[i - 1] <= a[i] )
		{
			f1[i][0] = min(f1[i][0], f1[i - 1][0] + 1);
			f2[i][0] = max(f2[i][0], f2[i - 1][0] + 1);
		}
		if ( a[i - 1] <= b[i] )
		{
			f1[i][1] = min(f1[i][1], f1[i - 1][0]);
			f2[i][1] = max(f2[i][1], f2[i - 1][0]);
		}
		if ( b[i - 1] <= b[i] )
		{
			f1[i][1] = min(f1[i][1], f1[i - 1][1]);
			f2[i][1] = max(f2[i][1], f2[i - 1][1]);
		}
		if ( b[i - 1] <= a[i] )
		{
			f1[i][0] = min(f1[i][0], f1[i - 1][1] + 1);
			f2[i][0] = max(f2[i][0], f2[i - 1][1] + 1);
		}
	}
	if ( f1[n][0] <= m && m <= f2[n][0] ) Solve(n, 1, m - 1);
	else if ( f1[n][1] <= m && m <= f2[n][1] ) Solve(n, 2, m);
	else { puts("-1"); return 0; }
	REP(i, 1, n) printf("%c", ans[i] == 1 ? 'A' : 'B'); puts("");
	return 0;
}
