/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2020年11月20日 星期五 10时53分05秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, Begin[maxn], Next[maxn], To[maxn], e, MaxDeg, deg[maxn], t;
vector<pii> ans;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; ++ deg[u]; }

inline void DFS(int u, int fa)
{
    ans.push_back(pii(u, t));
    int now = t - 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( t == MaxDeg ) { t = MaxDeg - deg[u]; ans.push_back(pii(u, t)); }
        ++ t; DFS(v, u); ++ t; ans.push_back(pii(u, t));
    }
    if ( u != 1 && t > now ) { ans.push_back(pii(u, now)); t = now; }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, n) MaxDeg = max(MaxDeg, deg[i]);
    DFS(1, 0);
    printf("%d\n", ans.size());
    for ( auto it : ans ) printf("%d %d\n", it.first, it.second);
    return 0;
}
