/***************************************************************
	File name: G.cpp
	Author: ljfcnyali
	Create time: 2020年07月13日 星期一 16时47分17秒
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

const int maxn = 6e5 + 10;
const int INF = 1e9 + 10;

int n, m, a[maxn], b[maxn], ans;
struct node { int Min; } Tree[maxn]; 

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Tree[root].Min = a[l]; return ; }
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Tree[root].Min = min(Tree[lson].Min, Tree[rson].Min);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].Min;
    int Mid = l + r >> 1, Min = INF;
    if ( L <= Mid ) Min = min(Min, Query(lson, l, Mid, L, R));
    if ( Mid < R ) Min = min(Min, Query(rson, Mid + 1, r ,L, R));
    return Min;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i ,1, n) scanf("%d", &a[i]);
    Build(1, 1, n);
    int Max = 0;
    REP(i, 1, m) { scanf("%d", &b[i]); Max = max(Max, b[i]); }
    REP(i, 1, n - m + 1)
    {
        int j = i + m - 1;
        if ( Query(1, 1, n, i, j) >= Max ) { ++ ans; continue ; }
        int l = 1, r = m, tot = 0;
        while ( l <= r ) 
        {
            if ( a[i + l - 1] < b[l] ) goto Finish ;
            if ( a[i + r - 1] < b[r] ) goto Finish ;
            ++ l; -- r; 
        }
        ++ ans;
Finish : ;
    }
    printf("%d\n", ans);
    return 0;
}
