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

const int maxn = 1e5 + 10;
const int maxm = 5e7 + 10;
const int inf = 5000 * 5000 * 2;
const int INF = maxm * maxm;

int n, q, ans, pri[maxn * 100], tot;
pii a[maxn];
struct node 
{
    int l, r; mutable pii val;
    node ( int a = 0, int b = 0, pii c = pii(0, 0) ) { l = a; r = b; val = c; }
    bool operator < (const node &a) const { return l < a.l; }
} ;
multiset<node> Set;
vector<node> p;
struct Node 
{
    int prime1[4], prime2[4], sum1, sum2;
    bool tag;
    pii lazy;
} Tree[maxn << 2];
bool prime[maxm], vis[maxm];

inline void INIT(int n)
{
    for ( int i = 2; i <= n; ++ i ) 
    {
        if ( !vis[i] ) { pri[++ tot] = i; prime[i] = true; }
        for ( int j = 1; j <= tot && i * pri[j] <= n; ++ j ) 
        {
            vis[i * pri[j]] = true;
            if ( i % pri[j] == 0 ) break ;
        }
    }
}

inline pii operator +(pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }
inline pii operator *(pii a, pii b) { return pii(a.x * b.x - a.y * b.y, a.y * b.x + b.y * a.x); }
inline int len(pii a) 
{ 
    if ( abs(a.x) >= inf || abs(a.y) >= inf ) return INF;
    return a.x * a.x + a.y * a.y; 
}

inline bool fakecheck(int x)
{
    if ( x >= maxm - 10 ) return false;
    if ( x == 1 ) return true;
    return prime[x];
}

inline bool check(pii a) 
{ 
    if ( a.x != 0 && a.y != 0 ) return false;
    if ( a.x == 0 && a.y == 0 ) return false;
    int t = len(a), x = sqrt(t);
    if ( x * x != t ) return false;
    return fakecheck(x);
}

inline bool Check(pii x)
{
    if ( x.x <= 1 || x.y != 0 ) return false;
    return fakecheck(x.x);
}

inline auto Split(int x)
{
    if ( x > n || !Set.size() ) return Set.end();
    if ( (*Set.begin()).l >= x ) return Set.begin();
    auto it = -- Set.upper_bound(node(x));
    if ( it -> l == x ) return it;
    if ( it -> r < x ) return ++ it;
    int l = it -> l, r = it -> r; pii val = it -> val;
    Set.erase(it); Set.insert(node(l, x - 1, val));
    return Set.insert(node(x, r, val));
}

inline void PushTag(int root, int l, int r, pii x)
{
    Tree[root].lazy = x; Tree[root].tag = true;
    bool flag = (len(x) == 1); int op = -1;
    if ( x.first > 0 && x.second == 0 ) op = 0;
    if ( x.first == 0 && x.second > 0 ) op = 1;
    if ( x.first < 0 && x.second == 0 ) op = 2;
    if ( x.first == 0 && x.second < 0 ) op = 3;
    if ( op != -1 ) 
    {
        Tree[root].prime1[op] = Tree[root].sum1 = (flag ^ 1) * (r - l + 1);
        Tree[root].prime2[op] = Tree[root].sum2 = flag * (r - l + 1);
    }
    REP(i, 0, 3) if ( op != i ) Tree[root].prime1[i] = Tree[root].prime2[i] = 0;
}

inline void PushUp(int root)
{
    REP(i, 0, 3) 
    {
        Tree[root].prime1[i] = Tree[lson].prime1[i] + Tree[rson].prime1[i];
        Tree[root].prime2[i] = Tree[lson].prime2[i] + Tree[rson].prime2[i];
    }
    Tree[root].sum1 = Tree[lson].sum1 + Tree[rson].sum1;
    Tree[root].sum2 = Tree[lson].sum2 + Tree[rson].sum2;
}

inline void PushDown(int root, int l, int r)
{
    if ( !Tree[root].tag ) return ; 
    int Mid = l + r >> 1;
    PushTag(lson, l, Mid, Tree[root].lazy);
    PushTag(rson, Mid + 1, r, Tree[root].lazy);
    Tree[root].tag = false;
}

