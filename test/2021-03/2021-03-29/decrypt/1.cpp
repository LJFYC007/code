#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 5e5 + 10;

int n, k, a[maxn], ans[maxn], f[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("decrypt.in", "r", stdin);
	freopen("decrypt.out", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, n) scanf("%d", &a[i]);
	int sum = 0, m = n;
	for ( int i = n; i >= 1; -- i ) 
	{
		if ( a[i] == 1 ) 
		{ 
			++ sum; 
			for ( int j = sum; j >= 2; -- j ) f[j] = f[j - 1]; 
			f[1] = 1;
			continue ; 
		} 
		if ( sum >= k ) 
		{
			REP(j, 1, sum - k) ans[m --] = 1;
			sum = k;
		}
		int now = 1;
		REP(j, 1, k)
		{
			if ( now > sum ) break ; 
			if ( f[now] > j ) continue ;
			f[now] = j + 1; ++ now; 
		}
		while ( sum >= now ) { -- sum; ans[m --] = 1; } 
		ans[m --] = 0; 
	}
	REP(i, 1, sum) ans[i] = 1;
	REP(i, 1, n) printf("%d ", ans[i]); puts("");
	return 0;
}
