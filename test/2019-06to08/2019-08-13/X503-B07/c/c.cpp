/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2019年08月13日 星期二 09时18分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 20010;
const LL Mod = 998244353;

int a, b, n, Begin[maxn], Next[maxn], To[maxn], e;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

namespace Subtask
{
    inline LL js(int x) { LL sum = 1; REP(i, 2, x) sum = (sum * i) % Mod; return sum; }

    inline LL DFS(int u, int fa)
    {
        LL sum = 1, son = 0;
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; if ( v == fa ) continue ;
            sum = (sum * DFS(v, u)) % Mod; ++ son;
        }
        sum = (sum * js(son)) % Mod;
        return sum;
    }

    inline void Solve()
    {
        REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
        printf("%lld\n", DFS(a, 0));
    }
}

int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%d%d%d", &n, &a, &b);
    if ( a == b ) { Subtask :: Solve(); return 0; }
    return 0;
}
