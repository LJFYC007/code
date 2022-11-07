#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>

const int maxn = 2e5 + 10;

int n, m, son[maxn][2], Root[maxn], tot;
vector<pii> p[maxn];
struct node { int lson, rson, Max, Min, tag1; bool tag2; } Tree[maxn << 7];

#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson

inline void PushUp(int root)
{
    Tree[root].Min = min(Tree[ls(root)].Min, Tree[rs(root)].Min);
    Tree[root].Max = max(Tree[ls(root)].Max, Tree[rs(root)].Max);
}

inline void PushTag1(int &root, int val) 
{
    if ( !root ) root = ++ tot; 
    Tree[root].Max += val; Tree[root].Min += val; 
    if ( Tree[root].tag2 ) val = -val;
    Tree[root].tag1 += val;
}

inline void PushTag2(int &root)
{
    if ( !root ) root = ++ tot;
    int x = Tree[root].Min, y = Tree[root].Max;
    Tree[root].Max = -x; Tree[root].Min = -y; Tree[root].tag2 ^= 1;
}

inline void PushDown(int root)
{
    if ( Tree[root].tag1 ) { PushTag1(ls(root), Tree[root].tag1); PushTag1(rs(root), Tree[root].tag1); Tree[root].tag1 = 0; }
    if ( Tree[root].tag2 ) { PushTag2(ls(root)); PushTag2(rs(root)); Tree[root].tag2 = 0; }
}

inline void Modify(int &root, int l, int r, int L, int R, int val)
{
    if ( !root ) root = ++ tot;
    if ( L <= l && r <= R ) { PushTag1(root, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(ls(root), l, Mid, L, R, val);
    if ( Mid < R ) Modify(rs(root), Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].Min;
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) return Query(ls(root), l, Mid, pos);
    return Query(rs(root), Mid + 1, r, pos);
}

inline int Merge(int p, int q, int l, int r)
{
    if ( Tree[p].Max == Tree[p].Min && (Tree[p].Min <= Tree[q].Min || Tree[p].Min >= Tree[q].Max) ) 
    {
        int val = Tree[p].Min;
        if ( Tree[q].Min >= val ) PushTag1(q, -val);
        else if ( Tree[q].Max <= val ) { PushTag2(q); PushTag1(q, val); }
        return q;
    }
    if ( Tree[q].Max == Tree[q].Min && (Tree[q].Min <= Tree[p].Min || Tree[q].Min >= Tree[p].Max) ) 
    {
        int val = Tree[q].Min;
        if ( Tree[p].Min >= val ) PushTag1(p, -val);
        else if ( Tree[p].Max <= val ) { PushTag2(p); PushTag1(p, val); }
        return p;
    }
    int Mid = l + r >> 1, root = ++ tot; PushDown(p); PushDown(q);
    ls(root) = Merge(ls(p), ls(q), l, Mid);
    rs(root) = Merge(rs(p), rs(q), Mid + 1, r);
    PushUp(root); return root; 
}

inline void Solve(int x)
{
    int u = son[x][0], v = son[x][1];
    if ( u ) 
    {
        Solve(u); Solve(v);
        Root[x] = Merge(Root[u], Root[v], 1, m);
    }
    else Root[x] = ++ tot;
    for ( int i = 0; i < p[x].size(); ++ i ) 
    {
        int val = p[x][i].first, l = p[x][i].second, r = i + 1 == p[x].size() ? m : p[x][i + 1].second - 1;
        if ( l <= r ) Modify(Root[x], 1, m, l, r, val);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { int x; scanf("%d", &x); p[i].push_back(pii(x, 1)); }
    REP(i, 1, (n - 1) / 2) scanf("%d%d", &son[i][0], &son[i][1]);
    REP(i, 1, m) { int x, y; scanf("%d%d", &x, &y); p[x].push_back(pii(y, i)); }
    Solve(1);  
    REP(i, 1, m) printf("%d\n", Query(Root[1], 1, m, i));
    return 0;
}