/***************************************************************
	File name: P4551.cpp
	Author: ljfcnyali
	Create time: 2019年08月18日 星期日 14时25分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 8000010;

struct node
{
    int next[2];
} Trie[maxn];

int n, Begin[maxn], Next[maxn], To[maxn], e, W[maxn];
int dis[maxn], cnt = 1, ans;

inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; } 

inline void DFS(int u, int fa)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa ) continue ;
        dis[v] = dis[u] ^ W[i];
        DFS(v, u);
    }
}

inline void Insert(int x)
{
    int u = 1;
    for ( int i = 30; i >= 0; -- i )
    {
        int c = (x >> i) & 1;
        if ( !Trie[u].next[c] ) Trie[u].next[c] = ++ cnt;
        u = Trie[u].next[c];
    }
}

inline void Query(int x)
{
    int sum = 0, u = 1;
    for ( int i = 30; i >= 0; -- i )
    {
        int c = (x >> i) & 1;
        if ( Trie[u].next[!c] ) c ^= 1;
        if ( c == 1 ) sum += 1 << i;
        u = Trie[u].next[c];
    }
    ans = max(ans, sum ^ x);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n - 1) { int u, v, w; scanf("%lld%lld%lld", &u, &v, &w); add(u, v, w); add(v, u, w); }
    DFS(1, 0);
    REP(i, 1, n) Insert(dis[i]);
    REP(i, 1, n) Query(dis[i]);
    printf("%lld\n", ans);
    return 0;
}
