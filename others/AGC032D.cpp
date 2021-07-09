/***************************************************************
	File name: AGC032D.cpp
	Author: ljfcnyali
	Create time: 2021年01月18日 星期一 15时53分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;
const int INF = 1e18;

int n, A, B, a[maxn], f[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &A, &B); REP(i, 1, n) scanf("%lld", &a[i]); 
    a[n + 1] = n + 1;
    REP(i, 1, n + 1)
    {
        int sum1 = 0, sum2 = 0; f[i] = INF;
        for ( int j = i - 1; j >= 0; -- j )
        {
            if ( a[j] < a[i] ) f[i] = min(f[i], f[j] + sum1 * A + sum2 * B);
            if ( a[j] < a[i] ) ++ sum2; else ++ sum1; 
        }
    }
    printf("%lld\n", f[n + 1]);
    return 0;
}
