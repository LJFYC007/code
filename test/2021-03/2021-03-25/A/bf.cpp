#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e6 + 10;

int n, a[maxn], m[maxn], q;

inline bool Check(int x, int y)
{
	if ( (a[x] - a[y]) % __gcd(m[x], m[y]) == 0 ) return true;
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) scanf("%d%d", &m[i], &a[i]);
	scanf("%d", &q);
	while ( q -- ) 
	{
		int l, r, ans = 0; scanf("%d%d", &l, &r);
		REP(i, l, r) REP(j, i, r) 
		{
			bool flag = true;
			REP(k, i, j) if ( !Check(k, j) ) flag = false;
			if ( flag ) ++ ans; else break ; 
		}
		printf("%d\n", ans);
	}
	return 0;
}
