#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>

const int maxn = 110;

int n = 100, b[maxn][maxn], c[maxn][maxn], a[maxn][maxn];
bool vis[maxn];

inline void DFS(int u)
{
    vis[u] = true;
    REP(i, 1, n) if ( a[u][i] && !vis[i] ) DFS(i);
}

int main()
{
    freopen("tree.in", "w", stdout);
    srand(time(0));
    REP(i, 2, n) 
    {
        int x = i, y = rand() % (i - 1) + 1;
        a[x][y] = a[y][x] = b[x][y] = b[y][x] = true;
        x = i; y = rand() % (i - 1) + 1;
        a[x][y] = a[y][x] = c[x][y] = c[y][x] = true;
    }
    while ( 1 ) 
    {
        bool flag = false;
        REP(i, 1, n)
        {
            memset(vis, 0, sizeof(vis));
            vis[i] = true; DFS(i == 1 ? 2 : 1);
            REP(j, 1, n) if ( !vis[j] ) 
            {
                flag = true;
                vector<int> p; REP(k, 1, n) if ( vis[k] && k != i ) p.push_back(k);
                vector<int> q; REP(k, 1, n) if ( !vis[k] ) q.push_back(k);
                int x = p[rand() % p.size()], y = q[rand() % q.size()];
                a[x][y] = a[y][x] = true;
                break ; 
            }
        }
        if ( !flag ) break ; 
    }
    //REP(i, 1, n) REP(j, i + 1, n) if ( rand() % 5 == 1 ) a[i][j] = a[j][i] = true;
    int m = 0;
    REP(i, 1, n) REP(j, i + 1, n) if ( a[i][j] ) ++ m;
    printf("%d %d\n", n, m);
    REP(i, 1, n) REP(j, i + 1, n) if ( a[i][j] ) printf("%d %d %d %d\n", i, j, b[i][j], c[i][j]);
    return 0;
}