/***************************************************************
	File name: P2439.cpp
	Author: ljfcnyali
	Create time: 2019年06月24日 星期一 16时27分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 30010;

int n, dp[maxn];
vector<int> a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { int s, t; scanf("%d%d", &s, &t); a[s].push_back(t); }
    REP(i, 0, 30000)
    {
        if ( i > 0 ) dp[i] = max(dp[i], dp[i - 1]);
        REP(j, 0, a[i].size() - 1)
            dp[a[i][j]] = max(dp[a[i][j]], dp[i] + a[i][j] - i);
    }
    printf("%d\n", dp[30000]);
    return 0;
}
