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

int n, q, a[maxn];
set<int> Col[maxn];
struct node 
{ 
    multiset<int> Set; 
    int Max, sum, ans, lazy, Min, lMax, rMax, Fuck; 
} Tree[maxn << 2];

inline void PushTag(int root, int val)
{
    Tree[root].Min += val; Tree[root].lazy += val;
    Tree[root].ans = Tree[root].Min ? Tree[root].Max : Tree[root].sum;
}

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    PushTag(lson, Tree[root].lazy);
    PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void PushUp(int root)
{
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
    if ( Tree[lson].Min < Tree[rson].Min ) 
    {
        Tree[root].lMax = Tree[lson].lMax;
        Tree[root].rMax = max(Tree[rson].Max, Tree[lson].rMax);
        Tree[root].sum = Tree[lson].sum - Tree[lson].rMax + Tree[root].rMax;
        Tree[root].Fuck = Tree[lson].Fuck;
    }
    else if ( Tree[rson].Min < Tree[lson].Min ) 
    {
        Tree[root].lMax = max(Tree[lson].Max, Tree[rson].lMax);
        Tree[root].rMax = Tree[rson].rMax;
        Tree[root].sum = Tree[rson].sum - Tree[rson].lMax + Tree[root].lMax;
        Tree[root].Fuck = Tree[rson].Fuck;
    }
    else 
    {
        Tree[root].lMax = Tree[lson].lMax;
        Tree[root].rMax = Tree[rson].rMax;
        Tree[root].sum = Tree[lson].sum + Tree[rson].sum - min(Tree[lson].rMax, Tree[rson].lMax);
        Tree[root].Fuck = Tree[lson].Fuck + Tree[rson].Fuck;
        if ( Tree[lson].rMax == 0 && Tree[rson].lMax == 0 ) ++ Tree[root].Fuck;
    }
    Tree[root].ans = Tree[root].Min ? Tree[root].Max : Tree[root].sum;
}

inline void Build(int root, int l, int r)
{
    Tree[root].Fuck = r - l;
    if ( l == r ) return ;
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
}

inline void Modify1(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { PushTag(root, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify1(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify1(rson, Mid + 1, r, L, R, val);
    PushUp(root);
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
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) Modify2(lson, l, Mid, pos, val);
    else Modify2(rson, Mid + 1, r, pos, val);
    PushUp(root);
}

inline void Insert(int x)
{
    if ( Col[x].size() <= 1 ) return ;
    int l = *Col[x].begin(), r = *(-- Col[x].end()) - 1;
    Modify1(1, 0, n, l, r, 1);
    Modify2(1, 0, n, l, Col[x].size());
}

inline void Delete(int x)
{
    if ( Col[x].size() <= 1 ) return ;
    int l = *Col[x].begin(), r = *(-- Col[x].end()) - 1;
    Modify1(1, 0, n, l, r, -1);
    Modify2(1, 0, n, l, -Col[x].size());
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &q); 
    REP(i, 1, n) { scanf("%d", &a[i]); Col[a[i]].insert(i); }
    Build(1, 0, n);
    REP(i, 1, 200000) Insert(i);
    printf("%d\n", n - Tree[1].Fuck - Tree[1].ans);
    while ( q -- ) 
    {
        int pos, col; scanf("%d%d", &pos, &col);
        Delete(a[pos]); Col[a[pos]].erase(pos); Insert(a[pos]);
        a[pos] = col;
        Delete(a[pos]); Col[a[pos]].insert(pos); Insert(a[pos]);
        printf("%d\n", n - Tree[1].Fuck - Tree[1].ans);
    }
    return 0;
}
