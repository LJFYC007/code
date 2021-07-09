/***************************************************************
	File name: P2120.cpp
	Author: ljfcnyali
	Create time: 2019年07月31日 星期三 09时19分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 10000010;

LL dp[maxn], n, X[maxn], P[maxn], C[maxn], sum1[maxn], sum2[maxn], Q[maxn], head, tail;

inline double x(int i) { return sum1[i]; }

inline double y(int i) { return dp[i] + sum2[i]; }

inline double slope(int i, int j) { return (y(i) - y(j)) / (x(i) - x(j)); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld%lld%lld", &X[i], &P[i], &C[i]);
    REP(i, 1, n) { sum1[i] = sum1[i - 1] + P[i]; sum2[i] = sum2[i - 1] + X[i] * P[i]; }
    head = tail = 1; 
    REP(i, 1, n)
    {
        while ( head < tail && slope(Q[head], Q[head + 1]) < X[i] ) ++ head; 
        dp[i] = dp[Q[head]] + X[i] * (sum1[i - 1] - sum1[Q[head]]) - (sum2[i - 1] - sum2[Q[head]]) + C[i];
        while ( head < tail && slope(Q[tail - 1], Q[tail]) > slope(Q[tail - 1], i) ) -- tail;
        Q[++ tail] = i;
    }
    printf("%lld\n", dp[n]);
    return 0;
}
