/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年11月10日 星期日 21时31分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100010;

int n, m, s, Begin[maxn], Next[maxn], To[maxn], e, W[maxn], dis[maxn], p[maxn];
bool vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

struct node 
{ 
    int x, y; 
    node (int X, int Y) { x = X; y = Y; }
    bool operator < (const node &a) const { return x < a.x; }
} ;

int main()
{
    freopen("path2.in", "r", stdin);
    freopen("path2.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v, w; read(u); read(v); scanf("%d", &w); add(u, v, w); }
    scanf("%d", &s); memset(dis, 0x3f, sizeof(dis)); dis[s] = 0;
    priority_queue<node> Q; Q.push(node(0, s));
    while ( !Q.empty() ) 
    {
        int u = Q.top().y; Q.pop();
        ++ p[u]; if ( p[u] > n ) { puts("ERROR"); return 0; }
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( dis[v] > dis[u] + W[i] ) 
            {
                dis[v] = dis[u] + W[i];
                if ( !vis[v] ) { vis[v] = true; Q.push(node(p[v], v)); }
            }
        }
        vis[u] = false;
    }
    REP(i, 1, n) printf("%d ", dis[i] == 0x3f3f3f3f ? -1 : dis[i]); puts("");
    return 0;
}
