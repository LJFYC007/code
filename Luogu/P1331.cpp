/***************************************************************
	File name: P1331.cpp
	Author: ljfcnyali
	Create time: 2019年06月26日 星期三 08时09分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

LL Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
LL n, s, dis[maxn], ans, Max[maxn];

inline void add(LL u, LL v, LL w)
{
    To[++ e] = v;
    Next[e] = Begin[u];
    Begin[u] = e;
    W[e] = w;
}

inline void DFS(LL u, LL fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) DFS(To[i], u);
    for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) Max[u] = max(Max[u], W[i]);
    for ( int i = Begin[u]; i; i = Next[i] ) if ( To[i] != fa ) ans += Max[u] - W[i];
    for ( int i = Begin[fa]; i; i = Next[i] ) if ( To[i] == u ) W[i] += Max[u];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &s);
    REP(i, 1, n - 1) { LL u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    DFS(s, 0);
    printf("%lld\n", ans);
    return 0;
}
