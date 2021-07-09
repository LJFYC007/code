/***************************************************************
	File name: physics.cpp
	Author: ljfcnyali
	Create time: 2019年08月01日 星期四 08时46分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 400010;
const int INF = 1e9 + 7;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, m, s, t, p[110], dis[maxn];
bool vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void Spfa()
{
    memset(dis, 0x3f, sizeof(dis)); queue<int> Q; Q.push(s); dis[s] = 0;
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] )
        {
            int v = To[i];
            if ( dis[v] > dis[u] + W[i] ) 
            {
                dis[v] = dis[u] + W[i];
                if ( !vis[v] ) { vis[v] = true; Q.push(v); }
            }
        }
        vis[u] = false;
    }
}

int main()
{
    freopen("physics.in", "r", stdin);
    freopen("physics.out", "w", stdout);
    scanf("%d%d%d%d%d", &n, &n, &m, &s, &t);
    p[0] = 1; REP(i, 1, 10) p[i] = p[i - 1] * 2;
    REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, p[w]); add(v, u, p[w]); }
    Spfa();
    printf("%d\n", dis[t] % INF);
    return 0;
}
