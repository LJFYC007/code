/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2020年06月16日 星期二 16时50分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e18;

int n, d[maxn], a[maxn], ans;
priority_queue<int, vector<int>, greater<int> > Q1;
priority_queue<int> Q2;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 2, n) { scanf("%lld", &d[i]); d[i] += d[i - 1]; }
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n)
    {
        Q1.push(a[i] - d[i]);
        int x = Q1.top(); Q1.pop();
        ans += d[i] + x; Q2.push(2 * d[i] + x);
        if ( !Q2.empty() && a[i] + d[i] - Q2.top() < 0 ) 
        {
            x = Q2.top(); Q2.pop();
            ans += a[i] + d[i] - x;
            Q1.push(x - 2 * d[i]);
            Q2.push(a[i] + d[i]);
        }
        else Q1.push(a[i] - d[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
