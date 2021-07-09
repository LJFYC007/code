/***************************************************************
	File name: P1776.cpp
	Author: ljfcnyali
	Create time: 2019年06月26日 星期三 15时56分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

struct node
{
    int v, w;
} p;
vector<node> a;

int dp[maxn], n, m, cnt;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n)
    {
        int v, w, x; scanf("%d%d%d", &v, &w, &x);
        int y = 1;
        while ( y <= x ) 
        {
            p.v = v * y; p.w = w * y;
            a.push_back(p);
            x -= y; y *= 2;
        }
        if ( x != 0 ) { p.v = v * x; p.w = w * x; a.push_back(p); }
    }
    REP(i, 0, a.size() - 1)
        for ( int j = m; j >= a[i].w; -- j )
            dp[j] = max(dp[j], dp[j - a[i].w] + a[i].v);
    printf("%d\n", dp[m]);
    return 0;
}
