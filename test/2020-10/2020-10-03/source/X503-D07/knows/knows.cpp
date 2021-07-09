/***************************************************************
	File name: know.cpp
	Author: ljfcnyali
	Create time: 2020年10月03日 星期六 09时14分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define lson root << 1
#define rson root << 1 | 1
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 2e9 + 10;

int n, p[maxn], q[maxn], c[maxn], f[maxn], id[maxn];
pii ans;
struct node { int Max, lMin; } Tree[maxn << 2];

inline void Find(int root, int l, int r, int L, int R)
{
    if ( Tree[root].Max < ans.first ) return ;
    int Mid = l + r >> 1;
    if ( L <= l && r <= R ) 
    {
        if ( l != r && Tree[rson].Max < ans.first ) Find(lson, l, Mid, L, R);     
        else 
        { 
            if ( l != r ) Find(rson, Mid + 1, r, L, R);
            ans.first = Tree[root].Max; ans.second = min(ans.second, Tree[root].lMin); 
        }
        return ;
    }
    if ( Mid < R ) Find(rson, Mid + 1, r, L, R);
    if ( L <= Mid ) Find(lson, l, Mid, L, R);
}

inline void PushUp(int root, int l, int r)
{
    int Mid = l + r >> 1;
    ans = pii(Tree[rson].Max, INF);
    Find(lson, l, Mid, l, Mid);
    Tree[root].lMin = ans.second;
    Tree[root].Max = max(Tree[lson].Max, Tree[rson].Max);
}

inline void Modify(int root, int l, int r, int pos, int val, int w)
{
    if ( l == r ) { Tree[root].Max = val; Tree[root].lMin = w; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val, w);
    else Modify(rson, Mid + 1, r, pos, val, w);
    PushUp(root, l, r);
}

int main()
{
    freopen("knows.in", "r", stdin);
    freopen("knows.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &p[i]); q[p[i]] = i; }
    REP(i, 1, n) scanf("%d", &c[i]);
    Modify(1, 0, n, 0, 0, 0);
    REP(i, 1, n) { Modify(1, 0, n, i, 0, INF); id[i] = i; }
    sort(id + 1, id + n + 1, [](int a, int b) { return q[a] < q[b]; });
    REP(i, 1, n)
    {
        int pos = id[i];
        ans = pii(0, INF); Find(1, 0, n, 0, pos - 1);
        f[pos] = ans.second + c[q[pos]]; 
        Modify(1, 0, n, pos, q[pos], f[pos]);
    }
    int ans = INF, Max = 0;
    for ( int i = n; i >= 1; -- i )
    {
        if ( Max < q[i] ) ans = min(ans, f[i]);
        Max = max(Max, q[i]);
    }
    printf("%d\n", ans);
    return 0;
}
