/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年12月26日 星期六 09时27分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, ans;
struct node { int u, v, w; } a[maxn];
vector<int> Edge[maxn];
bool vis[maxn];

inline void DFS1(int u)
{
    if ( vis[u] ) return ; vis[u] = true;
    for ( auto v : Edge[u] ) DFS1(v);
}

inline bool Check()
{
    mem(vis); DFS1(1);
    REP(i, 1, n) if ( !vis[i] ) return false;
    return true;
}

inline void DFS(int x, int sum, int val)
{
    if ( x == m + 1 ) 
    {
        // if ( sum != n - 1 || val == 0 ) return ;
        if ( sum != n - 1 ) return ;
        if ( Check() ) ++ ans;
        return ;
    }
    DFS(x + 1, sum, val);
    Edge[a[x].u].push_back(a[x].v);
    Edge[a[x].v].push_back(a[x].u);
    DFS(x + 1, sum + 1, val ^ (a[x].w % 2));
    Edge[a[x].u].pop_back();
    Edge[a[x].v].pop_back();
}

int main()
{
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, m) scanf("%d%d%d", &a[i].u, &a[i].v, &a[i].w);
    DFS(1, 0, 0);
    printf("%d\n", ans);
    return 0;
}
