/***************************************************************
	File name: prime.cpp
	Author: ljfcnyali
	Create time: 2020年10月19日 星期一 09时37分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define x first
#define y second
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 2e5 + 10;
const int maxm = 5e7 + 10;
const int inf = 5000 * 5000 * 2;
const int INF = maxm * maxm;

int n, q, ans, pri[maxn * 100], tot;
pii a[maxn], b[4];
struct node 
{
    int l, r; mutable pii val;
    node ( int a = 0, int b = 0, pii c = pii(0, 0) ) { l = a; r = b; val = c; }
    bool operator < (const node &a) const { return l < a.l; }
} ;
multiset<node> Set;
struct Node 
{
    int prime[4], sum, lazy, tag;
} Tree[maxn << 2];
bool vis[maxm];
vector<pii> g;

inline void INIT(int n)
{
    for ( int i = 2; i <= n; ++ i ) 
    {
        if ( !vis[i] ) pri[++ tot] = i; 
        for ( int j = 1; j <= tot && i * pri[j] <= n; ++ j ) 
        {
            vis[i * pri[j]] = true;
            if ( i % pri[j] == 0 ) break ;
        }
    }
}

inline pii operator +(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
inline pii operator *(pii a, pii b) { return pii(a.x * b.x - a.y * b.y, a.y * b.x + b.y * a.x); }
inline int len(pii a) { return a.x * a.x + a.y * a.y; }
inline bool fakecheck(int x) { return (x <= maxn - 10) && (!vis[x]); }
inline bool Check(pii x) { return x.x > 1 && x.y == 0 && fakecheck(x.x); }

inline bool check(pii a) 
{ 
    if ( a.x != 0 && a.y != 0 ) return false;
    if ( a.x == 0 && a.y == 0 ) return false;
    if ( abs(a.x + a.y) == 1 ) return false;
    return fakecheck(abs(a.x + a.y));
}

inline int Get(pii x)
{
    if ( x.x > 0 && x.y == 0 ) return 0;
    if ( x.y > 0 && x.x == 0 ) return 1;
    if ( x.x < 0 && x.y == 0 ) return 2;
    if ( x.y < 0 && x.x == 0 ) return 3;
    return -1;
}

inline bool calc(int x)
{
    if ( x <= maxm - 10 && !vis[x] ) return true;
    int y = sqrt(x);
    if ( y * y != x || y > inf ) return false;
    if ( vis[y] ) return false;
    return true;
}

inline auto Split(int x)
{
    if ( x > n || !Set.size() ) return Set.end();
    auto it = -- Set.upper_bound(node(x));
    if ( it -> l == x ) return it;
    int l = it -> l, r = it -> r; pii val = it -> val;
    Set.erase(it); Set.insert(node(l, x - 1, val));
    return Set.insert(node(x, r, val));
}

inline void Assign(int l, int r, pii val)
{
    auto itr = Split(r + 1), itl = Split(l);
    Set.erase(itl, itr);
    Set.insert(node(l, r, val));
}

inline void PushTag(int root, int l, int r, int x)
{
    Tree[root].tag = x; Tree[root].lazy = Tree[root].sum = 0;
    REP(i, 0, 3) 
        if ( i != x ) Tree[root].prime[i] = 0;
        else Tree[root].prime[i] = Tree[root].sum = r - l + 1;
}

inline void PushLazy(int root, int x)
{
    Tree[root].lazy += x;
    static int a[5];
    REP(i, 0, 3) a[(i + x) % 4] = Tree[root].prime[i];
    REP(i, 0, 3) Tree[root].prime[i] = a[i];
}

inline void PushUp(int root)
{
    REP(i, 0, 3) Tree[root].prime[i] = Tree[lson].prime[i] + Tree[rson].prime[i];
    Tree[root].sum = Tree[lson].sum + Tree[rson].sum;
}

inline void PushDown(int root, int l, int r)
{
    if ( Tree[root].tag != -2 ) 
    {
        int Mid = l + r >> 1;
        PushTag(lson, l, Mid, Tree[root].tag);
        PushTag(rson, Mid + 1, r, Tree[root].tag);
        Tree[root].tag = -2;
    }
    Tree[root].lazy &= 3;
    if ( Tree[root].lazy ) 
    {
        PushLazy(lson, Tree[root].lazy);
        PushLazy(rson, Tree[root].lazy);
        Tree[root].lazy = 0;
    }
}

inline void Modify1(int root, int l, int r, int L, int R, int x)
{
    if ( L <= l && r <= R ) { PushTag(root, l, r, x); return ; }
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( L <= Mid ) Modify1(lson, l, Mid, L, R, x);
    if ( Mid < R ) Modify1(rson, Mid + 1, r, L, R, x);
    PushUp(root);
}

inline void Modify2(int root, int l, int r, int L, int R, int x)
{
    if ( L <= l && r <= R ) { PushLazy(root, x); return ; }
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( L <= Mid ) Modify2(lson, l, Mid, L, R, x);
    if ( Mid < R ) Modify2(rson, Mid + 1, r, L, R, x);
    PushUp(root);
}

inline int Find(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].lazy & 3;
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( pos <= Mid ) return Find(lson, l, Mid, pos);
    return Find(rson, Mid + 1, r, pos);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].prime[0];
    int Mid = l + r >> 1, ret = 0; PushDown(root, l, r);
    if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
    return ret;
}

signed main()
{
    freopen("prime.in", "r", stdin);
    freopen("prime.out", "w", stdout);
    b[0] = pii(1, 0); b[1] = pii(0, 1); b[2] = pii(-1, 0); b[3] = pii(0, -1); 
    INIT(maxm - 10);
    scanf("%lld%lld", &n, &q);
    REP(i, 1, n * 4) Tree[i].tag = -2;
    REP(i, 1, n) 
    { 
        scanf("%lld%lld", &a[i].x, &a[i].y); 
        if ( check(a[i]) ) { Set.insert(node(i, i, pii(0, 0))); Modify1(1, 1, n, i, i, Get(a[i])); }
        else Set.insert(node(i, i, a[i])); 
    }
    int cnt = 0;
    while ( q -- ) 
    {
        // if ( q % 1000 == 0 ) cerr << Set.size() << " " << q << endl;
        int op, l, r, x, y; scanf("%lld%lld%lld", &op, &l, &r);
        if ( op == 1 ) 
        {
            scanf("%lld%lld", &x, &y);
            auto itr = Split(r + 1), itl = Split(l);
            Set.erase(itl, itr);
            if ( check(pii(x, y)) ) { Set.insert(node(l, r, pii(0, 0))); Modify1(1, 1, n, l, r, Get(pii(x, y))); }
            else { Set.insert(node(l, r, pii(x, y))); Modify1(1, 1, n, l, r, -1); }
        }
        if ( op == 2 ) 
        {
            scanf("%lld%lld", &x, &y);
            if ( x == 0 && y == 0 ) 
            {
                Modify1(1, 1, n, l, r, -1); Assign(l, r, pii(0, 0));
                continue ;
            }

            if ( abs(x) + abs(y) == 1 ) 
            {
                auto itr = Split(r + 1), itl = Split(l);
                Modify2(1, 1, n, l, r, Get(pii(x, y)));
                continue ;
            }

            auto itr = Split(r + 1), itl = Split(l);
            vector<node> p; p.clear(); g.clear(); int lst = l;
            for ( auto it = itl; it != itr; ++ it )
            {
                it -> val = it -> val * pii(x, y) * b[Find(1, 1, n, it -> l)];
                int t = len(it -> val), x = sqrt(t);
                if ( !calc(t) ) it -> val = pii(0, 0);
                if ( Get(it -> val) != -1 ) 
                {
                    p.push_back(node(it -> l, it -> r, pii(Get(it -> val), 0)));
                    it -> val = pii(0, 0);
                }
                if ( it -> val != pii(0, 0) ) { g.push_back(pii(lst, it -> l - 1)); lst = it -> r + 1; }
            }
            g.push_back(pii(lst, r));
            Modify1(1, 1, n, l, r, -1);
            for ( auto it : g ) if ( it.x <= it.y ) Assign(it.x, it.y, pii(0, 0));
            for ( auto it : p ) Modify1(1, 1, n, it.l, it.r, it.val.x % 4);
        }
        if ( op == 3 ) 
        {
            ans = Query(1, 1, n, l, r);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
