/***************************************************************
	File name: permutation.cpp
	Author: ljfcnyali
	Create time: 2020年07月08日 星期三 08时46分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5;
const int Mod = 1e9 + 7;

signed main()
{
    freopen("permutation.in", "r", stdin);
    freopen("permutation.out", "w", stdout);
    int now = 1;
    REP(i, 1, 1000000000)
    {
        now = now * i % Mod;
        if ( i % maxn == 0 ) printf("%lld,", now);
    }
    return 0;
}
