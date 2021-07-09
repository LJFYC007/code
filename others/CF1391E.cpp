/***************************************************************
	File name: CF1391E.cpp
	Author: ljfcnyali
	Create time: 2020年08月11日 星期二 17时01分29秒
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

const int maxn = 2e6 + 10;

int T, n, m, Begin[maxn], Next[maxn], To[maxn], e;
vector<int> a[maxn];
vector<pii> ans;
bool vis[maxn], flag;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int dep)
{
    if ( vis[u] || flag ) return ; vis[u] = true;
    a[dep].push_back(u);
    if ( dep >= (n + 1) / 2 ) 
    {
        puts("PATH"); printf("%d\n", dep);
        REP(i, 1, dep) printf("%d ", a[i].back()); puts("");
        flag = true;
        return ;
    }
    for ( int i = Begin[u]; i; i = Next[i] ) 
        DFS(To[i], dep + 1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m);
        e = 0; REP(i, 1, n) { Begin[i] = vis[i] = 0; a[i].clear(); }
        REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
        ans.clear(); flag = false;
        DFS(1, 1);
        if ( flag ) continue ;
        REP(i, 1, n) while ( a[i].size() >= 2 ) 
        {
            int x = a[i].back(); a[i].pop_back();
            int y = a[i].back(); a[i].pop_back();
            ans.push_back(pii(x, y));
        }
        puts("PAIRING"); printf("%d\n", ans.size());
        for ( auto it : ans ) printf("%d %d\n", it.x, it.y);
    }
    return 0;
}
