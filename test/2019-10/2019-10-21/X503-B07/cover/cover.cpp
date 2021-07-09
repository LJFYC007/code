/***************************************************************
	File name: cover.cpp
	Author: ljfcnyali
	Create time: 2019年10月21日 星期一 09时48分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 600010;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, p[maxn];
int tot, Root[maxn], num, ans[maxn];

struct node
{
    int l, r, w;
    bool operator < (const node &a) const { return l < a.l || (l == a.l && r > a.r); }
} a[maxn];
struct Node
{
    int x;
    bool operator < (const Node &a) const { return x > a.x; }
} p1, p2;

multiset<Node> Set[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Merge(int u, int v)
{
    if ( Set[u].size() < Set[v].size() ) swap(Set[u], Set[v]);
    vector<int> t;
    while ( !Set[v].empty() ) 
    {
        auto x = Set[u].begin(), y = Set[v].begin();
        t.push_back(x -> x + y -> x);
        Set[u].erase(x); Set[v].erase(y);
    }
    for ( auto i : t ) { p1.x = i; Set[u].insert(p1); }
}

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; DFS(v);
        Merge(u, v);
    }
    p1.x = p[u];
    Set[u].insert(p1);
}

inline void read(int &x) 
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

signed main()
{
    freopen("cover.in", "r", stdin);
    freopen("cover.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, m) { read(a[i].l); read(a[i].r); read(a[i].w); }
    sort(a + 1, a + m + 1);
    stack<pii> Stack;
    REP(i, 1, m)
    {
        while ( !Stack.empty() && a[i].r > Stack.top().first ) Stack.pop();
        ++ tot; p[tot] = a[i].w;
        if ( !Stack.empty() ) add(Stack.top().second, tot);
        else Root[++ num] = tot;
        Stack.push(make_pair(a[i].r, tot));
    }
    REP(i, 1, num) 
    {
        DFS(Root[i]);
        int num = 0;
        for ( auto j : Set[Root[i]] ) ans[++ num] += j.x;
    }
    REP(i, 1, m) printf("%lld ", ans[i] += ans[i - 1]); puts("");
    return 0;
}
