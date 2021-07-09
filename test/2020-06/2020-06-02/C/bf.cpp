/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年06月02日 星期二 08时31分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, L[maxn], R[maxn];
int dis[maxn], Q;

inline void add(int u, int v, int l, int r)
{
    To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e;
    L[e] = l; R[e] = r;
}

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( L[i] > Q || Q > R[i] ) continue ;
        dis[v] = dis[u] + 1; DFS(v, u);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C1.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) { int u, v, l, r; scanf("%d%d%d%d", &u, &v, &l, &r); add(u, v, l, r); add(v, u, l, r); }
    REP(o, 1, m)
    {
        scanf("%d", &Q);
        int ans = 0;
        REP(i, 1, n)
        {
            mem(dis); DFS(i, 0);
            int pos = i;
            REP(j, 1, n) if ( dis[j] > dis[pos] ) pos = j;
            mem(dis); DFS(pos, 0);
            REP(j, 1, n) ans = max(ans, dis[j]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
