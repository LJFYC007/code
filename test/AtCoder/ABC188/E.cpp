/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2021年01月10日 星期日 20时17分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;
const int INF = 2147483647;

int n, m, a[maxn], Begin[maxn], Next[maxn], To[maxn], e, ans = -INF, f[maxn], deg[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[v]; } 

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { scanf("%d", &a[i]); f[i] = a[i]; }
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(v, u); }
    queue<int> Q; REP(i, 1, n) if ( !deg[i] ) Q.push(i);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        for ( int i = Begin[u]; i; i = Next[i] ) 
        {
            int v = To[i]; ans = max(ans, f[u] - a[v]);
            f[v] = max(f[v], f[u]); -- deg[v];
            if ( !deg[v] ) Q.push(v);
        }
    }
    printf("%d\n", ans);
    return 0;
}
