#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1e5 + 10;

int t, n, m;
struct node { int a, b, c, d; } ;

inline node Solve(int n, int m)
{
	if ( n + n > m && m + m > n ) return node{n + n - m, n + m, m + m - n, n + m};
	bool flag = false; node t; if ( n > m ) { swap(n, m); flag = true; } 
	if ( n * 4 < m ) { t = Solve(n * 8, m); t.c *= 2; t.d *= 2; } 
	else { t = Solve(n * 27, m * 8); t.a *= 2; t.b *= 2; t.c *= 3; t.d *= 3; } 
	if ( flag ) swap(t.a, t.c), swap(t.b, t.d);
	return t;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &t);
	while ( t -- ) 
	{
		scanf("%lld%lld", &n, &m);
		node t = Solve(n, m);
		printf("%lld %lld %lld %lld\n", t.a, t.b, t.c, t.d);
	}
	return 0;
}
