/***************************************************************
	File name: D2.cpp
	Author: ljfcnyali
	Create time: 2020年11月16日 星期一 11时31分45秒
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

const int maxn = 2e5 + 10;

int n, a[maxn], t[maxn], val, ans;
vector<int> p[maxn];
struct node { int Min, Max, lazy; } Tree[maxn << 2];

inline void PushTag(int root, int val) { Tree[root].Min += val; Tree[root].Max += val; Tree[root].lazy += val; }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
}

inline int Query1(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].Min;
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) return Query1(lson, l, Mid, pos);
    return Query1(rson, Mid + 1, r, pos);
}

inline int Query2(int root, int l, int r, int val)
{
    if ( l == r ) return l;
    int Mid = l + r >> 1; PushDown(root);
    if ( Tree[lson].Min <= val && val <= Tree[lson].Max ) return Query2(lson, l, Mid, val);
    return Query2(rson, Mid + 1, r, val);
}

inline int Query3(int root, int l, int r, int val)
{
    if ( l == r ) return l;
    int Mid = l + r >> 1; PushDown(root);
    if ( Tree[rson].Min <= val && val <= Tree[rson].Max ) return Query3(rson, Mid + 1, r, val);
    return Query3(lson, l, Mid, val);
}

inline void Solve(int it)
{
    int x = Query1(1, 0, n, it);
    int L = Query2(1, 0, n, x), R = Query3(1, 0, n, x);
    ans = max(ans, R - L);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &a[i]); ++ t[a[i]]; p[a[i]].push_back(i); }
    REP(i, 1, n) if ( t[i] > t[val] ) val = i;
    REP(i, 1, n) if ( t[i] == t[val] && i != val ) { printf("%d\n", n); return 0; }
    for ( auto it : p[val] ) Modify(1, 0, n, it, n, 1);

    REP(i, 1, n)
    {
        if ( i == val || !t[i] ) continue ;
        for ( auto it : p[i] ) Modify(1, 0, n, it, n, -1);
        for ( auto it : p[i] ) { Solve(it); Solve(it - 1); }
        for ( auto it : p[i] ) Modify(1, 0, n, it, n, 1);
    }
    printf("%d\n", ans);
    return 0;
}
