/***************************************************************
	File name: 1.cpp
	Author: ljfcnyali
	Create time: 2020年10月08日 星期四 16时12分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int main()
{
    freopen("reverse.out", "w", stdout);
    LL sum = 1;
    REP(i, 1, 400000000) 
    {
        sum = sum * (2 * i + 1) % Mod;
        if ( i % 1000000 == 0 ) printf("%lld,", sum);
    }
    return 0;
}
