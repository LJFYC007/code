/***************************************************************
	File name: home.cpp
	Author: ljfcnyali
	Create time: 2019年08月04日 星期日 10时32分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int n, m, k, p[20], ans, sum[10000][20];
bool a[20][20], vis[20];

inline bool pd()
{
    REP(i, 1, ans)
    {
        REP(j, 0, n - 1)
        {
            bool flag = false;
            REP(k, 1, n) if ( sum[i][(k + j - 1) % n + 1] != p[k] ) { flag = true; break ; }
            if ( flag == false ) return true;
        }
    }
    return false;
}

inline void DFS(int x)
{
    if ( x == n + 1 )
    {
        if ( a[p[n]][p[1]] ) return ;
        if ( abs(p[n] - p[1]) > k ) return ;
        if ( pd() ) return ;
        ++ ans;
        REP(i, 1, n) sum[ans][i] = p[i];
        return ;
    }
    REP(i, 1, n)
    {
        if ( vis[i] || abs(i - p[x - 1]) > k || a[p[x - 1]][i] ) continue ;
        vis[i] = true; p[x] = i; DFS(x + 1); vis[i] = false;
    }
}

int main()
{
    freopen("home.in", "r", stdin);
    freopen("home.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    if ( k == 0 ) { if ( n == 1 ) puts("1"); else puts("0"); return 0; }
    if ( n == 1 ) { puts("1"); return 0; }
    if ( k == 1 ) { puts("0"); return 0; }
    REP(i, 1, m) { int x, y; scanf("%d%d", &x, &y); a[x][y] = 1; }
    REP(i, 1, n) { p[1] = i; mem(vis); vis[i] = true; DFS(2); }
    printf("%d\n", ans);
    return 0;
}
