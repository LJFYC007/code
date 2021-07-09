/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2020年06月09日 星期二 14时14分14秒
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

const int maxn = 1e6 + 100;

int N = maxn - 10, n, a[maxn], Delta = 500010, ans, c[maxn];
struct node { int Max, lazy; } Tree[maxn << 2];

inline void PushUp(int root) { Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max); }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    Tree[lson].lazy += Tree[root].lazy;
    Tree[rson].lazy += Tree[root].lazy;
    Tree[lson].Max += Tree[root].lazy;
    Tree[rson].Max += Tree[root].lazy;
    Tree[root].lazy = 0;
}

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].Max = -(l - Delta); return ; } 
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L <= l && r <= R ) { Tree[root].Max += val; Tree[root].lazy += val; return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].Max;
    int Mid = l + r >> 1, ans = -N; PushDown(root);
    if ( L <= Mid ) ans = max(ans, Query(lson, l, Mid, L, R));
    if ( Mid < R ) ans = max(ans, Query(rson, Mid + 1, r, L, R));
    return ans;
}

inline int lowbit(int x) { return x & -x; } 

inline void add(int pos) { for ( int i = pos; i <= N; i += lowbit(i) ) ++ c[i]; }

inline int get(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i]; return sum; } 

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    Build(1, 0, N);
    REP(i, 1, n)
    {
        Modify(1, 0, N, a[i] + Delta, N, 1);        
        add(a[i] + Delta);
        int L = -Delta, R = 0, pos = N;
        while ( L <= R ) 
        { 
            int Mid = L + R >> 1;
            if ( get(Mid + Delta) >= -Mid ) { R = Mid - 1; pos = Mid; }
            else L = Mid + 1;
        }
        // printf("%d ", pos);
        Modify(1, 0, N, 0, N, -get(pos + Delta - 1));
        ans = i - get(pos + Delta - 1) - Query(1, 0, N, pos + Delta, N);
        Modify(1, 0, N, 0, N, +get(pos + Delta - 1));
        printf("%d\n", ans);
    }
    return 0;
}
