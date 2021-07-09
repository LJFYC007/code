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

const int maxn = 2000010;

int Begin[maxn], To[maxn], Next[maxn], W[maxn], e, dis[maxn], n, m;
bool vis[maxn];

inline int read()
{
    char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    int x = 0;
    while ( c >= '0' && c <= '9' ) 
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline bool spfa(int x)
{
    vis[x] = true;
    for ( int i = Begin[x]; i; i = Next[i] )
    {
        int v = To[i];
        if ( dis[v] < dis[x] + W[i] )
        {
            dis[v] = dis[x] + W[i];
            if ( vis[v] ) return false;
            if ( !spfa(v) ) return false;
        }
    }
    vis[x] = false;
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    n = read(); m = read();
    REP(i, 1, m)
    {
        int opt, u, v, w;
        opt = read(); u = read(); v = read();
        if ( opt == 1 ) 
        {
            w = read();
            add(v, u, w);
        }
        else if ( opt == 2 ) 
        {
            w = read();
            add(u, v, -w);
        }
        else if ( opt == 3 ) 
        {
            add(u, v, 0); add(v, u, 0);
        }
    }
    REP(i, 1, n) add(0, i, 0);
    REP(i, 1, n) dis[i] = -2147483647;
    if ( !spfa(0) ) printf("No\n");
    else printf("Yes\n");
    return 0;
}
