/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年11月03日 星期日 15时48分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long 
typedef long long LL;

int n, C, k;
map<int, int> Map;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &C, &k);
    Map[0] = 1; int block = C / k;
    REP(i, 2, n) { int x; scanf("%lld", &x); ++ Map[x % block]; }
    for ( auto i : Map ) if ( i.second >= k ) { puts("Yes"); return 0; } 
    puts("No");
    return 0;
}
