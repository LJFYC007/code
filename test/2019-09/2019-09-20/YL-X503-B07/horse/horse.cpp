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
#define int long long
typedef long long LL;

const int maxn = 200010;

int Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int n, a[maxn], ans, num;
struct node
{
    int pos, len;
    bool operator < (const node &a) const { return len > a.len; } 
} p1;
priority_queue<node> p[maxn];

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }

inline void DFS1(int u, int fa)
{
    num += a[u];
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        p1.pos = v; p1.len = W[i]; p[u].push(p1);
    }
    while ( !p[u].empty() ) 
    {
        node x = p[u].top(); p[u].pop();
        if ( num < x.len ) { ans += x.len - num; num = 0; }
        else num -= x.len;
        DFS1(x.pos, u);
        if ( num < x.len ) { ans += x.len - num; num = 0; }
        else num -= x.len;
    }
}

signed main()
{
    freopen("horse.in", "r", stdin);
    freopen("horse.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    DFS1(1, 0);
    printf("%lld\n", ans);
    return 0;
}
