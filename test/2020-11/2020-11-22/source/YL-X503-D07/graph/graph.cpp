/***************************************************************
	File name: graph.cpp
	Author: ljfcnyali
	Create time: 2020年11月22日 星期日 10时37分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 510;

int n, m, ans[maxn][maxn], t[maxn][maxn];
pii Edge[maxn * maxn];
bool vis[maxn];

inline void Insert(int x)
{
    if ( vis[x] ) return ; vis[x] = true;
    REP(j, 1, n) if ( !vis[j] ) { ans[j][x] = t[j][x] ^ 1; ans[x][j] = t[j][x]; }
}

int main()
{
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, m) scanf("%d%d", &Edge[i].first, &Edge[i].second);
    REP(i, 1, n)
    {
        mem(vis); mem(ans); mem(t); Insert(i);
        REP(j, 1, m)
        {
            if ( vis[Edge[j].first] == vis[Edge[j].second] ) 
            {
                int x = Edge[j].first, y = Edge[j].second;
                t[x][y] ^= 1; t[y][x] ^= 1;
                continue ;
            }
            Insert(Edge[j].first); Insert(Edge[j].second);
        }
        bool flag = false;
        REP(j, 1, n) if ( !vis[j] ) flag = true;
        if ( !flag ) continue ;
        
        REP(i, 1, n - 1) { REP(j, i + 1, n) printf("%d ", ans[i][j]); puts(""); }
        return 0;
    }
    return 0;
}
