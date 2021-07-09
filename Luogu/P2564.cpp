/***************************************************************
	File name: P2564.cpp
	Author: ljfcnyali
	Create time: 2019年07月01日 星期一 12时25分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

struct node
{
    int x, pos;
} a[maxn];
queue<int> Q;

int n, m, tot, cnt, ans = 0x3f3f3f3f, sum[maxn];

inline int cmp(node a, node b) { return a.pos < b.pos || (a.pos == b.pos && a.x < b.x); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m)
    {
        int x; scanf("%d", &x);
        REP(j, 1, x) { scanf("%d", &a[++ tot].pos); a[tot].x = i; }
    }
    sort(a + 1, a + n + 1, cmp);
//    REP(i, 1, n) printf("%d %d\n", a[i].x, a[i].pos);
    int l = a[1].pos, r = a[1].pos;
    REP(i, 1, n)
    {
        while ( cnt < m && i <= n ) 
        {
            ++ sum[a[i].x];
            if ( sum[a[i].x] == 1 ) ++ cnt;
            r = a[i].pos; 
            Q.push(i);
            ++ i;
        }
//        printf("%d %d %d\n", l, r, i - 1);
        ans = min(ans, r - l);
        while ( cnt == m ) 
        {
            int x = Q.front(); Q.pop();
            -- sum[a[x].x]; if ( !sum[a[x].x] ) -- cnt;
            l = a[x].pos; ans = min(ans, r - l);
        }
        l = a[Q.front()].pos;
        -- i;
    }
    printf("%d\n", ans);
    return 0;
}
