/***************************************************************
	File name: sow.cpp
	Author: ljfcnyali
	Create time: 2019年08月11日 星期日 08时25分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 10010;

LL dp[maxn], w[maxn], n, m, sum[maxn], ans, head, tail, Q[maxn];
LL f[maxn];
vector<LL> p[maxn];

inline double X(LL x) { return 2 * dp[x] + x * x - x + 2 * sum[x]; }

inline double Y(LL x) { return x; }

inline double slope(LL i, LL j) { return (X(i) - X(j)) / (Y(i) - Y(j)); }

inline LL js(LL l, LL r) { return (r - l + 1) * (r - l) / 2; }

namespace Subtask
{
#define maxm 100010
    LL W[maxm], Sum;

    inline void Solve()
    {
        REP(i, 1, n) { scanf("%lld", &W[i]); Sum += W[i]; }
        LL x; scanf("%lld", &x);
        LL Ans = n * (n + 1) / 2;
        REP(i, 1, x)
        {
            LL u, val; scanf("%lld%lld", &u, &val);
            printf("%lld\n", Ans - (Sum - W[u] + val));
        }
    }
}

int main()
{
    freopen("sow.in", "r", stdin);
    freopen("sow.out", "w", stdout);
    scanf("%lld", &n);
    if ( n >= 10000 ) { Subtask :: Solve(); return 0; }
    REP(i, 1, n) scanf("%lld", &w[i]);
    REP(i, 1, n) sum[i] = sum[i - 1] + w[i];
    scanf("%lld", &m);
    head = tail = 1;
    REP(i, 1, n)
    {
        REP(j, head, tail) p[i].push_back(Q[j]);
        while ( head < tail && slope(Q[head], Q[head + 1]) > 2 * i ) ++ head;
        dp[i] = dp[Q[head]] + js(Q[head], i) - sum[i] + sum[Q[head]];
        while ( head < tail && slope(Q[tail - 1], Q[tail]) < slope(Q[tail - 1], i) ) -- tail;
        Q[++ tail] = i;
    }
    REP(i, 1, n) f[i] = dp[i];
    REP(k, 1, m)
    {
        LL x, y, val; scanf("%lld%lld", &x, &y); 
        val = w[x]; w[x] = y; 
        REP(i, x, n) sum[i] += y - val;
        head = 1; tail = 0;
        REP(i, 0, p[x].size() - 1) Q[++ tail] = p[x][i];
        REP(i, x, n)
        {
            while ( head < tail && slope(Q[head], Q[head + 1]) > 2 * i ) ++ head;
            dp[i] = dp[Q[head]] + js(Q[head], i) - sum[i] + sum[Q[head]];
            while ( head < tail && slope(Q[tail - 1], Q[tail]) < slope(Q[tail - 1], i) ) -- tail;
            Q[++ tail] = i;
        }
        ans = 0; REP(i, 1, n) ans = max(ans, dp[i]);
        printf("%lld\n", ans);
        REP(i, x, n) dp[i] = f[i];
        REP(i, x, n) sum[i] -= y - val;
        w[x] = val;
    }
    return 0;
}