inline void Modify1(int root, int l, int r, int L, int R, pii x)
{
    if ( L <= l && r <= R ) { PushTag(root, l, r, x); return ; }
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( L <= Mid ) Modify1(lson, l, Mid, L, R, x);
    if ( Mid < R ) Modify1(rson, Mid + 1, r, L, R, x);
    PushUp(root);
}

inline void Modify2(int root, int l, int r, int L, int R, pii x)
{
    if ( Tree[root].sum1 + Tree[root].sum2 == 0 ) return ;
    if ( l == r ) 
    {
        Tree[root].sum1 = Tree[root].sum2 = 0;
        REP(i, 0, 3) Tree[root].prime1[i] = Tree[root].prime2[i] = 0;
        bool flag = len(x) == 1;
        x = Tree[root].lazy * x;
        if ( flag || len(x) < INF ) Set.insert(node(l, l, x));
        return ;
    }
    int Mid = l + r >> 1; PushDown(root, l, r);
    if ( L <= Mid ) Modify2(lson, l, Mid, L, R, x);
    if ( Mid < R ) Modify2(rson, Mid + 1, r, L, R, x);
    PushUp(root);
}

inline void print(int root, int l, int r)
{
    cout << l << " " << r << " " << Tree[root].prime1[0] << endl;
    if ( l == r && Tree[root].prime1[0] ) 
    {
        cout << Tree[root].lazy.x << " " << Tree[root].lazy.y << endl;
    }
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    print(lson, l, Mid);
    print(rson, Mid + 1, r);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) 
    {
        // print(root, l, r);
        return Tree[root].prime1[0];
    }
    int Mid = l + r >> 1, ret = 0; PushDown(root, l, r);
    if ( L <= Mid ) ret += Query(lson, l, Mid, L, R);
    if ( Mid < R ) ret += Query(rson, Mid + 1, r, L, R);
    return ret;
}

signed main()
{
    freopen("prime.in", "r", stdin);
    freopen("prime.out", "w", stdout);
    INIT(maxm - 10);
    scanf("%lld%lld", &n, &q);
    REP(i, 1, n) 
    { 
        scanf("%lld%lld", &a[i].x, &a[i].y); 
        if ( check(a[i]) ) Modify1(1, 1, n, i, i, a[i]);
        else Set.insert(node(i, i, a[i])); 
    }
    int cnt = 0;
    while ( q -- ) 
    {
        int op, l, r, x, y; scanf("%lld%lld%lld", &op, &l, &r);
        if ( op == 1 ) 
        {
            scanf("%lld%lld", &x, &y);
            auto itr = Split(r + 1), itl = Split(l);
            Set.erase(itl, itr);
            if ( check(pii(x, y)) ) Modify1(1, 1, n, l, r, pii(x, y)); 
            else { Set.insert(node(l, r, pii(x, y))); Modify1(1, 1, n, l, r, pii(0, 0)); }
        }
        if ( op == 2 ) 
        {
            scanf("%lld%lld", &x, &y);
            p.clear();
            auto itr = Split(r + 1), itl = Split(l);
            for ( auto it = itl; it != itr; )
            {
                if ( it -> r < l || it -> l > r ) break ;
                it -> val = it -> val * pii(x, y);
                if ( len(pii(x, y)) != 1 && len(it -> val) >= INF ) it -> val = pii(0, 0);
                if ( check(it -> val) )
                {
                    p.push_back(*it);
                    auto x = it; ++ it;
                    Set.erase(x); 
                }
                else ++ it;
            }
            Modify2(1, 1, n, l, r, pii(x, y));
            for ( auto it : p ) Modify1(1, 1, n, it.l, it.r, it.val);
        }
        if ( op == 3 ) 
        {
            // ++ cnt;
            ans = Query(1, 1, n, l, r);
            auto itr = Split(r + 1), itl = Split(l);
            if ( cnt == 108 ) 
            {
                cout << l << " " << r << endl;
                for ( auto it = itl; it != itr; ++ it )
                {
                    if ( it -> r < l || it -> l > r ) break ;
                    cout << it -> l << " " << it -> r << " " << it -> val.x << " " << it -> val.y << " ";
                    if ( Check(it -> val) ) cout << it -> r - it -> l + 1;
                    cout << endl;
                }
            }
            for ( auto it = itl; it != itr; ++ it )
            {
                if ( it -> r < l || it -> l > r ) break ;
                if ( Check(it -> val) ) ans += it -> r - it -> l + 1;
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}
