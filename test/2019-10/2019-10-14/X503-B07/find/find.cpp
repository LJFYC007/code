#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;

char s[maxn];
int f[maxn][maxn], n, ans = 0x3f3f3f3f;

int main()
{
	freopen("find.in", "r", stdin);
	freopen("find.out", "w", stdout);
	scanf("%s", s + 1);
	n = str(s + 1);
	memset(f, 0x3f, sizeof(f));
	f[0][n + 1] = 0;
	REP(i, 1, n) f[0][i] = n - i + 1, f[i][n + 1] = i;
	REP(i, 1, n)
		for ( int j = n; j >= 1; -- j )
		{
			if ( s[i] == s[j] ) f[i][j] = f[i - 1][j + 1];
			f[i][j] = min(f[i][j], f[i - 1][j] + 1);
			f[i][j] = min(f[i][j], f[i][j + 1] + 1);
			if ( i >= j - 1 ) ans = min(ans, f[i][j]);
		}
	printf("%d\n", ans);
	return 0;
}

