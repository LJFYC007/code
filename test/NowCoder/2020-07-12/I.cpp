/***************************************************************
	File name: I.cpp
	Author: ljfcnyali
	Create time: 2020年07月12日 星期日 12时59分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 210;

int n, m, d[maxn], Begin[maxn], Next[maxn], To[maxn], e, match[maxn][2], Pos;
bool vis[maxn];
pii Edge[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int DFS(int u, int now, bool flag)
{
    if ( vis[u] ) return 0; vis[u] = true;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( vis[v] ) continue ;
        REP(j, 0, 1)
        {
            if ( j == 1 && d[v] == 1 ) continue ;
            if ( match[v][j ^ 1] == u ) continue ;
            if ( !match[v][j] || DFS(match[v][j], match[match[v][j]][1] == v, 0) )
            {
                match[u][now] = v; match[v][j] = u;
                ++ now; 
                if ( !flag ) return 1;
                if ( now < d[u] ) break ; 
                else return 1;
            }
        }
    }
    return 0;
}

inline bool Solve()
{
    random_shuffle(Edge + 1, Edge + m + 1);
    e = 0; REP(i, 1, n) Begin[i] = match[i][0] = match[i][1] = 0;
    REP(i, 1, m) { add(Edge[i].first, Edge[i].second); add(Edge[i].second, Edge[i].first); }
    REP(i, 1, n)
    {
        REP(j, 1, n) vis[j] = false;
        // REP(j, 1, n) printf("%d %d\n", match[j][0], match[j][1]);
        // puts("");
        if ( d[i] == 1 && match[i][0] ) continue ;
        if ( d[i] == 2 && match[i][1] ) continue ;
        int x = match[i][0] ? DFS(i, 1, 1) : DFS(i, 0, 1);
        if ( !x ) return false;
    }
    // REP(j, 1, n) printf("%d %d\n", match[j][0], match[j][1]);
    // puts("HAHA");
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    srand(211212);
    // srand(time(0));
    while ( ~scanf("%d%d", &n, &m) )
    {
        REP(i, 1, n) scanf("%d", &d[i]);
        REP(i, 1, m) scanf("%d%d", &Edge[i].first, &Edge[i].second);
        REP(i, 1, 100) if ( Solve() ) { puts("Yes"); goto Finish; }
        puts("No");
Finish : ;
    }
    return 0;
}
