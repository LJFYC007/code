/***************************************************************
	File name: P3811.cpp
	Author: ljfcnyali
	Create time: 2019年06月05日 星期三 10时44分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

LL n, p, inv[30000000];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &p);
    inv[1] = 1; printf("1\n");
    REP(i, 2, n)
    {
        inv[i] = (p - p / i) * inv[p % i] % p;
        printf("%lld\n", inv[i]);
    }
    return 0;
}
