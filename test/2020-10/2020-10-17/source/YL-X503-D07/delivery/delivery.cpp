/***************************************************************
	File name: delivery.cpp
	Author: ljfcnyali
	Create time: 2020年10月17日 星期六 08时28分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 6e5 + 10;

int n, a[maxn], f[maxn], Begin[maxn], Next[maxn], To[maxn], e, size[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline bool cmp(pii a, pii b) { return a.first - 2 * a.second > b.first - 2 * b.second; }

inline void DFS(int u, int fa)
{
    vector<pii> p; p.clear();
    f[u] = a[u]; size[u] = 1;
    for ( int i = Begin[u]; i; i = Next[i]  )
    {
        int v = To[i]; if ( v == fa ) continue ;
        DFS(v, u); size[u] += size[v]; 
        p.push_back(pii(f[v], size[v]));
    }
    sort(p.begin(), p.end(), cmp); 
    int sum = 0;
    for ( auto it : p ) 
    {
        f[u] = max(f[u], it.first + sum + 1);
        sum += 2 * it.second;
    }
}

int main()
{
    freopen("delivery.in", "r", stdin);
    freopen("delivery.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    DFS(1, 0); 
    f[1] = max(f[1], a[1] + (n - 1) * 2);
    printf("%d\n", f[1]);
    return 0;
}
