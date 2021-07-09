/***************************************************************
	File name: lipschitz.cpp
	Author: ljfcnyali
	Create time: 2019年11月02日 星期六 08时33分33秒
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

const int maxn = 100010;

int n, m, a[maxn], Max[maxn << 2];

inline void PushUp(int root) { Max[root] = max(Max[lson], Max[rson]); }

inline void Build(int root, int l, int r)
{
    if ( l == r ) { Max[root] = abs(a[l + 1] - a[l]); return ; }
    int Mid = l + r >> 1;
    Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline void Modify(int root, int l, int r, int pos, int val)
{
    if ( l == r ) { Max[root] = val; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
    PushUp(root);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L > R ) return 0;
    if ( L <= l && r <= R ) return Max[root];
    int Mid = l + r >> 1, ret = 0;
    if ( L <= Mid ) ret = max(ret, Query(lson, l, Mid, L, R));
    if ( Mid < R ) ret = max(ret, Query(rson, Mid + 1, r, L, R));
    return ret;
}

int main()
{
    freopen("lipschitz.in", "r", stdin);
    freopen("lipschitz.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    Build(1, 1, n - 1);
    scanf("%d", &m);
    REP(o, 1, m)
    {
        int opt, l, r; scanf("%d%d%d", &opt, &l, &r);
        if ( opt == 0 ) 
        { 
            a[l] = r;
            // REP(i, 1, n) printf("%d ", a[i]); puts("");
            // REP(i, 1, n - 1) printf("%d ", Query(1, 1, n - 1, i, i)); puts("");
            Modify(1, 1, n - 1, l - 1, abs(a[l] - a[l - 1])); 
            if ( l != n ) Modify(1, 1, n - 1, l, abs(a[l] - a[l + 1])); 
            continue ;
        }
        else printf("%d\n", Query(1, 1, n - 1, l, r - 1));
    }
    return 0;
}
