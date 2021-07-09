/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2020年07月24日 星期五 16时06分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 6e5 + 10;
const int INF = 0x3f3f3f3f;

int n, w, q, type, a[maxn], tot, ans;
struct node { int l, r, k, id; } Q[maxn];
struct Node { int lson, rson, sum; } Tree[maxn << 7];
set<int> Set[maxn];
vector<pii> Root[maxn];

inline int Modify2(int now, int l, int r, int pos, int val)
{
    int root = ++ tot; Tree[root] = Tree[now]; Tree[root].sum += val;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) ls(root) = Modify2(ls(root), l, Mid, pos, val);
    else rs(root) = Modify2(rs(root), Mid + 1, r, pos, val);
    return root;
}

inline int Query2(vector<int> p, vector<int> q, int l, int r, int k)
{
    if ( l == r ) 
    {
        int ret = 0;
        for ( auto i : p ) ret += Tree[i].sum; for ( auto i : q ) ret -= Tree[i].sum;
        return k <= ret ? l : n;
    }
    int Mid = l + r >> 1, ret = 0;
    for ( auto i : p ) ret += Tree[ls(i)].sum; for ( auto i : q ) ret -= Tree[ls(i)].sum;
    if ( k <= ret ) 
    {
        for ( auto &i : p ) i = ls(i); for ( auto &i : q ) i = ls(i);
        return Query2(p, q, l, Mid, k);
    }
    else 
    {
        for ( auto &i : p ) i = rs(i); for ( auto &i : q ) i = rs(i);
        return Query2(p, q, Mid + 1, r, k - ret);
    }
}

inline int Find(int i, int t)
{
    auto it = -- upper_bound(Root[i].begin(), Root[i].end(), pii(t, INF));
    return (*it).second;
}

inline int lowbit(int x) { return x & -x; }

inline void Modify1(int x, int pos, int val, int t)
{
    for ( int i = x; i <= n; i += lowbit(i) )
    {
        int x = Root[i].back().second;
        if ( Root[i].back().first == t ) Root[i].pop_back();
        x = Modify2(x, 0, n - 1, pos, val);
        Root[i].push_back(pii(t, x));
    }
}

inline int Query1(int l, int r, int k, int t)
{
    vector<int> p, q;
    for ( int i = r; i > 0; i -= lowbit(i) ) p.push_back(Find(i, t));
    for ( int i = l - 1; i > 0; i -= lowbit(i) ) q.push_back(Find(i, t));
    return Query2(p, q, 0, n - 1, k);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &w, &q, &type);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n) Root[i].push_back(pii(0, 0));
    REP(i, 1, n)
    {
        Set[a[i]].insert(i); Modify1(i, a[i], 1, i);
        if ( Set[a[i]].size() == w + 1 ) Modify1(*Set[a[i]].begin(), a[i], -w - 1, i);
        else if ( Set[a[i]].size() == w + 2 ) 
        {
            auto it = Set[a[i]].begin(); Modify1(*it, a[i], w, i); 
            Set[a[i]].erase(it); Modify1(*Set[a[i]].begin(), a[i], -w - 1, i);
        }
    }
    REP(i, 1, q)
    {
        int L, R, k; scanf("%d%d%d", &L, &R, &k);
        L ^= ans * type; R ^= ans * type; k ^= ans * type;
        ans = Query1(L, R, k, R);
        printf("%d\n", ans);
    }
    return 0;
}
