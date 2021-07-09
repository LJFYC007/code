/***************************************************************
	File name: P5445.cpp
	Author: ljfcnyali
	Create time: 2019年10月22日 星期二 21时49分03秒
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

const int maxn = 300010;
const int N = 300000;

int n, m, Root[maxn], tot;
set<pii> Set;
char s[maxn];
struct node { int lazy, val, lson, rson; } Tree[maxn];

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    int x = Tree[root].lazy; Tree[root].lazy = 0;
    if ( !ls(root) ) ls(root) = ++ tot;
    if ( !rs(root) ) rs(root) = ++ tot;
    Tree[ls(root)].lazy += x; Tree[ls(root)].val += x; 
    Tree[rs(root)].lazy += x; Tree[rs(root)].val += x;
}

inline void Modify2(int &root, int l, int r, int L, int R, int val)
{
    if ( !root ) root = ++ tot; 
    if ( L <= l && r <= R ) 
    { 
        Tree[root].val += val; Tree[root].lazy += val;
        return ;
    }
    PushDown(root);
    int Mid = l + r >> 1;
    if ( L <= Mid ) Modify2(ls(root), l, Mid, L, R, val);
    if ( Mid < R ) Modify2(rs(root), Mid + 1, r, L, R, val);
}

inline int Query2(int root, int l, int r, int pos)
{
    if ( !root ) return 0;
    if ( l == r ) return Tree[root].val;
    PushDown(root);
    int Mid = l + r >> 1;
    if ( pos <= Mid ) return Query2(ls(root), l, Mid, pos);
    return Query2(rs(root), Mid + 1, r, pos);
}

inline int lowbit(int x) { return x & -x; }

inline void Modify1(int pos, int L, int R, int val)
{
    for ( int i = pos; i <= n; i += lowbit(i) )
        Modify2(Root[i], 1, n, L, R, val);
}

inline int Query1(int pos, int x)
{
    int sum = 0;
    for ( int i = pos; i > 0; i -= lowbit(i) ) 
        sum += Query2(Root[i], 1, n, x);
    return sum;
}

inline void Solve(int Lx, int Ly, int Rx, int Ry, int val)
{
    Modify1(Ly, Lx, Rx, val); 
    Modify1(Ry + 1, Lx, Rx, -val);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);
    REP(i, 1, n) Root[i] = ++ tot;
    for ( int i = 1; i <= n; ++ i ) 
    {
        if ( s[i] == '0' ) continue ;
        int L = i, R;
        while ( s[i] == '1' ) ++ i;
        R = i - 1;
        Set.insert(make_pair(L, R));
        Solve(L, L, R, R, m);
    }
    REP(i, 1, m)
    {
        scanf("%s", s + 1);
        if ( s[1] == 'q' ) 
        {
            int l, r; scanf("%d%d", &l, &r); -- r;
            int ans = Query1(l, r);
            auto it = -- Set.upper_bound(make_pair(l, r));
            if ( it -> first <= l && r <= it -> second ) ans -= m - i;
            printf("%d\n", ans);
            continue ;
        }
        int x; scanf("%d", &x);
        if ( s[x] == '0' ) 
        {
            s[x] = '1';
            auto it1 = -- Set.upper_bound(make_pair(x, x)), it2 = Set.lower_bound(make_pair(x, x));
            const int L = it1 -> first, R = it2 -> second;
            Set.erase(make_pair(L, x)); Set.erase(make_pair(x + 1, R));
            Set.insert(make_pair(L, R));
            Solve(L, x + 1, x, R, m - i);
        }
        else 
        {
            s[x] = '0';
            auto it = -- Set.upper_bound(make_pair(x, x));
            const int L = it -> first, R = it -> second;
            Set.erase(it);
            Set.insert(make_pair(L, x)); Set.insert(make_pair(x + 1, R));
            Solve(L, x + 1, x, R, -m + i);
        }
    }
    return 0;
}
