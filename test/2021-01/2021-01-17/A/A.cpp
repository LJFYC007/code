/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年01月17日 星期日 08时52分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 5e5 + 10;

int n, m, q, a[maxn];
LL b[maxn];
struct node { int Min, Max, tag1; LL sum, len, tag2; } Tree[maxn << 2];

inline void PushUp(int root)
{
    Tree[root].sum = Tree[lson].sum + Tree[rson].sum; 
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
}

inline void Build(int root, int l, int r)
{
    Tree[root].len = r - l + 1;
    if ( l == r ) { Tree[root].Min = Tree[root].Max = a[l]; return ; } 
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline void PushTag1(int root, int val) { Tree[root].tag1 = Tree[root].Min = Tree[root].Max = val; Tree[root].tag2 = Tree[root].sum = 0; }

inline void PushTag2(int root, LL val) { Tree[root].tag2 += val; Tree[root].sum += val * Tree[root].len; } 

inline void PushDown(int root)
{
    if ( Tree[root].tag1 ) { PushTag1(lson, Tree[root].tag1); PushTag1(rson, Tree[root].tag1); Tree[root].tag1 = 0; } 
    if ( Tree[root].tag2 ) { PushTag2(lson, Tree[root].tag2); PushTag2(rson, Tree[root].tag2); Tree[root].tag2 = 0; } 
}

inline void Modify1(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R && Tree[root].Min == Tree[root].Max ) { b[Tree[root].Min] += Tree[root].sum; PushTag1(root, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify1(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify1(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline void Modify2(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag2(root, val); return ; } 
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify2(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify2(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &q); REP(i, 1, n) scanf("%d", &a[i]);
    Build(1, 1, n);
    while ( q -- ) 
    {
        int op, l, r, x; scanf("%d%d%d%d", &op, &l, &r, &x);
        if ( op == 1 ) Modify1(1, 1, n, l, r, x);
        else Modify2(1, 1, n, l, r, x);
    }
    Modify1(1, 1, n, 1, n, 0);
    REP(i, 1, m) printf("%lld\n", b[i]);
    return 0;
}
