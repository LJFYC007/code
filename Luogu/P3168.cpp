/***************************************************************
	File name: P3168.cpp
	Author: ljfcnyali
	Create time: 2019年07月13日 星期六 09时43分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r
typedef long long LL;

const int maxn = 8000010;
const int maxm = 100010;

LL n, m, Root[maxm], tot, ans = 1, Max;
vector<LL> a[maxm];

struct node
{
    LL l, r, size, sum, val;
} Tree[maxn];

inline int Build(int l, int r)
{
    int root = ++ tot;
    ls(root) = rs(root) = Tree[root].size = Tree[root].sum = Tree[root].val = 0;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    ls(root) = Build(l, Mid);
    rs(root) = Build(Mid + 1, r);
    return root;
}

inline int Update(int now, int l, int r, int val, int opt)
{
    int root = ++ tot; Tree[root] = Tree[now];
    Tree[root].sum += val; Tree[root].size += opt;
    if ( l == r ) { Tree[root].val += opt; return root; }
    int Mid = l + r >> 1;
    if ( abs(val) <= Mid ) ls(root) = Update(ls(root), l, Mid, val, opt);
    else rs(root) = Update(rs(root), Mid + 1, r, val, opt);
    return root;
}

inline LL Query(int root, int l, int r, int k)
{
    if ( l == r ) 
    {
        if ( k < Tree[root].size ) return l * k;
        return Tree[root].size * l;
    }
    LL Mid = l + r >> 1, sum = Tree[ls(root)].size + Tree[root].val;
    if ( k <= sum ) return Query(ls(root), l, Mid, k);
    else return Tree[ls(root)].sum + Tree[root].val * Mid + Query(rs(root), Mid + 1, r, k - sum);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n)
    {
        LL s, t, p; scanf("%lld%lld%lld", &s, &t, &p);
        a[s].push_back(p); a[t + 1].push_back(-p);
        Max = max(Max, p);
    }
    REP(i, 1, m) 
    {
        Root[i] = Root[i - 1];
        REP(j, 0, a[i].size() - 1)
        {
            int opt = 1;
            if ( a[i][j] < 0 ) opt = -1;
            Root[i] = Update(Root[i], 1, Max, a[i][j], opt);
        }
    }
    REP(i, 1, m)
    {
        LL x, a, b, c, k; scanf("%lld%lld%lld%lld", &x, &a, &b, &c);
        k = 1 + (a * ans + b) % c;
        printf("%lld\n", ans = Query(Root[x], 1, Max, k));
    }
    return 0;
}
