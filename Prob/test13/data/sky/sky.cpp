/***************************************************************
	File name: sky.cpp
	Author: ljfcnyali
	Create time: 2020年12月28日 星期一 15时42分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define x first
#define y second
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e18;

int n, f[maxn], ans;
pii a[maxn];
struct node { int x, y, w; node ( int a = 0, int b = 0, int c = 0 ) { x = a; y = b; w = c; } } ;
inline node max(node a, node b) { return a.w < b.w ? b : a; }
inline pii max(pii a, pii b) { return a.x > b.x ? a : b; }
inline pii min(pii a, pii b) { return a.x < b.x ? a : b; }
struct Node 
{ 
    int lazy, minn, num, len;
    pii Min, Max, pre, suf;
    node ans1, ans2, ans3; 
} Tree[maxn << 2];
bool vis[maxn];

inline void PushUp(int root) 
{
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
    Tree[root].pre = Tree[lson].pre; Tree[root].suf = Tree[rson].suf;
    if ( Tree[lson].minn > 0 ) Tree[root].pre = min(Tree[root].pre, Tree[rson].pre);
    if ( Tree[rson].minn > 0 ) Tree[root].suf = max(Tree[root].suf, Tree[lson].suf);

    Tree[root].minn = min(Tree[lson].minn, Tree[rson].minn);
    Tree[root].num = 0;
    if ( Tree[lson].minn == Tree[root].minn ) Tree[root].num += Tree[lson].num;
    if ( Tree[rson].minn == Tree[root].minn ) Tree[root].num += Tree[rson].num;

    Tree[root].ans1 = max(Tree[lson].ans1, Tree[rson].ans1); 
    Tree[root].ans1 = max(Tree[root].ans1, node(Tree[rson].Max.y, Tree[lson].Min.y, Tree[rson].Max.x - Tree[lson].Min.x));
    Tree[root].ans2 = max(Tree[lson].ans2, Tree[rson].ans2); 
    Tree[root].ans2 = max(Tree[root].ans2, node(Tree[lson].suf.y, Tree[rson].pre.y, Tree[lson].suf.x - Tree[rson].pre.x));
    Tree[root].ans3 = max(Tree[lson].ans3, Tree[rson].ans3);
    Tree[root].ans3 = max(Tree[root].ans3, node(Tree[lson].Max.y, Tree[rson].Min.y, Tree[lson].Max.x - Tree[rson].Min.x));
}

inline void PushTag(int root, int val) 
{ 
    Tree[root].lazy += val; Tree[root].minn += val; 
    if ( Tree[root].minn > 0 ) 
    { 
        Tree[root].pre = Tree[root].Min; Tree[root].suf = Tree[root].Max;
        Tree[root].ans2 = Tree[root].ans3;
    }
    else 
    {
        Tree[root].num = Tree[root].len; Tree[root].ans2 = node();
        Tree[root].pre = pii(INF, 0); Tree[root].suf = pii(-INF, 0); 
    }
}

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Modify(int root, int l, int r, int pos, int val)
{
    Tree[root].len = r - l + 1;
    if ( l == r ) 
    { 
        if ( val != -1 ) Tree[root].Min = Tree[root].Max = Tree[root].pre = Tree[root].suf = pii(val, l);
        else { Tree[root].Min = Tree[root].pre = pii(INF, l); Tree[root].Max = Tree[root].suf = pii(-INF, l); }
        if ( Tree[root].minn == 0 ) { Tree[root].pre = pii(INF, l); Tree[root].suf = pii(-INF, l); }
        Tree[root].num = 1;
        return ; 
    }
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
    PushUp(root);
}

inline void Maintain(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R && val + Tree[root].minn > 0 ) { PushTag(root, val); return ; }
    if ( L <= l && r <= R && Tree[root].num == Tree[root].len ) { PushTag(root, val); return ; } 
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Maintain(lson, l, Mid, L, R, val);
    if ( Mid < R ) Maintain(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].minn;  
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) return Query(lson, l, Mid, pos);
    return Query(rson, Mid + 1, r, pos);
}

signed main()
{
    scanf("%lld", &n); REP(i, 1, n) scanf("%lld%lld", &a[i].first, &a[i].second);
    sort(a + 1, a + n + 1); REP(i, 1, n) Modify(1, 1, n, i, a[i].second);
    REP(o, 1, n / 2)
    {
        node val1 = Tree[1].ans1, val2 = Tree[1].ans2;
        if ( !val1.w && !val2.w ) goto Next ;
        if ( val1.w > val2.w ) 
        {
            Modify(1, 1, n, val1.x, -1); Modify(1, 1, n, val1.y, -1);
            Maintain(1, 1, n, val1.y + 1, val1.x - 1, 1); ans += val1.w;
        }
        else 
        {
            Modify(1, 1, n, val2.x, -1); Modify(1, 1, n, val2.y, -1);
            Maintain(1, 1, n, val2.x, val2.y, -1); ans += val2.w;
        }
Next : ;
        printf("%lld\n", ans);
    }
    return 0;
}
