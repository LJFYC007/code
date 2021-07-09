/***************************************************************
	File name: P2320.cpp
	Author: ljfcnyali
	Create time: 2019年08月20日 星期二 11时32分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1010;

LL a[maxn], sum, n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    while ( n ) { a[++ sum] = (n + 1) / 2; n /= 2; }
    sort(a + 1, a + sum + 1); printf("%lld\n", sum); REP(i, 1, sum) printf("%lld ", a[i]);
    return 0;
}
