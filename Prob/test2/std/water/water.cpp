/***************************************************************
	File name: water.cpp
	Author: ljfcnyali
	Create time: 2019年07月31日 星期三 09时19分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 2000010;

LL dp[maxn], n, X[maxn], P[maxn], C[maxn], sum1[maxn], sum2[maxn], Q[maxn], head, tail;

inline double x(int i) { return sum1[i]; }

inline double y(int i) { return dp[i] + sum2[i]; }

inline double slope(int i, int j) { return (y(i) - y(j)) / (x(i) - x(j)); }

inline void read(LL &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
    freopen("water.in", "r", stdin);
    freopen("water.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) read(X[i]), read(P[i]), read(C[i]);
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
