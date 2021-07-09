/***************************************************************
	File name: square.cpp
	Author: ljfcnyali
	Create time: 2019年08月29日 星期四 08时19分08秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long 
typedef long long LL;

const int maxn = 200100;
const int INF = 1000000000000000000;

struct node
{
    int x, y;
    bool operator < (const node &a) const { return x < a.x; } 
} a[maxn];

inline bool cmp(node a, node b) { return a.y < b.y; } 

int n, ans;

struct Node
{
    int x;
    bool operator < (const Node &a) const { return x > a.x; }
} p1;
priority_queue<Node> Q;

signed main()
{
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n * 2) 
    { 
        scanf("%lld%lld", &a[i].x, &a[i].y); 
        if ( a[i].x > a[i].y ) swap(a[i].x, a[i].y); 
    }
    sort(a + 1, a + n + n + 1);
    sort(a + 2, a + n + n + 1, cmp);
    REP(i, n + 2, n + n) 
    {
        p1.x = a[i].x;
        Q.push(p1);
    }
    for ( int i = n + 1; i >= 3; -- i )
    {
        ans = max(ans, a[1].x * min(a[1].y, a[2].y) + min(a[i].x, Q.top().x) * a[i].y);
        if ( i == 3 ) 
        {
            ans = max(ans, a[1].x * min(a[1].y, a[3].y) + min(a[2].x, Q.top().x) * a[2].y);
        }
        if ( a[i].x > Q.top().x ) { Q.pop(); p1.x = a[i].x; Q.push(p1); }
    }
    printf("%lld\n", ans);
    return 0;
}
