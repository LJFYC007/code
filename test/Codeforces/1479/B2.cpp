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
 
int n, m, a[maxn], ans, x, y;
vector<int> col[maxn];
 
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) { scanf("%d", &a[i]); col[a[i]].push_back(i); }
	REP(i, 0, n) col[i].push_back(n + 1);
	REP(i, 1, n)
	{
		int z = a[i];
		if ( z == x || z == y ) continue ;
		auto it1 = lower_bound(col[x].begin(), col[x].end(), i);
		auto it2 = lower_bound(col[y].begin(), col[y].end(), i);
		if ( *it1 > *it2 ) { x = z; ++ ans; }
		else { y = z; ++ ans; }
	}
	printf("%d\n", ans);
    return 0;
}
