/***************************************************************
	File name: b.cpp
	Author: ljfcnyali
	Create time: 2020年10月22日 星期四 15时55分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
#define ls(x) Tree[x].lson
#define rs(x) Tree[x].rson
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, m, k, a[maxn], s[maxn], vl[maxn], vr[maxn], ans, c[maxn], Root[maxn], tot;
struct node { int lson, rson, suml, sumr, sl, sr, lazy, val; } Tree[maxn << 5];
map<int, int> Map;

inline pii operator + (pii a, pii b) { return pii(a.x + b.x, a.y + b.y); }

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val) { for ( int i = pos; i <= k; i += lowbit(i) ) c[i] += val; }

inline int get(int pos) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[i]; return ret; }

inline void PushTag(int root, int val)
{
    Tree[root].suml += Tree[root].sl * val;
    Tree[root].sumr += Tree[root].sr * val;
    Tree[root].val += val;
    Tree[root].lazy += val;
}

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    if ( !ls(root) ) ls(root) = ++ tot; PushTag(ls(root), Tree[root].lazy);
    if ( !rs(root) ) rs(root) = ++ tot; PushTag(rs(root), Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void PushUp(int root)
{
    Tree[root].suml = Tree[ls(root)].suml + Tree[rs(root)].suml;
    Tree[root].sumr = Tree[ls(root)].sumr + Tree[rs(root)].sumr;
    Tree[root].sl = Tree[ls(root)].sl + Tree[rs(root)].sl;
    Tree[root].sr = Tree[ls(root)].sr + Tree[rs(root)].sr;
}

inline void Modify1(int &root, int l, int r, int L, int R, int val)
{
    if ( L > R ) return ;
    if ( !root ) root = ++ tot;
    if ( L <= l && r <= R ) { PushTag(root, val); return ; }
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify1(ls(root), l, Mid, L, R, val);
    if ( Mid < R ) Modify1(rs(root), Mid + 1, r, L, R, val);
    PushUp(root);
}

inline void Modify2(int &root, int l, int r, int pos, int op)
{
    if ( !root ) root = ++ tot;
    if ( l == r ) 
    { 
        Tree[root].sl = vl[pos] * op; Tree[root].suml = vl[pos] * Tree[root].val * op;
        Tree[root].sr = vr[pos] * op; Tree[root].sumr = vr[pos] * Tree[root].val * op;
        return ;
    }
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) Modify2(ls(root), l, Mid, pos, op);
    else Modify2(rs(root), Mid + 1, r, pos, op);
    PushUp(root);
}

inline pii Query1(int root, int l, int r, int L, int R)
{
    if ( L > R || !root ) return pii(0, 0);
    if ( L <= l && r <= R ) return pii(Tree[root].sl, Tree[root].suml);
    int Mid = l + r >> 1; pii x = pii(0, 0); PushDown(root);
    if ( L <= Mid ) x = x + Query1(ls(root), l, Mid, L, R);
    if ( Mid < R ) x = x + Query1(rs(root), Mid + 1, r, L, R);
    return x;
}

inline pii Query2(int root, int l, int r, int L, int R)
{
    if ( L > R || !root ) return pii(0, 0);
    if ( L <= l && r <= R ) return pii(Tree[root].sr, Tree[root].sumr);
    int Mid = l + r >> 1; pii x = pii(0, 0); PushDown(root);
    if ( L <= Mid ) x = x + Query2(ls(root), l, Mid, L, R);
    if ( Mid < R ) x = x + Query2(rs(root), Mid + 1, r, L, R);
    return x;
}

inline int Find(int root, int l, int r, int pos)
{
    if ( l == r ) return Tree[root].val;
    int Mid = l + r >> 1; PushDown(root);
    if ( pos <= Mid ) return Find(ls(root), l, Mid, pos);
    return Find(rs(root), Mid + 1, r, pos);
}

inline void Insert(int &root, int pos)
{
    Modify1(root, 1, n, pos, n, 1);
    Modify2(root, 1, n, pos, 1);
    pii val1 = Query1(root, 1, n, 1, pos - 1);
    pii val2 = Query2(root, 1, n, pos + 1, n);
    int num = Find(root, 1, n, pos);
    ans = (ans + vr[pos] * num * val1.x) % Mod;
    ans = (ans - vr[pos] * (val1.y + val1.x)) % Mod;
    ans = (ans - vl[pos] * num * val2.x) % Mod;
    ans = (ans + vl[pos] * (val2.y - val2.x)) % Mod;
    ans = (ans + val1.x * val2.x) % Mod;
}

inline void Delete(int &root, int pos)
{
    pii val1 = Query1(root, 1, n, 1, pos - 1);
    pii val2 = Query2(root, 1, n, pos + 1, n);
    int num = Find(root, 1, n, pos);
    ans = (ans - vr[pos] * num * val1.x) % Mod;
    ans = (ans + vr[pos] * (val1.y + val1.x)) % Mod;
    ans = (ans + vl[pos] * num * val2.x) % Mod;
    ans = (ans - vl[pos] * (val2.y - val2.x)) % Mod;
    ans = (ans - val1.x * val2.x) % Mod;
    Modify1(root, 1, n, pos, n, -1);
    Modify2(root, 1, n, pos, 0);
}

signed main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld", &s[i]); a[i] = s[i]; }
    sort(a + 1, a + n + 1); k = unique(a + 1, a + n + 1) - a - 1;
    REP(i, 1, k) Map[a[i]] = i; REP(i, 1, n) s[i] = Map[s[i]]; 

    REP(i, 1, n) { vl[i] = get(s[i]); add(s[i], 1); }
    mem(c);
    for ( int i = n; i >= 1; -- i ) { vr[i] = get(s[i]); add(s[i], 1); }

    REP(i, 1, n) Insert(Root[s[i]], i);
    printf("%lld\n", (ans + Mod) % Mod);

    scanf("%lld", &m);
    while ( m -- ) 
    {
        int t, x; scanf("%lld%lld", &t, &x);
        if ( t == 2 ) Insert(Root[s[x]], x);
        else Delete(Root[s[x]], x);
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
