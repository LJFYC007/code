#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 5010;

int n, m, ans, f[maxn][maxn];
char s[maxn], t[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
#endif
	scanf("%s", s + 1); n = str(s + 1);
	scanf("%s", t + 1); m = str(t + 1);
	for ( int i = n; i >= 1; -- i ) for ( int j = m; j >= 1; -- j ) 
	{
		int k = 0;
		while ( i + k <= n && j + k <= m && s[i + k] == t[j + k] ) ++ k;
		f[i][j] = max(max(f[i + 1][j], f[i][j + 1]), k);
		ans = max(ans, k + f[i + k][j + k]);
	}
	printf("%d\n", ans);
	return 0;
}
