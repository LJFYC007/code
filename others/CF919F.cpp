/***************************************************************
	File name: CF919F.cpp
	Author: ljfcnyali
	Create time: 2020年10月21日 星期三 19时22分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 510;

int T, n, m, deg[maxn][maxn], vis[maxn][maxn];
vector<int> g[maxn], a;
vector<pii> Edge[maxn][maxn], Pre[maxn][maxn];
queue<pii> Q;
map<vector<int>, int> Map;

inline void DFS(int x, int lst)
{
    if ( x == 8 ) { g[++ m] = a; Map[a] = m; return ; }
    REP(i, lst, 4)
    {
        a.push_back(i);
        DFS(x + 1, i);
        a.pop_back();
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    DFS(0, 0); memset(vis, -1, sizeof(vis));
    REP(i, 2, m) { vis[i][1] = 0; vis[1][i] = 1; }
    REP(i, 1, m) REP(j, 1, m)
        REP(x, 0, 7) REP(y, 0, 7)
        {
            if ( !g[i][x] || !g[j][y] ) continue ;
            a = g[i]; a[x] = (g[i][x] + g[j][y]) % 5; 
            sort(a.begin(), a.end());
            const int x = Map[a];
            Edge[i][j].push_back(pii(j, x)); ++ deg[i][j];
            Pre[j][x].push_back(pii(i, j));
        }
    REP(i, 1, m) REP(j, 1, m) if ( !deg[i][j] ) Q.push(pii(i, j)); 
    while ( !Q.empty() ) 
    {
        pii u = Q.front(); Q.pop();
        if ( vis[u.x][u.y] == -1 ) 
            vis[u.x][u.y] = 0;
        for ( auto it : Pre[u.x][u.y] )
        {
            if ( deg[it.x][it.y] < 0 ) continue ;
            -- deg[it.x][it.y];
            if ( vis[u.x][u.y] == 0 ) { vis[it.x][it.y] = 1; Q.push(it); deg[it.x][it.y] = -1; }
            if ( !deg[it.x][it.y] ) Q.push(it);
        }
    }
    scanf("%d", &T);
    while ( T -- ) 
    {
        int x, numx, numy; scanf("%d", &x);
        a.clear(); REP(i, 1, 8) { int y; scanf("%d", &y); a.push_back(y); } sort(a.begin(), a.end()); numx = Map[a];
        a.clear(); REP(i, 1, 8) { int y; scanf("%d", &y); a.push_back(y); } sort(a.begin(), a.end()); numy = Map[a];
        // cout << numx << " " << numy << endl;
        int flag;
        if ( x == 0 ) flag = vis[numx][numy];
        else flag = vis[numy][numx];
        if ( flag == -1 ) puts("Deal");
        else if ( (flag == 1 && x == 0) || (flag == 0 && x == 1) ) puts("Alice");
        else puts("Bob");
    }
    return 0;
}
