/***************************************************************
	File name: horse.cpp
	Author: ljfcnyali
	Create time: 2019年09月20日 星期五 19时18分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, a[maxn], size[maxn], num, ans;
struct node
{
    int sum, pos, len;
    bool operator < (const node &a) const { return sum < a.sum; } 
} p1;
priority_queue<node> p[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS1(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        if ( a[v] > W[i] ) size[v] += a[v] - W[i];
        DFS1(v, u);
        size[u] += size[v];
        p1.sum = size[v]; p1.pos = v; p1.len = W[i];
        p[u].push(p1);
    }
}

inline void DFS2(int u)
{
    num += a[u];
    while ( !p[u].empty() ) 
    {
        node x = p[u].top(); p[u].pop();
        if ( num < x.len ) { ans += x.len - num; num = x.len; }
        num -= x.len;
        DFS2(x.pos);
        if ( num < x.len ) { ans += x.len - num; num = x.len; }
        num -= x.len;
        // cerr << num << " " << p1.len << endl;
    }
    cerr << u << " " << ans << " " << num << endl;
}

int main()
{
    freopen("horse.in", "r", stdin);
    freopen("horse.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n - 1) { int u, v, w; scanf("%d%d%d", &u, &v, &w); add(u, v, w); add(v, u, w); }
    DFS1(1, 0);
    DFS2(1);
    printf("%d\n", ans);
    return 0;
}
