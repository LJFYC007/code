/***************************************************************
	File name: P4823.cpp
	Author: ljfcnyali
	Create time: 2019年08月31日 星期六 09时18分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 2010;

int dp[maxn], n, k;

struct node
{
    int a, b;
    bool operator < (const node &x) const { return a + b < x.a + x.b; }
} a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d%d", &a[i].a, &a[i].b);
    scanf("%d", &k);
    sort(a + 1, a + n + 1);
    REP(i, 1, n) dp[0] += a[i].a, dp[i] = -0x3f3f3f3f;
    REP(i, 1, n) for ( int j = i; j >= 1; -- j ) if ( dp[j - 1] + a[i].b >= k ) dp[j] = max(dp[j], dp[j - 1] - a[i].a);
    for ( int i = n; i >= 0; -- i ) if ( dp[i] >= 0 ) { printf("%d\n", i); return 0; }
    return 0;
}
