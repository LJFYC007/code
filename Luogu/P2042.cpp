/***************************************************************
	File name: P2042.cpp
	Author: ljfcnyali
	Create time: 2019年09月06日 星期五 20时04分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 4000010;

struct node
{
    int lson, rson, size, lazy_sum, lazy, pre, suf, sum, cen, val, rank, flag;
} Tree[maxn];

int n, m, Root, tot;
char s[10];
stack<int> Rub;

inline int NewNode(int val)
{
    int root; 
    if ( !Rub.empty() ) { root = Rub.top(); Rub.pop(); }
    else root = ++ tot;
    ls(root) = rs(root) = 0; Tree[root].size = 1;
    Tree[root].lazy_sum = Tree[root].flag = Tree[root].lazy = 0;
    Tree[root].pre = Tree[root].suf = max(0, val);
    Tree[root].cen = Tree[root].sum = Tree[root].val = val;
    Tree[root].rank = rand();
    return root;
}

inline void PushUp(int root)
{
    Tree[root].size = Tree[ls(root)].size + Tree[rs(root)].size + 1;
    Tree[root].sum = Tree[ls(root)].sum + Tree[rs(root)].sum + Tree[root].val;
    Tree[root].pre = max(Tree[ls(root)].pre, Tree[ls(root)].sum + Tree[rs(root)].pre + Tree[root].val);
    Tree[root].suf = max(Tree[rs(root)].suf, Tree[rs(root)].sum + Tree[ls(root)].suf + Tree[root].val);
    Tree[root].pre = max(0, Tree[root].pre); Tree[root].suf = max(0, Tree[root].suf);
    Tree[root].cen = max(Tree[root].val, Tree[ls(root)].suf + Tree[rs(root)].pre + Tree[root].val);
    if ( ls(root) ) Tree[root].cen = max(Tree[root].cen, Tree[ls(root)].cen);
    if ( rs(root) ) Tree[root].cen = max(Tree[root].cen, Tree[rs(root)].cen);
}

inline void Update(int root)
{
    Tree[root].lazy ^= 1;
    swap(ls(root), rs(root)); swap(Tree[root].pre, Tree[root].suf);
}

inline void Cover(int root, int val)
{
    Tree[root].val = Tree[root].lazy_sum = val; Tree[root].sum = val * Tree[root].size;
    Tree[root].pre = Tree[root].suf = max(0, Tree[root].sum);
    Tree[root].cen = max(Tree[root].val, Tree[root].sum);
    Tree[root].flag = 1;
}

inline void PushDown(int root)
{
    if ( Tree[root].flag ) 
    {
        if ( ls(root) ) Cover(ls(root), Tree[root].lazy_sum);
        if ( rs(root) ) Cover(rs(root), Tree[root].lazy_sum);
        Tree[root].lazy_sum = Tree[root].flag = 0;
    }
    if ( Tree[root].lazy ) 
    {
        Tree[root].lazy ^= 1;
        if ( ls(root) ) Update(ls(root));
        if ( rs(root) ) Update(rs(root));
    }
}

inline void Merge(int &root, int a, int b)
{
    if ( !a || !b ) { root = a + b; return ; }
    PushDown(a); PushDown(b);
    if ( Tree[a].rank < Tree[b].rank ) { root = a; Merge(rs(a), rs(a), b); }
    else { root = b; Merge(ls(b), a, ls(b)); }
    PushUp(root);
}

inline void Split(int root, int &a, int &b, int k)
{
    if ( !root ) { a = b = 0; return ; }
    PushDown(root);
    if ( k <= Tree[ls(root)].size ) { b = root; Split(ls(b), a, ls(b), k); }
    else { a = root; Split(rs(a), rs(a), b, k - Tree[ls(a)].size - 1); }
    PushUp(root);
}

inline void Delete(int root) 
{
    if ( ls(root) ) Delete(ls(root));
    Rub.push(root);
    if ( rs(root) ) Delete(rs(root));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { int x; scanf("%d", &x); x = NewNode(x); Merge(Root, Root, x); }
    int a, b, c;
    while ( m -- )
    {
        scanf("%s", s);
        if ( s[0] == 'I' ) 
        {
            int pos, num; c = 0; scanf("%d%d", &pos, &num);
            REP(i, 1, num) { int x; scanf("%d", &x); x = NewNode(x); Merge(c, c, x); }
            Split(Root, a, b, pos); Merge(a, a, c); Merge(Root, a, b);
        }
        if ( s[0] == 'D' ) 
        {
            int pos, num; scanf("%d%d", &pos, &num);
            Split(Root, a, b, pos + num - 1); Split(a, a, c, pos - 1); Delete(c);
            Merge(Root, a, b);
        }
        if ( s[0] == 'M' && s[4] == '-' ) 
        {
            int pos, num, val; scanf("%d%d%d", &pos, &num, &val);
            Split(Root, a, b, pos + num - 1); Split(a, a, c, pos - 1); Cover(c, val);
            Merge(a, a, c); Merge(Root, a, b);
        }
        if ( s[0] == 'R' ) 
        {
            int pos, num; scanf("%d%d", &pos, &num);
            Split(Root, a, b, pos + num - 1); Split(a, a, c, pos - 1); Update(c);
            Merge(a, a, c); Merge(Root, a, b);
        }
        if ( s[0] == 'G' ) 
        {
            int pos, num; scanf("%d%d", &pos, &num);
            Split(Root, a, b, pos + num - 1); Split(a, a, c, pos - 1);
            printf("%d\n", Tree[c].sum);
            Merge(a, a, c); Merge(Root, a, b);
        }
        if ( s[0] == 'M' && s[3] == '-' )
            printf("%d\n", Tree[Root].cen);
    }
    return 0;
}
