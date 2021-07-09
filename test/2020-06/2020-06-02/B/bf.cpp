/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年06月02日 星期二 10时29分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, q, s, w[maxn], Begin[maxn], Next[maxn], To[maxn], e;
int f[maxn], val[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u, int fa)
{
    val[u] = w[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        f[v] = u; DFS(v, u);
        val[u] += val[v];
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B1.out", "w", stdout);
#endif
    scanf("%d%d", &n, &q);
    REP(i, 1, n) scanf("%d", &w[i]);
    REP(i, 1, n) 
    { 
        int u, v; scanf("%d%d", &u, &v); 
        if ( !u ) s = v; 
        else { add(u, v); add(v, u); }
    }
    DFS(s, 0);
    while ( q -- ) 
    {
        int op, l, r; scanf("%d%d%d", &op, &l, &r);
        if ( op == 1 ) 
        {
            int x = r - w[l]; w[l] = r;
            while ( l != 0 ) 
            {
                val[l] += x;
                l = f[l];
            }
        }
        else 
        {
            int ans = 0;
            REP(i, l, r) ans += w[i];
            printf("%d\n", ans);
        }
    }

    return 0;
}
