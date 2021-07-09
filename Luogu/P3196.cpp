/***************************************************************
	File name: P3196.cpp
	Author: ljfcnyali
	Create time: 2021年01月05日 星期二 14时42分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

int n, m, ans, Begin[maxn], Next[maxn], To[maxn], e, Col[maxn];
int label[maxn], a[maxn];
bool vis[maxn], use[maxn];
set<pii> Set;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void Modify(int u) 
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
        vis[Col[To[i]]] = true;
    REP(i, 1, maxn - 10) if ( !vis[i] ) { Col[u] = i; ans = max(ans, i); break ; } 
    for ( int i = Begin[u]; i; i = Next[i] ) 
        vis[Col[To[i]]] = false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, v); add(v, u); }
    REP(i, 1, n) Set.insert(pii(0, i));
    REP(i, 1, n)
    {
        int x = (*Set.begin()).second; Set.erase(pii(-label[x], x)); a[i] = x; use[x] = true;
        for ( int j = Begin[x]; j; j = Next[j] ) 
        {
            int v = To[j]; if ( use[v] ) continue ; 
            Set.erase(pii(-label[v], v));
            ++ label[v]; 
            Set.insert(pii(-label[v], v));
        }
    }
    REP(i, 1, n) Modify(a[i]);
    printf("%d\n", ans);
    return 0;
}
