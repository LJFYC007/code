/***************************************************************
	File name: pair.cpp
	Author: ljfcnyali
	Create time: 2019年09月17日 星期二 20时00分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 20;
const int Mod = 998244353;

int num[maxn], T, l, r;

inline int Solve(int x)
{
    mem(num);
    int sum = 0;
    while ( x > 0 )
    {
        REP(i, 0, (x % 10) - 1) sum += num[i];
        ++ num[x % 10]; x /= 10;
    }
    return sum;
}

signed main()
{
    freopen("pair.in", "r", stdin);
    freopen("pair.out", "w", stdout);
    int ans = 0;
    REP(i, 1, 1000000000)
    {
        ans = (Solve(i) + ans) % Mod;
        if ( i % 5000000 == 0 ) printf("%lld,", ans), cerr << i / 5000000 << endl;
    }
    return 0;
}
