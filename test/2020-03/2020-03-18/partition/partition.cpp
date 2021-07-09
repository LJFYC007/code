#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int T, n, m, ans, a[maxn], b[maxn], f[maxn];

inline void DFS(int x, int N1, int N2)
{
	if ( x == n + 1 ) { ++ ans; return ; }
	bool flag = false;
	REP(i, 1, N1 - 1) REP(j, i + 1, N1) if ( a[i] * a[j] == x ) { flag = true; break ; }
	if ( !flag ) { a[N1 + 1] = x; DFS(x + 1, N1 + 1, N2); }
	flag = false;
	REP(i, 1, N2 - 1) REP(j, i + 1, N2) if ( b[i] * b[j] == x ) { flag = true; break ; }
	if ( !flag ) { b[N2 + 1] = x; DFS(x + 1, N1, N2 + 1); }
}

int main()
{
	freopen("partition.in", "r", stdin);
	freopen("partition.out", "w", stdout);
	scanf("%d", &T);
	REP(i, 1, 15)
	{
		n = i; ans = 0; DFS(1, 0, 0);
		f[i] = ans;
	}
	while ( T -- )
	{
		scanf("%d%d", &n, &m);
		printf("%d\n", f[n] % m);
	}
	return 0;
}
