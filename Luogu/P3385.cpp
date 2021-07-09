#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 100010;
const int INF = 1000000000;

int Begin[maxn], Next[maxn], To[maxn], e, n, m;
int T, cnt[maxn], dis[maxn], W[maxn];
bool vis[maxn];

inline void add(int u, int v, int w) 
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline bool SPFA()
{
    queue<int> Q;
    Q.push(1);
    REP(i, 1, n) dis[i] = INF;
    dis[1] = 0; cnt[1] = 1; vis[1] = true;
    while ( !Q.empty() )
    {
        int u = Q.front(); Q.pop();
        vis[u] = false;
        if ( cnt[u] > n ) return true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( dis[v] > dis[u] + W[i] ) 
            {
                dis[v] = dis[u] + W[i];
                cnt[v] = cnt[u] + 1;
                if ( cnt[v] > n ) return true;
                if ( !vis[v] ) 
                {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }            
    }
    return false;
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
        mem(vis); mem(cnt); mem(Begin);
        e = 0;
        REP(i, 1, m)
        {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            add(u, v, w); 
            if ( w >= 0 ) add(v, u, w);
        }
        if ( SPFA() ) printf("YE5\n");
        else printf("N0\n");
    }
    return 0;
}
