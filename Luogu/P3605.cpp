/***************************************************************
	File name: P3605.cpp
	Author: ljfcnyali
	Create time: 2019年09月14日 星期六 14时21分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

int n, h[maxn], Begin[maxn], Next[maxn], To[maxn], e, c[maxn], num, ans[maxn];
struct node
{
    int val, id;
    bool operator < (const node &a) const { return val > a.val; }
} a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline int lowbit(int x) { return x & -x; }

inline void Modify(int pos, int val)
{
    for ( int i = pos; i <= num; i += lowbit(i) )
        c[i] += val;
}

inline int Query(int pos)
{
    int sum = 0;
    for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i];
    return sum;
}

inline void DFS(int u)
{
    ans[u] -= Query(h[u]);
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i];
        DFS(v);
    }
    ans[u] += Query(h[u]);
    Modify(h[u], 1);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i].val), a[i].id = i;
    sort(a + 1, a + n + 1);
    REP(i, 1, n) { if ( a[i].val != a[i - 1].val ) ++ num; h[a[i].id] = num; }
    REP(i, 2, n)
    {
        int x; scanf("%d", &x);
        add(x, i);
    }
    DFS(1);
    REP(i, 1, n) printf("%d\n", ans[i]);
    return 0;
}
