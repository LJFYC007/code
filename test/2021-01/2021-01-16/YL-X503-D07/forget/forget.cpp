/***************************************************************
	File name: forget.cpp
	Author: ljfcnyali
	Create time: 2021年01月16日 星期六 10时50分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, k, c[maxn], Begin[maxn], Next[maxn], To[maxn], e, s[maxn];
map<int, int> Map[maxn];
struct node { int u, v, w; } Edge[maxn];
bool vis[maxn], flag;
vector<int> ans, p;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

namespace Subtask1
{
    inline void DFS(int u, int fa)
    {
        vis[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            if ( vis[v] ) { flag = false; return ; } 
            DFS(v, u);
        }
    }

    inline bool Check()
    {
        e = 0; mem(Begin); mem(s); mem(vis);
        for ( int i = 0; i < p.size(); ++ i ) { ++ s[Edge[p[i]].w]; add(Edge[p[i]].u, Edge[p[i]].v); add(Edge[p[i]].v, Edge[p[i]].u); }
        REP(i, 1, k) if ( s[i] > c[i] ) return false;
        flag = true; REP(i, 1, n) if ( !vis[i] ) DFS(i, 0); return flag;
    }

    inline void DFS(int x)
    {
        if ( x == m + 1 ) 
        {
            if ( ans.size() < p.size() && Check() ) 
                ans = p;
            return ; 
        }
        p.push_back(x); DFS(x + 1);
        p.pop_back(); DFS(x + 1);
    }

    int main()
    {
        DFS(1); REP(i, 1, m) vis[i] = true;
        for ( int i = 0; i < ans.size(); ++ i ) vis[ans[i]] = false;
        int num = 0;
        REP(i, 1, m) if ( vis[i] ) ++ num;
        printf("%d\n", num);
        REP(i, 1, m) if ( vis[i] ) cout << i << " "; cout << endl;
        return 0;
    }
}

namespace Subtask2
{
    inline void DFS(int u)
    {
        vis[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( vis[v] ) continue ;
            DFS(v); ans.push_back(Map[u][v]);
        }
    }

    int main()
    {
        REP(i, 1, n) if ( !vis[i] ) DFS(i); 
        while ( ans.size() > c[1] ) ans.pop_back();
        REP(i, 1, m) vis[i] = true;
        for ( int i = 0; i < ans.size(); ++ i ) vis[ans[i]] = false;
        int num = 0;
        REP(i, 1, m) if ( vis[i] ) ++ num;
        printf("%d\n", num);
        REP(i, 1, m) if ( vis[i] ) cout << i << " "; cout << endl;
        return 0;
    }
}

namespace Subtask3
{
    int main()
    {
        REP(i, 1, m) 
        {
            if ( c[Edge[i].w] == 0 ) continue ;
            -- c[Edge[i].w]; ans.push_back(i);
        }
        REP(i, 1, m) vis[i] = true;
        for ( int i = 0; i < ans.size(); ++ i ) vis[ans[i]] = false;
        int num = 0;
        REP(i, 1, m) if ( vis[i] ) ++ num;
        printf("%d\n", num);
        REP(i, 1, m) if ( vis[i] ) cout << i << " "; cout << endl;
        return 0;
    }
}

int main()
{
    freopen("forget.in", "r", stdin);
    freopen("forget.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, k) scanf("%d", &c[i]);
    REP(i, 1, m)
    {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        add(u, v); add(v, u); Edge[i].u = u; Edge[i].v = v; Edge[i].w = w; 
        Map[u][v] = Map[v][u] = i;
    }
    if ( m <= 5 ) return Subtask1 :: main();
    if ( k == 1 ) return Subtask2 :: main();
    return Subtask3 :: main();
    return 0;
}
