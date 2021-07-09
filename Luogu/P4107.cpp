/***************************************************************
	File name: P4107.cpp
	Author: ljfcnyali
	Create time: 2019年07月21日 星期日 14时20分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 4000010;

int Begin[maxn], Next[maxn], To[maxn], e;
int son[maxn], a[maxn], n, m, ans;

struct node
{
    int val, size, id;
    bool operator < (const node &a) const { return val + size > a.val + a.size; }
} p1, p2;

inline void add(int u, int v) { ++ v; To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    priority_queue<node> Q;
    for ( int i = Begin[u]; i; i = Next[i] )
    {
        int v = To[i]; ++ son[u];
        DFS(v);
        p1.id = v; p1.val = a[v]; p1.size = son[v];
        Q.push(p1);
    }
    if ( !son[u] ) return ;
    while ( !Q.empty() && a[u] + son[u] + Q.top().val + Q.top().size - 1 <= m ) 
    {
        a[u] += Q.top().val; son[u] += Q.top().size - 1; 
        Q.pop();
        ++ ans;
    }
    while ( !Q.empty() ) Q.pop();
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n)
    {
        int k; scanf("%d", &k);
        REP(j, 1, k) { int x; scanf("%d", &x); add(i, x); }
    }
    DFS(1);
    printf("%d\n", ans);
    return 0;
}
