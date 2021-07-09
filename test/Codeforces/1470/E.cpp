/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2021年01月06日 星期三 11时34分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3e5 + 10;
const int INF = 1e18;

int T, n, c, q, a[maxn], f[maxn][5], g[maxn][5][5], h[maxn][5][5], dp[maxn][5], C[maxn][5];
vector<pii> Ans;

inline int Find(int pos, int now, int y)
{
    int l = pos, r = n, ans = n + 1;
    while ( l <= r ) 
    {
        int Mid = l + r >> 1;
        if ( y <= dp[Mid][now] - dp[pos - 1][now] || y > dp[Mid][now] - dp[pos - 1][now] + h[Mid][now][0] )
        {
            ans = Mid; r = Mid - 1;
        }
        else l = Mid + 1;
    }
    return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &T); n = maxn - 10; 
    C[0][0] = 1; REP(i, 1, n) { C[i][0] = 1; REP(j, 1, 4) C[i][j] = C[i - 1][j - 1] + C[i - 1][j]; }
    REP(i, 1, n) REP(j, 0, 4) REP(k, 0, j) f[i][j] += C[i - 1][k]; REP(i, 0, 4) f[0][i] = 1;
    while ( T -- ) 
    {
        scanf("%lld%lld%lld", &n, &c, &q);
        REP(i, 1, n) scanf("%lld", &a[i]);

        REP(i, 1, n) REP(now, 0, c)
        {
            vector<pii> p; p.clear(); REP(j, i, min(n, i + now)) p.push_back(pii(a[j], j));
            sort(p.begin(), p.end()); int sum = 0, k = 0;
            for ( auto it : p ) 
            {
                int j = it.second; g[i][now][k ++] = j; h[i][now][j - i] = f[n - j][now - j + i];
                if ( j > i ) sum += f[n - j][now - j + i];
                else dp[i][now] = dp[i - 1][now] + sum;
            }
        }

        while ( q -- ) 
        {
            int x, y, now = c; scanf("%lld%lld", &x, &y);
            if ( y > f[n][c] ) { puts("-1"); continue ; } 
            int pos = 1, nxt; Ans.clear();
            while ( pos <= n ) 
            {
                nxt = Find(pos, now, y); if ( nxt == n + 1 ) break ; 
                y -= dp[nxt - 1][now] - dp[pos - 1][now];
                REP(i, 0, c)
                {
                    int t = g[nxt][now][i];
                    if ( y <= h[nxt][now][t - nxt] )
                    {
                        Ans.push_back(pii(nxt, t));
                        now -= t - nxt; pos = t + 1; break ; 
                    }
                    y -= h[nxt][now][t - nxt];
                }
            }
            for ( auto it : Ans ) if ( it.first <= x && x <= it.second ) 
            {
                printf("%lld\n", a[it.second - x + it.first]);
                goto Finish;
            }
            printf("%lld\n", a[x]);
Finish : ;
        }
    }
    return 0;
}
