/***************************************************************
	File name: route.cpp
	Author: ljfcnyali
	Create time: 2019年07月16日 星期二 08时46分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( register LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;
const LL INF = 10000000000000;

LL n, m, s, t, ans;

struct node
{
    LL x, y, p, q;
    bool operator < (const node &a) const { return q < a.q; }
} a[maxn];

struct Node
{
    LL pos, val;
} p1, p2;

vector<Node> dp[maxn];

inline LL js(LL x, LL y) { LL t = y - x; return t * t; }

int main()
{
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) scanf("%lld%lld%lld%lld", &a[i].x, &a[i].y, &a[i].p, &a[i].q);
    sort(a + 1, a + m + 1);
    REP(i, 1, m) 
        if ( a[i].x == 1 ) 
        {
            bool flag = false;
            REP(j, 0, dp[a[i].y].size() - 1)
            {
                p1 = dp[a[i].y][j];
                if ( p1.pos == a[i].q ) 
                {
                    p1.val = min(p1.val, a[i].p * a[i].p);
                    dp[a[i].y][j] = p1;
                    flag = true;
                    break ;
                }
            }
            if ( flag == false ) 
            {
                p1.pos = a[i].q; p1.val = a[i].p * a[i].p;
                dp[a[i].y].push_back(p1);
            }
        }
    REP(i, 1, m)
    {
        if ( a[i].x == 1 ) continue ;
        bool flag = false;
        REP(j, 0, dp[a[i].y].size() - 1)
        {
            p1 = dp[a[i].y][j];
            cerr << a[i].y << endl;
            if ( p1.pos == a[i].q ) 
            {
                REP(k, 0, dp[a[i].x].size() - 1)
                {
                    p2 = dp[a[i].x][k];
                    if ( p2.pos > a[i].p ) continue ;
                    p1.val = min(p1.val, p2.val + js(p2.pos, a[i].p));
                }
                dp[a[i].y][j] = p1;
                flag = true; break ;
            }
        }
        if ( flag == false ) 
        {
            p1.pos = a[i].q; p1.val = INF;
            REP(k, 0, dp[a[i].x].size() - 1) 
            {
                p2 = dp[a[i].x][k];
                if ( p2.pos > a[i].p ) continue ;
                p1.val = min(p1.val, p2.val + js(p2.pos, a[i].p));
            }
            dp[a[i].y].push_back(p1);
        }
        // dp[a[i].y][a[i].q] = min(dp[a[i].y][a[i].q], dp[a[i].x][j] + js(j, a[i].p));
    }
    ans = INF;
    REP(i, 0, dp[n].size() - 1) ans = min(ans, dp[n][i].val);
    printf("%lld\n", ans);
    return 0;
}
