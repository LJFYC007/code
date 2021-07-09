/***************************************************************
	File name: P1144.cpp
	Author: ljfcnyali
	Create time: 2019年06月16日 星期日 09时48分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 4000010;
const int Mod = 100003;

int n, m, Begin[maxn], Next[maxn], To[maxn], e;
int dis[maxn], ans[maxn];
bool vis[maxn];

inline void add(int u, int v)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    REP(i, 2, n) dis[i] = 0x3f3f3f3f;
    queue<int> Q; Q.push(1);
    ans[1] = 1;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop(); vis[u] = false;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( dis[v] >= dis[u] + 1 ) 
            {
                if ( dis[v] > dis[u] + 1 ) { dis[v] = dis[u] + 1; ans[v] = 0; }
                ans[v] += ans[u];
                ans[v] %= Mod;
                if ( !vis[v] ) 
                {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }
    REP(i, 1, n) printf("%d\n", ans[i]);
    return 0;
}
