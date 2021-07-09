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

const int maxn = 20010;
const int INF = 0x3f3f3f3f;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn], T[8], s, t, m, dis[maxn];
bool vis[maxn];

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline void Spfa()
{
    queue<int> Q; Q.push(s);
    REP(i, 1, 100) dis[i] = INF;
    dis[s] = 0;
    while ( !Q.empty() )
    {
        int u = Q.front(); Q.pop();
        // printf("%d\n", u);
        // if ( vis[u] ) return ;
        vis[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i];
            if ( dis[v] > dis[u] + W[i] ) 
            {
                dis[v] = dis[u] + W[i];
                if ( !vis[v] ) 
                {
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
        vis[u] = false;
    }
    printf("%d\n", dis[t]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    T[1] = 2; T[2] = 6; T[3] = 4; T[4] = 8; T[5] = 6; T[6] = 10; T[7] = 14;
    REP(i, 1, 7) { int x; scanf("%d", &x); if ( x == 1 ) T[i] /= 2; }
    scanf("%d%d", &s, &t);
    scanf("%d", &m);
    REP(i, 1, m)
    {
        int u, v, x; scanf("%d%d%d", &u, &v, &x);
        add(u, v, T[x]); add(v, u, T[x]);
    }
    Spfa();
    return 0;
}
