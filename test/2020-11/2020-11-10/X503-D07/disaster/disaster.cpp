/***************************************************************
	File name: disaster.cpp
	Author: ljfcnyali
	Create time: 2020年11月20日 星期五 11时26分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define ls(x) Tree[op][x].lson
#define rs(x) Tree[op][x].rson
typedef long long LL;

const int maxn = 5e5 + 10;
const int N = 2e9;

int n, m, q, op, Root[2][maxn], tot, ans, sum[maxn];
struct node 
{
    int x, l, r;
    node ( int a = 0, int b = 0, int c = 0 ) { x = a; l = b; r = c; }
} a[maxn];
vector<int> p;
struct Node { int lson, rson, sum; } Tree[2][maxn << 5];
map<int, int> Map;

inline int Modify(int op, int now, int l, int r, int pos, int val)
{
    int root = ++ tot; Tree[op][root] = Tree[op][now]; Tree[op][root].sum += val;
    if ( l == r ) return root;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) ls(root) = Modify(op, ls(root), l, Mid, pos, val);
    else rs(root) = Modify(op, rs(root), Mid + 1, r, pos, val);
    return root;
}

inline int Query(int op, int p, int q, int l, int r, int L, int R)
{
    if ( Tree[op][p].sum == Tree[op][q].sum ) return 0;
    if ( L <= l && r <= R ) return Tree[op][p].sum - Tree[op][q].sum;
    int Mid = l + r >> 1, ret = 0;
    if ( L <= Mid ) ret += Query(op, ls(p), ls(q), l, Mid, L, R);
    if ( Mid < R ) ret += Query(op, rs(p), rs(q), Mid + 1, r, L, R);
    return ret;
}

signed main()
{
    freopen("disaster.in", "r", stdin);
    freopen("disaster.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &q, &op);
    REP(i, 1, n) scanf("%lld%lld%lld", &a[i].x, &a[i].l, &a[i].r);
    sort(a + 1, a + n + 1, [](node &a, node &b) { return a.x < b.x; });
    a[0].x = -1; int m = 0;
    p.push_back(-N);
    REP(i, 1, n)
    {
        if ( a[i].x != a[i - 1].x ) 
        { 
            ++ m; Root[0][m] = Root[0][m - 1]; Root[1][m] = Root[1][m - 1];
            sum[m] = sum[m - 1]; Map[a[i].x] = m; p.push_back(a[i].x); 
        }
        sum[m] += a[i].x;
        Root[0][m] = Modify(0, Root[0][m], 0, N, a[i].r, a[i].x); 
        Root[1][m] = Modify(1, Root[1][m], 0, N, a[i].l, a[i].x);
    }
    p.push_back(N);

    REP(i, 1, q)
    {
        int l, r, u, v; scanf("%lld%lld%lld%lld", &l, &r, &u, &v);
        // l ^= ans * op; r ^= ans * op; u ^= ans * op; v ^= ans * op;
        int posl = *lower_bound(p.begin(), p.end(), l);          
        int posr = *(-- upper_bound(p.begin(), p.end(), r));
        if ( posl < 0 || posr >= N ) { ans = 0; puts("0"); continue ; }
        l = Map[posl]; r = Map[posr]; ans = sum[r] - sum[l - 1];

        ans -= Query(0, Root[0][r], Root[0][l - 1], 0, N, 0, u - 1);
        ans -= Query(1, Root[1][r], Root[1][l - 1], 0, N, v + 1, N);
        printf("%lld\n", ans);
    }
    return 0;
}
