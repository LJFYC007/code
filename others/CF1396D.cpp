/***************************************************************
	File name: CF1396D.cpp
	Author: ljfcnyali
	Create time: 2020年09月14日 星期一 21时51分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 2e3 + 10;
const int Mod = 1e9 + 7;

int n, N1, N2, k, L, lst, p1[maxn], p2[maxn], ans;
struct node { int x, y, c; } a[maxn];
struct Node { int len, sum, lazy, val; } Tree[maxn << 2];
vector<pii> p, b[maxn];
multiset<int> Col[maxn];

inline void PushTag(int root, int val)
{
    Tree[root].sum = val * Tree[root].len; 
    Tree[root].lazy = Tree[root].val = val;
}

inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; Tree[root].val = Tree[lson].val; }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Build(int root, int l, int r)
{
    Tree[root].len = p1[r] - p1[l - 1]; Tree[root].sum = Tree[root].len * (L + 1); Tree[root].lazy = 0;
    if ( l == r ) { Tree[root].val = Tree[root].sum; return ; }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L > R ) return ;
    if ( L <= l && r <= R ) { PushTag(root, val); return ; } 
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Find(int root, int l, int r, int val)
{
    if ( l == r ) return Tree[root].val <= val ? l : 0;
    int Mid = l + r >> 1; PushDown(root);
    if ( Tree[rson].val > val ) return Find(lson, l, Mid, val);
    return Find(rson, Mid + 1, r, val);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &k, &L);
    REP(i, 1, n) 
    {
        scanf("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].c);
        ++ a[i].x; ++ a[i].y;
    }
    sort(a + 1, a + n + 1, [](node &a, node &b) { return a.x < b.x; });
    lst = 0; REP(i, 1, n) if ( a[i].x != lst ) { lst = p1[++ N1] = a[i].x; a[i].x = N1; } else a[i].x = N1;
    sort(a + 1, a + n + 1, [](node &a, node &b) { return a.y < b.y; });
    lst = 0; REP(i, 1, n) if ( a[i].y != lst ) { lst = p2[++ N2] = a[i].y; a[i].y = N2; } else a[i].y = N2;
    REP(i, 1, n) b[a[i].y].push_back(pii(a[i].x, a[i].c));
    REP(o, 1, N2) sort(b[o].begin(), b[o].end()); // , [](pii a, pii b) { return a.first < b.first; });

    p1[N1 + 1] = p2[N2 + 1] = L + 1;
    REP(i, 1, N2) 
    {
        p.clear(); 
        REP(o, 1, k) { Col[o].clear(); Col[o].insert(0); }
        Build(1, 1, N1); 

        REP(k, 1, n) if ( a[k].y >= i ) p.push_back(pii(a[k].x, a[k].c)); 
        sort(p.begin(), p.end());
        for ( auto k : p )
        {
            auto it = -- Col[k.second].end();
            Modify(1, 1, N1, *it + 1, k.first, p1[k.first]);
            Col[k.second].insert(k.first);
        }
        REP(o, 1, k) 
        { 
            auto it = -- Col[o].end();
            Modify(1, 1, N1, *it + 1, N1, L + 1); 
            Col[o].insert(N1 + 1); 
        }
        int ret = ((L + 1) * p1[N1] - Tree[1].sum) % Mod;
        ret = ret * (p2[i] - p2[i - 1]) % Mod;
        ret = ret * (p2[N2 + 1] - p2[N2]) % Mod;
        ans = (ans + ret) % Mod;

        for ( int j = N2 - 1; j >= i; -- j ) 
        {
            for ( auto it : b[j + 1] )              
            {
                auto pos = Col[it.second].lower_bound(it.first);
                auto l = pos, r = pos; -- l; ++ r;
                Modify(1, 1, N1, *l + 1, Find(1, 1, N1, p1[*r]), p1[*r]);
                Col[it.second].erase(pos);
            }

            ret = ((L + 1) * p1[N1] - Tree[1].sum) % Mod;
            ret = ret * (p2[i] - p2[i - 1]) % Mod;
            ret = ret * (p2[j + 1] - p2[j]) % Mod;
            ans = (ans + ret) % Mod;
        }
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
