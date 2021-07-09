/***************************************************************
	File name: b.cpp
	Author: ljfcnyali
	Create time: 2019年11月03日 星期日 08时32分16秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
#define ls(x) Tree[root].lson
#define rs(x) Tree[root].rson
typedef long long LL;

const int maxn = 2000010;
const int N = 400000000;
const int M = 200000000;

int n, w[maxn], l[maxn], c[maxn], ans = 2147483647, t, tot, Root;
struct node { int lson, rson, sum; } Tree[maxn << 2];

inline void Modify(int &root, int l, int r, int pos, int val)
{
    if ( !root ) root = ++ tot;
    Tree[root].sum += val;
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(ls(root), l, Mid, pos, val);
    else Modify(rs(root), Mid + 1, r, pos, val);
}

inline int Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) return Tree[root].sum;
    int Mid = l + r >> 1, ret = 0;
    if ( L <= Mid ) ret += Query(ls(root), l, Mid, L, R);
    if ( Mid < R ) ret += Query(rs(root), Mid + 1, r, L, R);
    return ret;
}

int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d%d%d", &w[i], &l[i], &c[i]);
    int ret = 1;
    for ( int i = n; i >= 1; -- i ) 
    {
        ret += w[i];
        Modify(Root, 0, N, w[i] - l[i] + M - ret, c[i]);
        int sum = Query(Root, 0, N, 0, M - ret);
        if ( sum < ans ) { ans = sum; t = i; }
    }
    ret = 0;
    REP(i, t, n)
    {
        ret += w[i];
        if ( ret <= l[i] ) printf("%d\n", i);
    }
    return 0;
}
