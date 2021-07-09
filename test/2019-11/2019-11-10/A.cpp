/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年11月10日 星期日 21时23分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2000010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn], n, m, s, dis[maxn];
bool vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

int main()
{
    freopen("path1.in", "r", stdin);
    freopen("path1.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); }
    scanf("%d", &s); memset(dis, 0x3f, sizeof(dis)); dis[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii> > Q; Q.push(pii(0, s));
    while ( !Q.empty() )
    {
        int u = Q.top().second; Q.pop();
        if ( vis[u] ) continue ; vis[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; 
            if ( dis[v] > dis[u] + W[i] ) 
            { 
                dis[v] = dis[u] + W[i]; 
                if ( !vis[v] ) Q.push(pii(dis[v], v));
            }
        }
    }
    REP(i, 1, n) printf("%d ", dis[i] == 0x3f3f3f3f ? -1 : dis[i]); puts("");
    return 0;
}
