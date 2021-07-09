/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月23日 星期四 19时54分39秒
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

signed main()
{
    freopen("B.in", "w", stdout);
    int n = 528443277143540353ll, k = 500000, q = 493;
    srand(time(0));
    printf("%lld %lld %lld\n", n, k, q);
    REP(i, 0, k) printf("%lld " ,rand()); puts("");
    return 0;
}
