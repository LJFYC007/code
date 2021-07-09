/***************************************************************
	File name: ttds.cpp
	Author: ljfcnyali
	Create time: 2021年01月12日 星期二 11时39分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;
const int Mod = 998244353;
const int N = 1e5;

int n, k, b, a[maxn], c[maxn], Root[maxn], tot;
struct node
{
    int i, l, h, pre; bool op;
    node(int a = 0, int b = 0, int c = 0, int d = 0, bool e = false) { i = a; l = b; h = c; pre = d; op = e; }
    bool operator < (const node &a) const 
    { 
        if ( op != a.op ) return op < a.op;
        if ( op == false ) return l < a.l || (l == a.l && pre > a.pre); 
        return l > a.l || (l == a.l && pre > a.pre); 
    }
} ;
priority_queue<node> Q;
set<pii> Set;
struct Node { int lson, rson, sum; } Tree[maxn << 5];

inline int Modify(int now, int l, int r, int pos)
{
    int root = ++ tot; Tree[root] = Tree[now]; ++ Tree[root].sum;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) ls(root) = Modify(ls(root), l, Mid, pos);
    else rs(root) = Modify(rs(root), Mid + 1, r, pos);
    return root;
}

inline int Query(int root, int l, int r, int pos)
{
    if ( !root || !Tree[root].sum ) return INF;
    if ( l == r ) return l;
    int Mid = l + r >> 1, ret = INF;
    if ( pos <= Mid ) ret = min(ret, Query(ls(root), l, Mid, pos));
    if ( ret == INF ) ret = min(ret, Query(rs(root), Mid + 1, r, pos));
    return ret;
}

signed main()
{
    freopen("ttds.in", "r", stdin);
    freopen("ttds.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &k, &b);
    int val = INF; REP(i, 1, n) { scanf("%lld", &a[i]); val = min(val, a[i]); }
    c[n + 1] = INF; 
    for ( int i = n; i >= 1; -- i ) 
    {
        c[i] = min(c[i + 1], a[i]);
        Set.insert(pii(a[i], i));
        Root[i] = Modify(Root[i + 1], 1, N, a[i]);
    }
    Q.push(node(0, 0, 0, val, 0));
    while ( 1 ) 
    {
        while ( Q.top().op == true ) 
        {
            node x = Q.top(); Q.pop();
            auto it = Set.lower_bound(pii(x.pre, x.i + 1));
            while ( it != Set.end() && (*it).first == x.pre ) 
            {
                int i = (*it).second; ++ it;
                Q.push(node(i, x.l + 1, (x.h * b + a[i]) % Mod, c[i + 1], 0));
                printf("%lld\n", (x.h * b + a[i]) % Mod); -- k; if ( k == 0 ) return 0; 
            }
            if ( x.pre == N ) continue ; 
            int Min = Query(Root[x.i + 1], 1, N, x.pre + 1);
            // int Min = INF; REP(i, x.i + 1, n) if ( a[i] > x.pre ) Min = min(Min, a[i]);
            if ( Min != INF ) Q.push(node(x.i, x.l, x.h, Min, 0));
        }

        node x = Q.top(); Q.pop(); vector<node> p; p.push_back(x);
        while ( !Q.empty() && Q.top().l == x.l && Q.top().pre == x.pre ) { p.push_back(Q.top()); Q.pop(); }
        for ( auto it : p ) Q.push(node(it.i, it.l, it.h, it.pre, 1));
    }
    return 0;
}
