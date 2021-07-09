/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年01月10日 星期日 11时47分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, k, q, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], sum, ans, use[maxn];
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u)
{
    vis[u] = true; sum += use[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( !vis[v] ) DFS(v);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    while ( q -- ) 
    {
        scanf("%d", &k); ans = 0;
        REP(i, 1, k) { scanf("%d", &a[i]); ++ use[a[i]]; }
        REP(i, 1, n)
        {
            sum = 0; 
            REP(j, 1, n) if ( j != i ) 
            {
                REP(o, 1, n) vis[o] = false; 
                vis[j] = true; DFS(i);
            }
            // cerr << i << " " << sum << endl;
            ans = max(ans, sum);
        }
        REP(i, 1, k) use[a[i]] = 0;
        printf("%d\n", ans);
    }
    return 0;
}
