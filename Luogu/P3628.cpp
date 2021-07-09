/***************************************************************
	File name: P3628.cpp
	Author: ljfcnyali
	Create time: 2019年08月06日 星期二 19时16分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

LL n, a, b, c, x[maxn], sum[maxn], dp[maxn];
LL Q[maxn], head, tail;

inline double X(LL i) { return sum[i]; }

inline double Y(LL i) { return a * sum[i] * sum[i] - b * sum[i] + dp[i]; }

inline double slope(LL i, LL j) { return (Y(i) - Y(j)) / (X(i) - X(j)); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld%lld", &n, &a, &b, &c);
    REP(i, 1, n) { scanf("%lld", &x[i]); sum[i] = sum[i - 1] + x[i]; }
    head = tail = 1;    
    REP(i, 1, n)
    {
        while ( head < tail && slope(Q[head], Q[head + 1]) > 2 * a * sum[i] ) ++ head;
        dp[i] = dp[Q[head]] + a * (sum[i] - sum[Q[head]]) * (sum[i] - sum[Q[head]]) + b * (sum[i] - sum[Q[head]]) + c;
        while ( head < tail && slope(Q[tail - 1], Q[tail]) < slope(Q[tail - 1], i) ) -- tail;
        Q[++ tail] = i; 
    }
    printf("%lld\n", dp[n]);
    return 0;
}
