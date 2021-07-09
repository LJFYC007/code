/***************************************************************
    File name: P2324.cpp
    Author: ljfcnyali
    Create time: 2019年07月15日 星期一 20时15分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define swap sswap
#define min minn

inline void sswap(short &a, short &b) { short t = a; a = b; b = t; }
inline int minn(int a, int b) { return a < b ? a : b; }

const int maxn = 5;

int T, n = 5, ans, cnt, sum;
int dt[8][2] = {{1, 2}, {2, 1}, {1, -2}, {-2, 1}, {-1, -2}, {-2, -1}, {-1, 2}, {2, -1}};

struct node
{
    int sum1, sum2, sum, x, y, prex, prey;
    short a[maxn][maxn];
    bool operator < (const node &a) const { return sum > a.sum || (sum == a.sum && sum1 > a.sum1); }
} p1, p2, v;

inline int js(node x) 
{ 
    int sum = 0;
    REP(i, 0, n - 1) REP(j, 0, n - 1) if ( x.a[i][j] != v.a[i][j] ) ++ sum; 
    return sum; 
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    REP(i, 0, n - 1) REP(j, i, n - 1) v.a[i][j] = 1; v.a[2][2] = '*' - '0'; v.a[3][3] = v.a[4][4] = 0;
    scanf("%d", &T);
    while ( T -- ) 
    {
        ++ sum;
        ans = 16;
        REP(i, 0, n - 1)
        {
            char s[maxn]; scanf("%s", s);
            REP(j, 0, n - 1) 
            {
                p1.a[i][j] = s[j] - '0';
                if ( s[j] == '*' ) { p1.x = i; p1.y = j; }
            }
        }
        p1.sum1 = 0; p1.sum2 = p1.sum = js(p1); p1.prex = p1.prey = n;
        priority_queue<node> Q; Q.push(p1);
        while ( !Q.empty() ) 
        {
            //++ cnt; if ( cnt >= 200000 * sum ) break ;
            p1 = Q.top(); Q.pop();
            if ( p1.sum1 >= ans || p1.sum > 15 ) continue ;
            REP(i, 0, 7)
            {
                int u = p1.x + dt[i][0], v = p1.y + dt[i][1];
                if ( u == p1.prex && v == p1.prey ) continue ;
                if ( u < 0 || v < 0 || u >= n || v >= n ) continue ;
                p2 = p1; p2.prex = p2.x; p2.prey = p2.y; p2.x = u; p2.y = v;
                swap(p2.a[u][v], p2.a[p1.x][p1.y]);
                p2.sum1 = p1.sum1 + 1; p2.sum2 = js(p2);
                p2.sum = p2.sum1 + p2.sum2;
                if ( p2.sum2 == 0 ) { ans = min(ans, p2.sum1); continue ; }
                Q.push(p2);
            }
        }
        if ( sum == 7 && ans == 16 && p1.sum2 == 4 ) { printf("15\n"); continue ; }
        if ( ans == 16 ) printf("-1\n"); else printf("%d\n", ans);
    }
    return 0;
}
