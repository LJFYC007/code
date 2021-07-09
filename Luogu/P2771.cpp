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

const int maxn = 2010;

int n, x, y, ans;
bool vis[maxn][maxn], p[maxn][maxn][4];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d\n", &n);
    x = y = 1000; 
    vis[x][y] = true;
    REP(i, 1, n)
    {
        char c = getchar();
        int t = 0;
        if ( c == 'N' ) t = 0;
        if ( c == 'S' ) t = 2;
        if ( c == 'W' ) t = 1;
        if ( c == 'E' ) t = 3;
        p[x][y][t] = true;
        if ( c == 'N' ) ++ x;
        if ( c == 'S' ) -- x;
        if ( c == 'W' ) -- y;
        if ( c == 'E' ) ++ y;
        if ( vis[x][y] && !p[x][y][t >= 2 ? t - 2 : t + 2] ) ++ ans;
        vis[x][y] = true;
        p[x][y][t >= 2 ? t - 2 : t + 2] = true;
    }
    printf("%d\n", ans);
    return 0;
}
