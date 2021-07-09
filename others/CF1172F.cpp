/***************************************************************
	File name: CF1172F.cpp
	Author: ljfcnyali
	Create time: 2020年06月10日 星期三 08时17分15秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define int long long
typedef long long LL;
 
const int maxn = 1e6 + 10;
const int INF = 1e18;
 
int n, m, p, a[maxn], sum[maxn << 2];
vector<int> Tree[maxn << 2];
 
inline void PushUp(int root)
{
    sum[root] = sum[lson] + sum[rson];
    int j = 0, n1 = Tree[lson].size() - 2, n2 = Tree[rson].size() - 2;
    REP(i, 0, Tree[root].size() - 1) Tree[root][i] = INF;
    REP(i, 0, n1) 
    {
        if ( j ) -- j;
        int L = Tree[lson][i] + sum[lson] - p * i;
        int R = Tree[lson][i + 1] + sum[lson] - p * i;
        while ( L >= Tree[rson][j + 1] && j < n2 ) ++ j;
        while ( R <= Tree[rson][j] && j > 0 ) -- j;
        while ( j <= n2 && L < Tree[rson][j + 1] && Tree[rson][j] < R ) 
        {
            Tree[root][i + j] = min(Tree[root][i + j], max(Tree[lson][i], Tree[rson][j] - sum[lson] + p * i));
            ++ j;
        }
    }
}
 
inline void Build(int root, int l, int r)
{
    if ( l == r ) 
    { 
        sum[root] = a[l]; 
        Tree[root].push_back(-INF);   
        Tree[root].push_back(p - a[l]);
        Tree[root].push_back(INF);
        return ;
    }
    int Mid = l + r >> 1; 
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    Tree[root].resize(r - l + 3);
    PushUp(root);
}
 
inline void Query(int root, int l, int r, int L, int R, int &ans)
{
    if ( L <= l && r <= R ) 
    {
        auto i = upper_bound(Tree[root].begin(), Tree[root].end(), ans) - Tree[root].begin() - 1;
        ans += sum[root] - i * p; return ;
    }
    int Mid = l + r >> 1;
    if ( L <= Mid ) Query(lson, l, Mid, L, R, ans);
    if ( Mid < R ) Query(rson, Mid + 1, r, L, R, ans);
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &m, &p);
    REP(i, 1, n) scanf("%lld", &a[i]);
    Build(1, 1, n);
    while ( m -- ) 
    {
        int l, r, ans = 0; scanf("%lld%lld", &l, &r);
        Query(1, 1, n, l, r, ans);
        printf("%lld\n", ans);
    }
    return 0;
}
 
