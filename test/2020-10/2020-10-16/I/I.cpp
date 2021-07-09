/***************************************************************
	File name: I.cpp
	Author: ljfcnyali
	Create time: 2020年10月16日 星期五 20时21分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, m, s, q, Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int dis[maxn];
bitset<10001> Set[maxn];
vector<int> p;
priority_queue<pii, vector<pii>, greater<pii> > Q;
bool vis[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%d%d%d%d", &n, &m, &s, &q) )
    {
        e = 0; REP(i, 1, n) { Begin[i] = vis[i] = 0; dis[i] = INF; Set[i].reset(); }
        REP(i, 1, m) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
        p.clear();
        REP(i, 1, s) { int x; scanf("%d", &x); p.push_back(x); dis[x] = 0; Q.push(pii(0, x)); Set[x][x] = 1; }
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
                    Set[v] = Set[u]; 
                    Q.push(pii(dis[v], v));
                }
                else if ( dis[v] == dis[u] + W[i] ) Set[v] |= Set[u];
            }
        }

        REP(i, 1, q)
        {
            int x; scanf("%d", &x);
            int pos = Set[x]._Find_first();
            printf("%d ", pos);
            while ( (pos = Set[x]._Find_next(pos)) < 10001 ) printf("%d ", pos); 
            puts("");
        }
    }
    return 0;
}
