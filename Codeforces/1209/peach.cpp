/***************************************************************
	File name: G.cpp
	Author: ljfcnyali
	Create time: 2020年10月14日 星期三 16时08分45秒
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

const int maxn = 4e5 + 10;

int n, q, a[maxn], ans;
struct node 
{ 
    int l, r; mutable int val; 
    bool operator < (const node &a) const { return l < a.l; }
    node(int a = 0, int b = 0, int c = 0) { l = a; r = b; val = c; } 
} ;
set<node> Set;
set<int> Col[maxn];
struct Node { multiset<int> Set; int Max, lazy, Min; bool tag; } Tree[maxn << 2];

inline void PushTag(int root, int val)
{
    Tree[root].Min += val; Tree[root].lazy += val;
    Tree[root].tag = Tree[root].Min != 0;
}

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    PushTag(lson, Tree[root].lazy);
    PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Modify1(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify1(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify1(rson, Mid + 1, r, L, R, val);
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
    Tree[root].tag = Tree[root].Min != 0;
}

inline void Modify2(int root, int l, int r, int pos, int val)
{
    if ( l == r ) 
    { 
        if ( val > 0 ) Tree[root].Set.insert(val); 
        else { auto it = Tree[root].Set.lower_bound(-val); Tree[root].Set.erase(it); }
        Tree[root].Max = Tree[root].Set.size() ? *(-- Tree[root].Set.end()) : 0; 
        return ; 
    }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify2(lson, l, Mid, pos, val);
    else Modify2(rson, Mid + 1, r, pos, val);
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
}

inline bool Check(int root, int l, int r, int L, int R)
{
    if ( Tree[root].tag || (L <= l && r <= R) ) return Tree[root].tag;
    int Mid = l + r >> 1; bool op = true; PushDown(root);
    if ( L <= Mid ) op &= Check(lson, l, Mid, L, R);
    if ( Mid < R ) op &= Check(rson, Mid + 1, r, L, R);
    return op;
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].Max;
    int Mid = l + r >> 1, ret = 0;
    if ( L <= Mid ) ret = max(ret, Query(lson, l, Mid, L, R));
    if ( Mid < R ) ret = max(ret, Query(rson, Mid + 1, r, L, R));
    return ret;
}

inline void change1(int l, int r)
{
    auto it = Set.lower_bound(node(l));
    ans -= (r - l) / 2 + 2 - it -> val;
    Set.erase(it);
}

inline void change2(int l, int r)
{
    int x = Query(1, 1, n + n, l, r);
    ans += (r - l) / 2 + 2 - Query(1, 1, n + n, l, r);
    Set.insert(node(l, r, x));
}

inline void Insert(int x)
{
    if ( Col[x].size() <= 1 ) return ;
    int l = *Col[x].begin() * 2 + 1, r = *(-- Col[x].end()) * 2 - 1;
    Modify1(1, 1, n + n, l, r, 1);
    Modify2(1, 1, n + n, l, Col[x].size());

    auto it = Set.lower_bound(node(l + 1));
    while ( it != Set.end() && r >= it -> l )  
    {
        r = max(r, it -> r);
        change1(it -> l, it -> r);
        it = Set.lower_bound(node(l + 1)); 
    }
    while ( it != Set.begin() ) 
    {
        -- it;
        if ( l <= it -> r ) { l = it -> l; r = max(r, it -> r); change1(it -> l, it -> r); }
        else break ;
        it = Set.lower_bound(node(l + 1)); 
    }
    change2(l, r);
}

inline void Delete(int x)
{
    if ( Col[x].size() <= 1 ) return ;  
    int l = *Col[x].begin() * 2 + 1, r = *(-- Col[x].end()) * 2 - 1;
    Modify1(1, 1, n + n, l, r, -1);
    Modify2(1, 1, n + n, l, -Col[x].size());

    auto it = -- Set.lower_bound(node(l + 1));
    l = it -> l; r = it -> r; change1(l, r);

    for ( int posl = l, posr; posl <= r; posl = posr + 1 ) 
    {
        int L = posl, R = r; posr = -1; 
        while ( L <= R ) 
        {
            int Mid = L + R >> 1;
            if ( Check(1, 1, n + n, posl, Mid) ) { posr = Mid; L = Mid + 1; }
            else R = Mid - 1;
        }
        if ( posr == -1 ) { posr = posl; continue ; }
        change2(posl, posr);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &q); 
    REP(i, 1, n) { scanf("%d", &a[i]); Col[a[i]].insert(i); }
    REP(i, 1, 200000) Insert(i);
    printf("%d\n", ans);
    while ( q -- ) 
    {
        int pos, col; scanf("%d%d", &pos, &col);
        Delete(a[pos]); Col[a[pos]].erase(pos); Insert(a[pos]);
        a[pos] = col;
        Delete(a[pos]); Col[a[pos]].insert(pos); Insert(a[pos]);
        printf("%d\n", ans);
    }
    return 0;
}
