/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, m, num[maxn], ans[maxn], t[maxn];
vector<int> a[maxn], c[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d%d", &n, &m);
		REP(i, 1, n) { a[i].clear(); num[i] = 0; }
		REP(i, 1, m) { c[i].clear(); ans[i] = 0; } 
		REP(i, 1, m)
		{
			int k, x; scanf("%d", &k);
			REP(j, 1, k) { scanf("%d", &x); a[x].push_back(i); c[i].push_back(x); } 
			if ( k == 1 ) ++ num[x];
		}
		bool flag = false;
		REP(i, 1, n) if ( num[i] > (m + 1) / 2 ) flag = true;
		if ( flag ) { puts("NO"); continue ; } 
		puts("YES");

		REP(i, 1, n) t[i] = (m + 1) / 2;
		REP(i, 1, m) if ( c[i].size() == 1 ) { ans[i] = c[i][0]; -- t[c[i][0]]; }
		REP(i, 1, n) for ( auto it : a[i] ) if ( t[i] && !ans[it] ) { ans[it] = i; -- t[i]; } 
		REP(i, 1, m) printf("%d ", ans[i]); puts("");
	}
    return 0;
} 
