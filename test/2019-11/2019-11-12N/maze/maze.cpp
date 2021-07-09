/***************************************************************
	File name: maze.cpp
	Author: ljfcnyali
	Create time: 2019年11月12日 星期二 19时10分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 10010;

int n, m, t, Begin[maxn], Next[maxn], To[maxn], e, f[1010][1010], ans, a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

int main()
{
    freopen("maze.in", "r", stdin);
    freopen("maze.out", "w", stdout);
    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &m);
        mem(Begin); e = 0; ans = 0x3f3f3f3f;
        REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
        scanf("%d", &t);
        REP(i, 1, t) scanf("%d", &a[i]);
        REP(i, 1, n) f[i][1] = 1; f[a[1]][1] = 0;
        REP(o, 2, t)
            REP(u, 1, n)
            {
                f[u][o] = f[u][o - 1];
                for ( int i = Begin[u]; i; i = Next[i] ) 
                {
                    int v = To[i];
                    f[u][o] = min(f[u][o], f[v][o - 1]);
                }
                if ( a[o] != u ) ++ f[u][o];
            }
        // REP(i, 1, n) REP(j, 1, t) printf("%d %d %d\n", i, j, f[i][j]);
        REP(i, 1, n) ans = min(ans, f[i][t]); printf("%d\n", ans);
    }
    return 0;
}
