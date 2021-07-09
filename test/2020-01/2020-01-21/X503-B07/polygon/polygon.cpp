/***************************************************************
	File name: polygon.cpp
	Author: ljfcnyali
	Create time: 2020年01月21日 星期二 10时07分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int Mod = 1e9 + 7;

signed main()
{
    freopen("polygon.in", "r", stdin);
    freopen("polygon.out", "w", stdout);
    int n; scanf("%lld", &n);
    if ( n <= 2 ) { puts("0"); return 0; }
    int ret = 1;
    REP(i, 1, n) ret = ret * 2 % Mod;
    ret -= (n * (n - 1) / 2) % Mod; 
    ret -= n + 1;
    ret = (ret % Mod + Mod) % Mod;
    printf("%lld\n", ret);
    return 0;
}
