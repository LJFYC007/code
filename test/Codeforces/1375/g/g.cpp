/***************************************************************
	File name: g.cpp
	Author: ljfcnyali
	Create time: 2020年07月07日 星期二 15时58分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, col[maxn], sum1, sum2;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        col[v] = col[u] ^ 1; sum1 += col[v]; DFS(v, u);
    }
}

int main()
{
    scanf("%d", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS(1, 0);
    sum2 = n - sum1;
    printf("%d\n", min(sum1, sum2) - 1);
    return 0;
}
