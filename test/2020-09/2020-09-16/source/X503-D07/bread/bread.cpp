/***************************************************************
	File name: bread.cpp
	Author: ljfcnyali
	Create time: 2020年09月16日 星期三 22时00分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 2010;
const int Mod = 998244353;

int n, m, k, lst, p1[maxn], p2[maxn], N1, N2, ans1, ans2, sum, f[maxn];
struct node { int x, y; } a[maxn];
struct Node { int len, sum, lazy; } Tree[maxn << 2];
vector<int> belong[maxn];
set<int> Set;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void PushTag(int root, int val)
{
    Tree[root].sum = val * Tree[root].len; 
    Tree[root].lazy = val;
}

inline void PushUp(int root) { Tree[root].sum = Tree[lson].sum + Tree[rson].sum; }

inline void PushDown(int root)
{
    if ( !Tree[root].lazy ) return ;
    PushTag(lson, Tree[root].lazy); PushTag(rson, Tree[root].lazy);
    Tree[root].lazy = 0;
}

inline void Build(int root, int l, int r)
{
    Tree[root].len = p1[r] - p1[l - 1]; Tree[root].sum = (n + 1) * Tree[root].len; Tree[root].lazy = 0;
    if ( l == r ) return ;
    int Mid = l + r >> 1; Build(lson, l, Mid); Build(rson, Mid + 1, r);
    PushUp(root);
}

inline void Modify(int root, int l, int r, int L, int R, int val)
{
    if ( L > R ) return ;
    if ( L <= l && r <= R ) { PushTag(root, val); return ; } 
    int Mid = l + r >> 1; PushDown(root);
    if ( L <= Mid ) Modify(lson, l, Mid, L, R, val);
    if ( Mid < R ) Modify(rson, Mid + 1, r, L, R, val);
    PushUp(root);
}

signed main()
{
    freopen("bread.in", "r", stdin);
    freopen("bread.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k);
    REP(i, 1, k) scanf("%lld%lld", &a[i].x, &a[i].y);
    sort(a + 1, a + k + 1, [](node &a, node &b) { return a.x < b.x; });
    lst = 0; REP(i, 1, k) if ( a[i].x != lst ) { lst = p1[++ N1] = a[i].x; a[i].x = N1; } else a[i].x = N1;
    sort(a + 1, a + k + 1, [](node &a, node &b) { return a.y < b.y; });
    lst = 0; REP(i, 1, k) if ( a[i].y != lst ) { lst = p2[++ N2] = a[i].y; a[i].y = N2; } else a[i].y = N2;

    p2[N2 + 1] = m + 1; p1[N1 + 1] = n + 1;
    REP(i, 1, k) REP(j, 1, k)
    {
        int Minx = min(a[i].x, a[j].x), Maxx = max(a[i].x, a[j].x);
        int Miny = min(a[i].y, a[j].y), Maxy = max(a[i].y, a[j].y);
        ans2 = (ans2 + (p1[Minx] * p2[Miny] % Mod) * ((n + 1 - p1[Maxx]) * (m + 1 - p2[Maxy]) % Mod)) % Mod;
    }
    REP(i, 1, k) ans1 = (ans1 + (p1[a[i].x] * p2[a[i].y] % Mod) * ((n + 1 - p1[a[i].x]) * (m + 1 - p2[a[i].y]) % Mod)) % Mod;
    REP(i, 1, k) belong[a[i].y].push_back(a[i].x);

    REP(i, 1, N2) 
    {
        Set.clear(); Set.insert(0); Build(1, 1, N1);
        REP(j, i, N2)
        {
            for ( auto it : belong[j] ) 
            {
                int pos = *(-- Set.lower_bound(it));
                Modify(1, 1, N1, pos + 1, it, p1[it]);
                Set.insert(it);
            }
            int ret = (n + 1) * p1[N1] % Mod;
            ret = (ret - Tree[1].sum) % Mod;
            sum = (sum + (ret * (p2[i] - p2[i - 1]) % Mod) * (p2[j + 1] - p2[j])) % Mod;
        }
    }

    int x = ans1 * power(sum, Mod - 2) % Mod;
    int ans = (ans2 + (x * x % Mod) * sum - 2 * ans1 * x) % Mod;
    ans = ans * power(sum, Mod - 2) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
