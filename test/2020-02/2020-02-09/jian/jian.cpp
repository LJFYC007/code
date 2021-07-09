#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6;

int n, m, a[maxn], ans, b[maxn];
bool vis[maxn];

inline bool cmp()
{
	REP(i, 1, n)
	{
		if ( a[i] > b[i] ) return true;
		if ( a[i] < b[i] ) return false;
	}
	return false;
}

inline bool Check()
{
	REP(i, 2, n)
	{
		int pos = i;
		REP(j, 1, n) { b[j] = a[pos]; ++ pos; if ( pos > n ) pos = 1; }
		if ( cmp() == false ) return false;
	}
	mem(vis);
	REP(i, 1, n)
	{
		int x = (a[i] + i) % n;
		if ( vis[x] ) return false;
		vis[x] = true;
	}
	return true;
}

inline void DFS(int x, int sum)
{
	if ( x == n + 1 )
	{
		if ( sum == m && Check() )  ++ ans;
		return ;
	}
	REP(i, 0, m - sum) { a[x] = i; DFS(x + 1, sum + i); }
}

int main()
{
	freopen("jian.in", "r", stdin);
	freopen("jian.out", "w", stdout);
	scanf("%d%d", &n, &m);
	DFS(1, 0);
	printf("%d\n", ans);
	return 0;
}
