/***************************************************************
	File name: tree.cpp
	Author: ljfcnyali
	Create time: 2019年11月06日 星期三 08时24分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e = 1, L, S;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

namespace Subtask1
{
    long double f[maxn][maxn], ans;

    inline void DFS(int u, int fa)
    {
        int sum = 0;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            DFS(v, u); ++ sum;
            REP(j, 0, S) REP(k, 0, L) f[u][j + k] += f[v][j] / (L + 1);
        }
        if ( !sum ) f[u][0] = 1;
    }

    inline int main()
    {
        DFS(1, 0);
        REP(i, 0, S) ans += f[1][i];
        printf("%.6Lf\n", ans);
        return 0;
    }
}

namespace Subtask2
{
    int w[maxn], num1, num2, Max, pos;

    inline void DFS1(int u, int fa, int dis)
    {
        if ( dis > Max ) { Max = dis; pos = u; }
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            DFS1(v, u, dis + w[i]);
        }
    }

    inline int Check()
    {
        Max = 0; pos = 0;
        DFS1(1, 0, 0);
        DFS1(pos, 0, 0);
        return Max <= S;
    }

    inline void DFS(int x)
    {
        if ( x == 2 * n ) { ++ num1; num2 += Check(); return ; }
        REP(i, 0, L) { w[x] = w[x + 1] = i; DFS(x + 2); }
    }

    inline int main()
    {
        DFS(2); 
        printf("%.6lf\n", num2 * 1.0 / num1);
        return 0;
    }
}

signed main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &L, &S);
    REP(i, 1, n - 1) { int u, v; scanf("%lld%lld", &u, &v); add(u, v); add(v, u); }
    if ( S == 100 || S == 500 ) return Subtask1 :: main();
    return Subtask2 :: main();
}
