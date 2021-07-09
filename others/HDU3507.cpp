
/***************************************************************
    File name: 3507.cpp
    Author: ljfcnyali
    Create time: 2019年06月26日 星期三 20时42分29秒
***************************************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#include<stack>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 550010;

int dp[maxn], n, m, sum[maxn], q[maxn], s, t;

inline int js1(int j, int k)
{
    return dp[j] + sum[j] * sum[j] - dp[k] - sum[k] * sum[k];
}

inline int js2(int j, int k)
{
    return 2 * (sum[j] - sum[k]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%d%d", &n, &m) )
    {
        memset(dp, 0x3f, sizeof(dp)); mem(q);
        REP(i, 1, n) { int x; scanf("%d", &x); sum[i] = sum[i - 1] + x; }
        dp[0] = 0;
        s = t = 0; q[t ++] = 0;
        REP(i, 1, n)
        {
            while ( s + 1 < t && js1(q[s + 1], q[s]) <= sum[i] * js2(q[s + 1], q[s]) ) ++ s;
            dp[i] = dp[q[s]] + (sum[q[s]] - sum[i]) * (sum[q[s]] - sum[i]) + m;
            while ( s + 1 < t && js1(i, q[t - 1]) * js2(q[t - 1], q[t - 2]) <= js1(q[t - 1], q[t - 2]) * js2(i, q[t - 1]) ) -- t;
            q[t ++] = i;
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}
