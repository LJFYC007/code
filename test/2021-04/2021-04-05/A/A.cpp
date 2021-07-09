/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年04月05日 星期一 15时42分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n, q, a[maxn], fac[maxn];
bool vis[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &q);
	fac[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i;
	REP(i, 1, n) 
	{ 
		int x = 1; 
		while ( q > fac[n - i] ) { q -= fac[n - i]; ++ x; } 
		REP(j, 1, n) 
		{
			if ( !vis[j] ) -- x;
			if ( !x ) { a[i] = j; vis[j] = true; break ; }
		}
	}

	printf("%lld\n", n + 1);
	REP(i, 1, n - 1) 
	{
		REP(j, 1, a[i] - 1) printf("%lld ", n);	
		printf("%lld ", i + 1);
		REP(j, a[i] + 1, n) printf("%lld ", n + 1);	
		puts("");
	}
	REP(i, 1, n) printf("%lld ", n); puts("");
	REP(i, 1, n) printf("%lld ", n + 1); puts("");
	puts("1");
	if ( !q ) puts("0");
	else printf("1 %lld\n", n);
    return 0;
}
