/***************************************************************
	File name: P5470.cpp
	Author: ljfcnyali
	Create time: 2019年07月19日 星期五 09时38分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 200010;
const int INF = 1000000000000000;

int T, n, k, l, a[maxn], b[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- )
    {
        scanf("%lld%lld%lld", &n, &k, &l);
        REP(i, 1, n) scanf("%lld", &a[i]);
        REP(i, 1, n) scanf("%lld", &b[i]);
    }
    return 0;
}
