/***************************************************************
	File name: P2794.cpp
	Author: ljfcnyali
	Create time: 2019年08月10日 星期六 16时38分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define ls(x) Tree[x].l
#define rs(x) Tree[x].r
typedef long long LL;

const int maxn = 4000010;

struct node
{
    int l, r, Min, Max;
} Tree[maxn];

struct Node
{
    int a, b, c, A, B, C, id, pos;
    bool operator < (const node &x) { return c < x.c; }
} a[maxn];

inline int cmp(Node a, Node b) { return a.a < b.a; }

inline int cmp(Node a, Node b) { return a.id < b.id; }

int n, m, num, N, M, cnt, Root[maxn];

inline void Push_up(int root)
{
    if ( ls(root) ) 
    {
        Tree[root].Min = min(Tree[root].Min, Tree[ls(root)].Min);
        Tree[root].Max = max(Tree[root].Max, Tree[ls(root)].Max);
    }
    if ( rs(root) ) 
    {
        Tree[root].Min = min(Tree[root].Min, Tree[rs(root)].Min);
        Tree[root].Max = max(Tree[root].Max, Tree[rs(root)].Max);
    }
}

inline void Update(int &root, int l, int r, int pos, int x)
{
    if ( !root ) root = ++ cnt;
    if ( l == r ) 
    { 
        Tree[root].Min = -2 * a[x].a + a[x].b; 
        Tree[root].Max = a[x].b; 
        return ; 
    }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Update(ls(root), l, Mid, pos, x);
    else Update(rs(root), Mid + 1, r, pos, x);
    Push_up(root);
}

inline int Query(int root, int l, int r, int pos, int x)
{
    if ( !root ) return 0x3f3f3f3f;
    if ( l == r ) return 
}

inline int lowbit(int x) { return x & -x; }

inline void Add(int pos, int x)
{
    for ( int i = pos; i <= M; i += lowbit(i) )
    {
        Update(Root[i], 1, N, a[x].A, x);
        Update(Root[N + i], 1, N, a[x].B, x);
    }
}

inline int Get_sum(int pos, int x)
{
    int ans = 0x3f3f3f3f;
    for ( int i = pos; i >= 1; i -= lowbit(i) )
        ans = min(ans, min(Query_Min(Root[i], 1, N, 1, a[x].A, x), Query_Max(Root[i], 1, N, a[x].A, N, x));
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { scanf("%d%d", &a[i].a, &a[i].b); a[i].c = a[i].a - a[i].b; a[i].id = i; }
    REP(i, n + 1, n + m) 
    { 
        scanf("%d", &a[i].pos); a[i].id = i; 
        scanf("%d%d", &a[i].a, &a[i].b); 
        a[i].c = a[i].a - a[i].b; 
    }

    sort(a + 1, a + n + m + 1, cmp);
    a[0].a = -0x3f3f3f3f;
    REP(i, 1, n + m) { if ( a[i].a != a[i - 1].a ) ++ num; a[i].A = num; }
    N = num;
    REP(i, 1, n + m) a[i].B = N - a[i].A;

    sort(a + 1, a + n + m + 1);
    num = 0; a[0].c = -0x3f3f3f3f;
    REP(i, 1, n + m) { if ( a[i].c != a[i - 1].c ) ++ num; a[i].C = num; }
    M = num;

    sort(a + 1, a + n + m + 1, cmp1);
    REP(i, 1, n) Add(a[i].C, i);

    REP(i, n + 1, n + m + 1)
    {
        if ( a[i].pos == 1 ) { Add(a[i].C, i); continue ; }
        printf("%d\n", Get_sum(a[i].C, i));
    }
    return 0;
}
