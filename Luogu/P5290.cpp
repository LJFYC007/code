/***************************************************************
	File name: P5290.cpp
	Author: ljfcnyali
	Create time: 2019年10月20日 星期日 20时13分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;

int n, a[maxn], Begin[maxn], Next[maxn], To[maxn], e;
priority_queue<int> Q[maxn];
vector<int> p;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Merge(int x, int y)
{
    p.clear();    
    if ( Q[x].size() < Q[y].size() ) swap(Q[x], Q[y]);
    while ( !Q[y].empty() ) 
    {
        p.push_back(max(Q[x].top(), Q[y].top()));
        Q[x].pop(); Q[y].pop();
    }
    for ( auto i : p ) Q[x].push(i);
}

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; 
        DFS(v); Merge(u, v);
    }
    Q[u].push(a[u]);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 2, n) { int u; scanf("%lld", &u); add(u, i); }
    DFS(1);
    int ans = 0;
    while ( !Q[1].empty() ) ans += Q[1].top(), Q[1].pop();
    printf("%lld\n", ans);
    return 0;
}
