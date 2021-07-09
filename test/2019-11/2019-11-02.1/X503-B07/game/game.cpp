/***************************************************************
	File name: game.cpp
	Author: ljfcnyali
	Create time: 2019年11月02日 星期六 14时49分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100010;

int n, m, dis1[maxn], dis2[maxn], Begin[maxn], To[maxn], Next[maxn], e, W[maxn], a[maxn], s, t;
bool vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &s, &t); ++ s; ++ t;
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); ++ u; ++ v; add(u, v, w); add(v, u, w); }
    memset(dis1, 0x3f, sizeof(dis1)); dis1[s] = 0; dis2[s] = a[s];
    queue<int> Q; Q.push(s);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; 
            if ( dis1[v] > dis1[u] + W[i] || (dis1[v] == dis1[u] + W[i] && dis2[v] < dis2[u] + a[v]) )
            {
                dis1[v] = dis1[u] + W[i];
                dis2[v] = dis2[u] + a[v];
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
    printf("%d %d\n", dis1[t], dis2[t]);
    return 0;
}
