/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2019年09月21日 星期六 14时53分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 200010;

int n, a[maxn], y, z;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%I64d", &n);
    REP(i, 1, n) scanf("%I64d", &a[i]);
    sort(a + 1, a + n + 1);
    for ( int i = n - 1; i >= 1; -- i )
        z = __gcd(z, (a[n] - a[i]));
    REP(i, 1, n) y += (a[n] - a[i]) / z;
    printf("%I64d %I64d\n", y ,z);
    return 0;
}
