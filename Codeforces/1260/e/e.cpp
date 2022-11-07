/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年11月28日 星期四 10时24分25秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 1e6 + 10;
 
int n, a[maxn], ret, m;
LL ans;
priority_queue<int, vector<int>, greater<int> > Q;
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
	REP(i, 1, n) scanf("%d", &a[i]);
	while ( (1 << m) < n ) ++ m;
	for ( int i = n; i >= 1; -- i )
	{
		if ( a[i] == -1 ) { cout << ans << endl; return 0; }
		Q.push(a[i]);
		if ( !ret ) { ans += Q.top(); Q.pop(); ret = 1 << -- m; }
		-- ret;
	}
    return 0;
}
