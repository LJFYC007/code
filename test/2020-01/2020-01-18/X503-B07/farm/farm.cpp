/***************************************************************
	File name: farm.cpp
	Author: ljfcnyali
	Create time: 2020年01月18日 星期六 09时12分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
typedef long long LL;

const int maxn = 3e5 + 10;

int w, h, n, N, t, ans, ret, Root;
struct node { int x, y; bool operator < (const node &a) const { return y > a.y; } } a[maxn];
struct Node { int lson, rson, lazy, Max; } Tree[maxn << 2];
struct NODE { int l, r, x; } p1;
stack<NODE> Stack1, Stack2;

inline void PushTag(int &root, int val)
{
	if ( !root ) root = ++ ret;
	Tree[root].Max += val; Tree[root].lazy += val;
}

inline void PushUp(int root) { Tree[root].Max = max(Tree[ls(root)].Max, Tree[rs(root)].Max); }

inline void PushDown(int root)
{
	if ( !Tree[root].lazy ) return ;
	PushTag(ls(root), Tree[root].lazy);
	PushTag(rs(root), Tree[root].lazy);
	Tree[root].lazy = 0;
}

inline void Modify(int &root, int l, int r, int L, int R, int val)
{
    if ( !root ) root = ++ ret;
    if ( L <= l && r <= R ) { PushTag(root, val); return ; }
	PushDown(root);
	int Mid = l + r >> 1;
	if ( L <= Mid ) Modify(ls(root), l, Mid, L, R, val);
	if ( Mid < R ) Modify(rs(root), Mid + 1, r, L, R, val);
	PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( !root ) return 0;
	if ( L <= l && r <= R ) return Tree[root].Max;
	PushDown(root);
	int Mid = l + r >> 1, Max = 0;
	if ( L <= Mid ) Max = max(Max, Query(ls(root), l, Mid, L, R));
	if ( Mid < R ) Max = max(Max, Query(rs(root), Mid + 1, r, L, R));
    return Max;
}

inline void Insert(int L, int R)
{
    while ( !Stack1.empty() && L > Stack1.top().x )
    {
        p1 = Stack1.top(); Stack1.pop();
        Modify(Root, 1, N, p1.l, p1.r, -(w / 2 - p1.x));
    }
    int tot = 1;
    if ( !Stack1.empty() ) tot = Stack1.top().r + 1;
    Modify(Root, 1, N, tot, t, w / 2 - L);
    p1.l = tot; p1.r = t; p1.x = L;
    Stack1.push(p1);

    while ( !Stack2.empty() && R < Stack2.top().x )
    {
        NODE p1 = Stack2.top(); Stack2.pop();
        Modify(Root, 1, N, p1.l, p1.r, -(p1.x - w / 2));
    }
    tot = 1;
    if ( !Stack2.empty() ) tot = Stack2.top().r + 1;
    Modify(Root, 1, N, tot, t, R - w / 2);
    p1.l = tot; p1.r = t; p1.x = R;
    Stack2.push(p1);
}

inline void Solve()
{
    N = t = 0;
	while ( !Stack1.empty() ) Stack1.pop();
	while ( !Stack2.empty() ) Stack2.pop();
	mem(Tree); ret = Root = 1;
    sort(a + 1, a + n + 1);
    a[n + 1].y = -1; a[0].y = h;
    REP(i, 1, n) if ( a[i].y != a[i + 1].y ) ++ N;
    REP(i, 1, n) ans = max(ans, 2 * (w + a[i - 1].y - a[i].y));
    REP(i, 1, n)
    {
        if ( a[i].y == h ) continue ;
        int x = a[i - 1].y - a[i].y; 
        ++ t; Modify(Root, 1, N, 1, t, x);
        ans = max(ans, 2 * Query(1, 1, N, 1, t));
        int L = 0, R = w;
        while ( a[i].y == a[i + 1].y && i <= n )
        {
            if ( a[i].x < w / 2 ) L = max(L, a[i].x);
            if ( a[i].x > w / 2 ) R = min(R, a[i].x);
            if ( a[i].x == w / 2 ) return ;
            ++ i;
        }
        if ( a[i].x < w / 2 ) L = max(L, a[i].x);
        if ( a[i].x > w / 2 ) R = min(R, a[i].x);
        if ( a[i].x == w / 2 ) return ;
        Insert(L, R);
    }
    ans = max(ans, (w + a[n].y) * 2); 
}

int main()
{
    freopen("farm.in", "r", stdin);
    freopen("farm.out", "w", stdout);
    scanf("%d%d%d", &w, &h, &n);
    REP(i, 1, n) scanf("%d%d", &a[i].x, &a[i].y);
    Solve();
    REP(i, 1, n) swap(a[i].x, a[i].y); swap(w, h);
    Solve();
    printf("%d\n", ans);
    return 0;
}
