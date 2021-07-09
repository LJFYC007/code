/***************************************************************
	File name: P1757.cpp
	Author: ljfcnyali
	Create time: 2019年06月25日 星期二 18时38分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int n, m, dp[maxn], k, sum[maxn], now, ans;
struct node
{
    int a, b, c;
} a[maxn];

inline int cmp(node a, node b)
{
    return a.c < b.c;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &m, &n);
    REP(i, 1, n) 
    { 
        scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].c); 
        k = max(k, a[i].c); 
        ++ sum[a[i].c]; 
    }
    sort(a + 1, a + n + 1, cmp);
    int x = 0;
    REP(i, 1, k)
    {
        for ( int j = m; j >= 0; -- j )
        {
            now = x;
            REP(o, 1, sum[i])
            {
                ++ now;
                if ( j < a[now].a ) continue ;
                dp[j] = max(dp[j], dp[j - a[now].a] + a[now].b);
            }
        }
        x += sum[i];
    }
    printf("%d\n", dp[m]); return 0;
    REP(i, 0, m) ans = max(ans, dp[i]);
    printf("%d\n", ans);
    return 0;
}
