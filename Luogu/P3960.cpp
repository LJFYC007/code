/***************************************************************
	File name: P3960.cpp
	Author: ljfcnyali
	Create time: 2019年07月08日 星期一 14时41分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r
typedef long long LL;

const int maxn = 15000010;

struct node
{
    LL l, r, size, rank;
} Tree[maxn];

LL n, m, q, Root[maxn], cnt, l[maxn], r[maxn];

inline LL New_Node(LL L, LL R)
{
    ++ cnt;
    l[cnt] = L; r[cnt] = R;
    ls(cnt) = rs(cnt) = 0;
    Tree[cnt].size = R - L + 1;
    Tree[cnt].rank = rand();
    return cnt;
}

inline void Push_up(LL root) 
{ 
    Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + r[root] - l[root] + 1; 
}

inline void Merge(LL &root, LL a, LL b)
{
    if ( !a || !b ) { root = a + b; return ; }
    if ( Tree[a].rank < Tree[b].rank ) { root = a; Merge(rs(a), rs(a), b); }
    else { root = b; Merge(ls(b), a, ls(b)); }
    Push_up(root);
}

inline void New(LL root, LL k)
{
    if ( k >= r[root] - l[root] + 1 ) return ;
    LL x = l[root] + k - 1;
    LL a = New_Node(x + 1, r[root]);
    r[root] = x;
    Merge(rs(root), a, rs(root));
    Push_up(root);
}

inline void Split(LL root, LL &a, LL &b, LL k)
{
    if ( !root ) { a = b = 0; return ; }
    if ( Tree[ls(root)].size >= k )
    {
        b = root;
        Split(ls(b), a, ls(b), k);
    }
    else
    {
        New(root, k - Tree[ls(root)].size);
        a = root;
        Split(rs(a), rs(a), b, k - Tree[ls(root)].size - (r[root] - l[root] + 1));
    }
    Push_up(root);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &q);
    REP(i, 1, n) Merge(Root[i], Root[i], New_Node((i - 1) * m + 1, i * m - 1));
    REP(i, 1, n) Merge(Root[n + 1], Root[n + 1], New_Node(i * m, i * m)); 
    while ( q -- )
    {
        LL x, y; scanf("%lld%lld", &x, &y);
        if ( y == m ) 
        {
            LL a, b, c;
            Split(Root[n + 1], a, b, x);
            Split(a, a, c, x - 1);
            printf("%lld\n", l[c]);
            Merge(Root[n + 1], a, b);
            Merge(Root[n + 1], Root[n + 1], c);
            continue ; 
        }
        LL a, b, c, s, t;
        Split(Root[x], a, b, y);
        Split(a, a, c, y - 1);
        printf("%lld\n", l[c]);
        s = c;
        Merge(Root[x], a, b);
        Split(Root[n + 1], a, b, x);
        Split(a, a, c, x - 1);
        t = c;
        Merge(Root[n + 1], a, b);
        Merge(Root[x], Root[x], t);
        Merge(Root[n + 1], Root[n + 1], s);
    }
    return 0;
}
