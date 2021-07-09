#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 1010;

int a[maxn][maxn], n, m, ans, L, R, cnt;
int dt[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
bool flag, vis[maxn][maxn];

inline void DFS(int x, int y, int Max)
{
    // printf("%d %d %d\n", x, y, Max);
    ++ cnt; if ( cnt > 100000 ) return ;
    if ( x <= 0 || y <= 0 || x > n || y > m ) return ;
    if ( flag == true ) return ;
    if ( x == n ) { flag = true; return ; }
    REP(i, 0, 3)
    {
        int u = x + dt[i][0], v = y + dt[i][1];
        if ( a[u][v] > Max || vis[u][v] ) continue ;
        vis[u][v] = true;
        DFS(u, v, Max);
    }
}

inline bool solve(int Max)
{
    flag = false; cnt = 0;
    mem(vis); vis[1][1] = true;
    DFS(1, 1, Max);
    if ( flag == true ) return true;
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) REP(j, 1, m) { scanf("%d", &a[i][j]); R = max(R, a[i][j]); }
    // printf("%d\n", solve(2));
    // return 0;
    L = 0;
    while ( L <= R ) 
    {
        int Mid = (L + R) / 2;
        if ( solve(Mid) ) 
        {
            ans = Mid; R = Mid - 1;
        }
        else L = Mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}
