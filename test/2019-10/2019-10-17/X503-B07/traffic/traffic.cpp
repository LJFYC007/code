/***************************************************************
	File name: traffic.cpp
	Author: ljfcnyali
	Create time: 2019年10月17日 星期四 09时34分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6010;
const int INF = 0x3f3f3f3f;

int n, a[maxn], b[maxn], Begin[maxn * maxn], To[maxn * maxn], Next[maxn * maxn], e;
int dis[maxn];
LL ans;
bool vis[maxn][maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

int main()
{
    freopen("traffic.in", "r", stdin);
    freopen("traffic.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 2, n) scanf("%d", &a[i]);
    REP(i, 2, n) scanf("%d", &b[i]);
    REP(i, 2, n)
    {
        REP(j, a[i], i) if ( !vis[i][j] ) { vis[i][j] = true; add(i, j); }
        REP(j, b[i], i) if ( !vis[j][i] ) { vis[j][i] = true; add(j, i); }
    }
    REP(i, 1, n)
    {
        queue<int> Q; Q.push(i); REP(j, 1, n) dis[j] = INF; dis[i] = 0;
        while ( !Q.empty() ) 
        {
            int u = Q.front(); Q.pop();
            for ( int i = Begin[u]; i; i = Next[i] ) 
            {
                int v = To[i]; if ( dis[v] != INF ) continue ;
                dis[v] = dis[u] + 1;
                Q.push(v);
            }
        }
        REP(j, 1, n) ans ^= (i + j) * dis[j];
    }
    printf("%lld\n", ans);
    return 0;
}
