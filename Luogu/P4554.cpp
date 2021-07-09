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

const int maxn = 4000010;
const int INF = 0x3f3f3f3f;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn], dis[maxn], n, m, a[510][510];
int dt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int s1, t1, s2, t2, s, t;
bool vis[maxn];

inline void add(int u, int v, int w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while(1)
    {
        scanf("%d%d", &n, &m);
        if ( !n && !m ) return 0;
        mem(a); mem(Begin); e = 0; mem(vis);
        REP(i, 1, n)
        {
            char s[1010];
            scanf("%s", s);
            REP(j, 1, m) a[i][j] = s[j - 1] == '@' ? 1 : 0;
        } 
        REP(i, 1, n)
            REP(j, 1, m)
                REP(k, 0, 3)
                {
                    int u = i + dt[k][0], v = j + dt[k][1];
                    if ( u < 1 || v < 1 || u > n || v > m ) continue ;
                    int x = (i - 1) * m + j, y = (u - 1) * m + v;
                    if ( a[i][j] == a[u][v] ) { add(x, y, 0); add(y, x, 0); }
                    else { add(x, y, 1); add(y, x, 1); }
                }
        scanf("%d%d%d%d", &s1, &t1, &s2, &t2);
        ++ s1; ++ s2; ++ t1; ++ t2;
        s = (s1 - 1) * m + t1; t = (s2 - 1) * m + t2;
        REP(i, 0, n * m + 1) dis[i] = INF;
        dis[s] = 0;
        queue<int> Q;
        Q.push(s);
        vis[s] = true;
        while ( !Q.empty() )
        {
            int u = Q.front(); Q.pop();
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
        // REP(i, 1, n * m) printf("%d ", dis[i]);
        printf("%d\n", dis[t]);
    }
    return 0;
}
