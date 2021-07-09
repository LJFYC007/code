/***************************************************************
	File name: P3224.cpp
	Author: ljfcnyali
	Create time: 2019年07月15日 星期一 09时20分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r

const int maxn = 100010;

struct node
{
    int l, r, size;
} Tree[maxn << 5];

int Root[maxn], n, m, q, f[maxn], cnt, size[maxn], id[maxn];

inline int cha(int x) { return x == f[x] ? x : f[x] = cha(f[x]); }

inline int Update(int now, int l, int r, int val)
{
    int root = ++ cnt; Tree[root] = Tree[now];
    ++ Tree[root].size;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    if ( val <= Mid ) ls(root) = Update(ls(root), l, Mid, val);
    else rs(root) = Update(rs(root), Mid + 1, r, val);
    return root;
}

inline int Merge(int p, int q, int l, int r)
{
    if ( !p || !q ) return p + q; 
    Tree[p].size += Tree[q].size;
    if ( l == r ) return p;
    int Mid = l + r >> 1;
    ls(p) = Merge(ls(p), ls(q), l, Mid);
    rs(p) = Merge(rs(p), rs(q), Mid + 1, r);
    return p;
}

inline int Query(int root, int l, int r, int k)
{
    if ( l == r ) return l;
    int Mid = l + r >> 1, sum = Tree[ls(root)].size;
    if ( k <= sum ) return Query(ls(root), l, Mid, k);
    else return Query(rs(root), Mid + 1, r, k - sum);
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
        int x; scanf("%d", &x);
        Root[i] = Update(Root[i], 1, n, x);
        f[i] = id[x] = i;
    }
    REP(i, 1, m)
    {
        int x, y; scanf("%d%d", &x, &y);
        int fx = cha(x), fy = cha(y);
        if ( fx == fy ) continue ;
        if ( size[fx] == size[fy] ) ++ size[fx];
        if ( size[fx] < size[fy] ) swap(fx, fy);
        f[fy] = fx;
        Root[fx] = Merge(Root[fx], Root[fy], 1, n);
    }
    scanf("%d", &q);
    while ( q -- ) 
    {
        getchar();
        getchar(); char c = getchar();
        if ( c == 'B' ) 
        {
            int x, y; scanf("%d%d", &x, &y);
            int fx = cha(x), fy = cha(y);
            if ( fx == fy ) continue ;
            if ( size[fx] == size[fy] ) ++ size[fx];
            if ( size[fx] < size[fy] ) swap(fx, fy);
            f[fy] = fx;
            Root[fx] = Merge(Root[fx], Root[fy], 1, n);
        }
        else
        {
            int x, k; scanf("%d%d", &x, &k);
            int root = Root[cha(x)];
            if ( Tree[root].size < k ) puts("-1");
            else printf("%d\n", id[Query(root, 1, n, k)]);
        }
    }
    return 0;
}
