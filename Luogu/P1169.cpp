#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss
const int maxn = 2010;

int n, m, a[maxn][maxn], Left[maxn][maxn], Right[maxn][maxn], up[maxn][maxn];
int ans1, ans2;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n)
		REP(j, 1, m)
		{
			scanf("%d", &a[i][j]);
			Left[i][j] = j;
			Right[i][j] = j;
			up[i][j] = 1;
		}
	REP(i, 1, n)
		REP(j, 2, m)
			if ( a[i][j] != a[i][j - 1] ) Left[i][j] = Left[i][j - 1];
	REP(i, 1, n)
		for ( int j = m - 1; j >= 1; -- j )
			if ( a[i][j] != a[i][j + 1] ) Right[i][j] = Right[i][j + 1];
	REP(i, 1, n)
		REP(j, 1, m)
		{
			if ( i > 1 && a[i][j] != a[i - 1][j] ) 
			{
				Left[i][j] = max(Left[i][j], Left[i - 1][j]);
				Right[i][j] = min(Right[i][j], Right[i - 1][j]);
				up[i][j] = up[i - 1][j] + 1;
			}
			int a = Right[i][j] - Left[i][j] + 1;
			int b = min(a, up[i][j]);
			ans1 = max(ans1, b * b);
			ans2 = max(ans2, a * up[i][j]);
		}
	printf("%d\n%d\n", ans1, ans2);
	return 0;
}

