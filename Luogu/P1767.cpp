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

int a[maxn][maxn], n, ans, dt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool vis[maxn][maxn];

inline void DFS(int x, int y)
{
    REP(i, 0, 3)
    {
        int u = x + dt[i][0], v = y + dt[i][1];
        if ( vis[u][v] || a[u][v] ) continue ;
        vis[u][v] = true;
        DFS(u, v);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    memset ( a, 1, sizeof ( a ) );
    string s;
    getline(cin, s);
    REP(i, 1, n)
    {
        getline(cin, s);
        a[i][0] = s.size();
        REP(j, 0, a[i][0] - 1)
        {
            if ( s[j] >= 'a' && s[j] <= 'z' ) a[i][j + 1] = 0;
        }
    }
    REP(i, 1, n) REP(j, 1, a[i][0]) if ( !vis[i][j] && !a[i][j] ) { vis[i][j] = true; DFS(i, j); ++ ans; }
    printf("%d\n", ans);
    return 0;
}
