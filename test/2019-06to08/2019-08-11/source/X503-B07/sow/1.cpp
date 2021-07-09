/***************************************************************
	File name: sow.cpp
	Author: ljfcnyali
	Create time: 2019年08月11日 星期日 08时25分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 5010;

int dp[maxn], w[maxn], n, m, sum[maxn], ans;

inline int js(int l, int r)
{
    return (2 + r - l) * (r - l + 1) / 2;
}

int main()
{
    freopen("sow1.in", "r", stdin);
    freopen("sow1.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &w[i]);
    REP(i, 1, n) sum[i] = sum[i - 1] + w[i];
    scanf("%d", &m);
    REP(k, 1, m)
    {
        int x, y, val; scanf("%d%d", &x, &y); 
        val = w[x]; w[x] = y; 
        REP(i, x, n) sum[i] += y - val;
        REP(i, 1, n)
        {
            dp[i] = 0;
            REP(j, 0, i - 1)
            {
                // printf("%d ", dp[j] + js(j + 1, i) - sum[i] + sum[j]);
                dp[i] = max(dp[i], dp[j] + js(j + 1, i) - (sum[i] - sum[j]));
            }
            // puts("");
        }
        ans = 0; REP(i, 1, n) ans = max(ans, dp[i]);
        // REP(i, 1, n) printf("%d ", dp[i]);
        printf("%d\n", ans);
        REP(i, x, n) sum[i] -= y - val;
        w[x] = val;
    }
    return 0;
}
